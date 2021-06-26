#include <DHT.h>
const int numSensors = 3;
const int readingPeriod = 300000; // 5 minutes in milliseconds. minimum is 2 seconds; 2000; as per specs
// Pin used by the Relay
int relayPin = 5;
// minimum Heat Index value to activate the relay
float minHeatIndex = 70.0;
// Array of DHT sensors. Can be 11's or 22's
DHT* sensors[numSensors];

void setup() {
  Serial.begin(9600);
  // Set the pin for outputing.
  pinMode(relayPin, OUTPUT);
  // Setup the sensors to be used
  for(int i = 0; i < numSensors; i++){
    // Create a new instance of each sensor.
    // Starts at pin 2. The type used is DHT22; 2nd argument.
    sensors[i] = new DHT(i+2, 22); 
    sensors[i]->begin();
  }
  delay(3000);
}

void loop() {
  float t, h, hi, hip = 0.0; 
  // Run over the sensors and get their readings.
  for(int i = 0; i < numSensors; i++){
    t = sensors[i]->readTemperature(true); // reading in fahrenheit
    h = sensors[i]->readHumidity();
    hi = sensors[i]->computeHeatIndex(t, h); // reading in fahrenheit
    hip += hi; // accumulate the heat index 
  }
  hip = hip / (float)numSensors; // get the average of the sensors
  // determine what to do with the relay module.
  if(minHeatIndex <= hip){
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }
  delay(readingPeriod); // Wait a set period of time before continuing

}
