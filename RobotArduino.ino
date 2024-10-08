// General global variables
int echoPin = 13;              // Echo Pin of Ultrasonic Sensor
int trigPin = 12;              // Trigger Pin of Ultrasonic Sensor
long duration;                 //Time (in microseconds) it takes for pulses to come back to sensor
double distance_cm;            //measured distance, in cm
double speedOfSound = 34321.0; /*in cm/s, in air, at room 20 degrees C */
const int ser_read = (1 / 50) * 1000;
//const int ser_read = 50;
unsigned long previousMillis = 0;


// Global variabes for low pass filter
double T = 0.02; // T = 1/50
double omega_c = .5;
double y_k;
double u_km1 = 0;
double y_km1 = 0;
double max_distance = 12;    // Distance that y_k has to be under for data to be captured
double previousY_k;


// Servo motor global variables
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
float pos = 0.00;    // variable to store the servo position
float increment = 0.1;


// Button variable
int button = 8;   // button pin
int buttonVal;


void setup() {


  Serial.begin(115200);      // Starting Serial Terminal
  pinMode(button, INPUT_PULLUP);
  pinMode(echoPin, INPUT);   //Set echo pin to input
  pinMode(trigPin, OUTPUT);  //Set trigger pin to output
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object


}


unsigned long currentMillis = millis();


void loop() {
  myservo.write(pos);
  currentMillis = millis();
  //this pulse results in the sensor sending out 8 pulses at 40 kHz
  if (currentMillis - previousMillis >= ser_read) {
    // save the last time you read serial
    previousMillis = currentMillis;    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 11500);               //time duration in microseconds for pulses to return to sensor
    distance_cm = (speedOfSound * duration * 1.0e-6) * 0.5; //speed of sound (cm/s) * time duration (s)
   
    y_k = (1 - omega_c * T) * y_km1 + omega_c * T * u_km1;  // Filtered distance signal
    y_km1 = y_k;
    u_km1 = distance_cm;
         
    buttonVal = digitalRead(button);


    if (buttonVal == LOW) {    
      pos = pos + increment;
      if (pos >= 160) {
        increment = -increment;    
      }
      else if (pos <= 0) {
        increment = -increment;
      }
    }
       
    String pos_value = String(pos);
    String yk_value = String(y_k);
    Serial.println(yk_value);
    Serial.println(pos_value);
   
  }
}