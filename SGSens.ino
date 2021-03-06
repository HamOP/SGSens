/*
  SGSens - Battery voltage / altitude / vario / temperature Jeti EX telemetry sensor

  Author:   Stefan Glück
  Date:     2016-11-02
  Version:  0.2

  Platform:  Arduino Pro Mini
  Sensors:
    - Voltage divider to A0
    - BMP180 pressure sensor (SDA --> A4, SCL --> A5)
    - Current Sensor to A1
  Wiring:
    - TX0 --> Jeti RX signal
    - GND --> Jeti RX GND + BMP180 GND
    - +5V  --> Jeti RX +5V + BMP180 VCC (careful: BMP180 needs voltage regulator!)

    Sketch uses the millis() function to calculate climb rate - which will overflow after about 50 days according to Arduino reference.
    As the sensor is never intended to run this long, no overflow handling was implemented.

    Arduino libraries used:
      - JetiExSensor_V0.9.9 - https://sourceforge.net/projects/jetiexsensorcpplib/
      - BMP180_Breakout - https://github.com/sparkfun/BMP180_Breakout
*/

// includes
#include <SFE_BMP180.h>
#include <Wire.h>
#include <JetiExProtocol.h>

// initialization
JetiExProtocol jetiEx; // Jeti EX protocol handler
SFE_BMP180 pressure; // BMP180 pressure sensor

// global variables
double baseline; // baseline pressure
float voltage; // measured battery voltage
int sensorValue; // sensor value for voltage measurement
const int ratio = 3; // voltage divider ratio
const float correction = 1.00998; // calibration factor for voltage measurement
float count = 0; // variable for mean value calculation
unsigned long timestamp = 0; // for calculating vario rate
double temp; // Temperature from BMP180
double alti; // Altitude
double pres; // Air pressure
double vario; // Vario value
double sensVal;           // for raw sensor values 
float filterVal = 0.0;       // this determines smoothness  - .99 is max  0 is off (no smoothing)
double smoothedVal;     // this holds the last loop value just use a unique variable for every different sensor that needs smoothing
float amps;
double mAh = 0.0;
unsigned long timestamp_old = 0;



// Jeti EX sensor definitions

enum
{
  ID_VOLTAGE = 1,
  ID_ALTITUDE,
  ID_TEMP,
  ID_VARIO,
  ID_PRESS,
  ID_AMPS,
  ID_CAPA
};

// id from 1..15
JETISENSOR_PTR sensors[] =
{
  //              id             name          unit         data type             precision 0->0, 1->0.0, 2->0.00
  new JetiSensor( ID_VOLTAGE,    "Spannung",    "V",         JetiSensor::TYPE_14b, 2 ), // LiPo voltage
  new JetiSensor( ID_ALTITUDE,   "Hoehe",   "m",         JetiSensor::TYPE_14b, 0 ), // altitude
  new JetiSensor( ID_TEMP,       "Temperatur",       "\xB0\x43",  JetiSensor::TYPE_14b, 0 ), // temperature from BMP180 sensor
  new JetiSensor( ID_VARIO,      "Vario",      "m/s",       JetiSensor::TYPE_14b, 2 ), // climb rate
  new JetiSensor( ID_PRESS,      "Luftdruck",   "mbar",      JetiSensor::TYPE_14b, 0 ), // air pressure
  new JetiSensor( ID_AMPS,      "Strom",   "A",      JetiSensor::TYPE_14b, 2 ), // Current
  new JetiSensor( ID_CAPA,      "Kapazitaet",   "mAh",      JetiSensor::TYPE_14b, 0 ), // Capacity


  0 // end of array
};


void setup() {
  pressure.begin(); // initialize pressure sensor
  delay(1000);
  jetiEx.Start( "SGSens", sensors ); // start JetiEX stack
  baseline = getPressure();  // get baseline pressure
  timestamp = millis();
}

void loop() {
  timestamp_old = timestamp;
  jetiEx.SetSensorValue( ID_VOLTAGE, getVoltage());
  amps = getAmps();
  jetiEx.SetSensorValue( ID_AMPS, amps*100);
  readAlti();
  smoothedVal =  smooth(vario, filterVal, smoothedVal);
  jetiEx.SetSensorValue( ID_ALTITUDE, alti);
  jetiEx.SetSensorValue( ID_TEMP, temp);
  jetiEx.SetSensorValue( ID_VARIO, smoothedVal);
  jetiEx.SetSensorValue( ID_PRESS, pres);
  mAh = mAh + ((timestamp-timestamp_old)/3600.*amps);
  jetiEx.SetSensorValue( ID_CAPA, mAh);
  jetiEx.DoJetiSend();
}

double getVoltage()
{
  count = 0;
  for(int x = 0; x < 20; x++){
    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1023.0)*100*ratio*correction;
    count = count + voltage;
    //delay(10);
    }
  voltage = count / 20.0;
  return voltage;
}

double getAmps()
{
  count = 0;
  for(int x = 0; x < 20; x++){
    sensorValue = analogRead(A1);
    voltage = (sensorValue * (5.0 / 1023.0)-2.5)*10;
    count = count + voltage;
    //delay(10);
    }
  voltage = count / 20.0;
  return voltage;
}

double getPressure()
{
  char status;
  double T,P;

  // You must first get a temperature measurement to perform a pressure reading.

  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    temp = T;
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
      }
    }
  }

}

void readAlti() {
  unsigned long timestamp_old;
  double alti_old;
  count = 0;
  for(int x = 0; x < 10; x++){
    alti_old = alti;
    timestamp_old = timestamp;
    pres = getPressure();
    count = count + pres;
    //delay(10);
    }
  pres = count / 10.0;
  //pres = getPressure();
  alti_old =  pressure.altitude(pres,baseline);
  //delay(20);
    count = 0;
  for(int x = 0; x < 10; x++){
    alti_old = alti;
    timestamp_old = timestamp;
    pres = getPressure();
    count = count + pres;
    //delay(10);
    }
  pres = count / 10.0;
  timestamp = millis();
  alti = pressure.altitude(pres,baseline);
  vario = ( 100*(alti - alti_old) * 1000) / (timestamp - timestamp_old);
  /* Serial.print(alti);
   Serial.print(" ");
   Serial.print((alti - alti_old));
   Serial.print(" ");
   Serial.println((timestamp - timestamp_old));
  */
  //Serial.print(vario);
  //Serial.print(" ");
}

double smooth(double data, float filterVal, double smoothedVal){


  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (double)smoothedVal;
}
