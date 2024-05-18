// Define Blynk-specific constants
#define BLYNK_TEMPLATE_ID "TMPL2ON8_11M0"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "8usAfS4H-cE4-WM7jTWMbSiV3qI0cPlu"

// Include the main Blynk library
#include <Blynk.h>

// Include the Blynk library specific to ESP8266 WiFi boards
#include <BlynkSimpleEsp8266.h>

// Define WiFi SSID and Password
const char* ssid = "TUK-WIFI";
const char* password = "P@ssword@123";

// Define pins for the ultrasonic sensor (trig & echo pins)
const int trigPin = 12;
const int echoPin = 14;

#define SOUND_VELOCITY 0.034 // Speed of sound in air in cm/uS
#define CM_TO_INCH 0.393701 // Conversion constant from cm to inches

// Variables to store the measurement values
long duration;
float distanceCm;
float distanceInch;

// Initial setup that runs once
void setup() {
  Serial.begin(115200); // Start the serial communication for debugging
  pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
  pinMode(echoPin, INPUT); // Set the echoPin as an Input

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password); // Initialize the Blynk service with credentials
}

// Main loop that runs continuously
void loop() {
  Blynk.run(); // Blynk background task

  // Start ultrasonic distance measurement sequence
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the echo to be received
  duration = pulseIn(echoPin, HIGH);

  // Convert that time to a distance in cm
  distanceCm = duration * SOUND_VELOCITY / 2;

  // Convert the distance from cm to inches
  distanceInch = distanceCm * CM_TO_INCH;

  // Print the distance to the Serial Monitor for debugging
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  // Send the distance values to Blynk app
  Blynk.virtualWrite(V0, distanceCm); // Update virtual pin V0 with the distance in centimeters
  Blynk.virtualWrite(V1, distanceInch); // Update virtual pin V1 with the distance in inches

  // Delay for a second before the next loop iteration
  delay(1000);
}
