"# Smart-Sewage-Monitoring-System" 
The smart sewage monitoring system is an IOT based system  technology that uses the esp86 microntroller ,ultrasonic sensor and blynk console to display the level of sewage waste in a drainage ,manholes ,and sewers
This code is a complete Arduino sketch designed for a smart sewage monitoring system that uses an ultrasonic sensor to measure distances and esp86 microcontroller. It utilizes the Blynk platform to send the collected data to a mobile application for remote monitoring.Let me give more details in the code breakdown below.

1. Blynk-Specific Constants
#define BLYNK_TEMPLATE_ID "TMPL2ON8_11M0"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "8usAfS4H-cE4-WM7jTWMbSiV3qI0cPlu"
These lines define constants for the Blynk platform:
BLYNK_TEMPLATE_ID and BLYNK_TEMPLATE_NAME identify the Blynk template being used.
BLYNK_AUTH_TOKEN is the unique token for your Blynk project, allowing the device to connect to the Blynk server.

2. Library Inclusions
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
These lines include the Blynk libraries needed for the main Blynk functions and for ESP8266 WiFi boards.

3. WiFi Credentials
const char* ssid = "TUK-WIFI";
const char* password = "P@ssword@123";
These lines define the SSID and password for the WiFi network the ESP8266 will connect to.

4. Ultrasonic Sensor Pin Definitions
const int trigPin = 12;
const int echoPin = 14;
Defines the GPIO pins on the ESP8266 connected to the ultrasonic sensor's trigger (trigPin) and echo (echoPin) pins.

5. Sound Velocity and Conversion Constants
#define SOUND_VELOCITY 0.034 // Speed of sound in air in cm/uS
#define CM_TO_INCH 0.393701 // Conversion constant from cm to inches
Defines constants for the speed of sound in air and the conversion factor from centimeters to inches.

6. Measurement Variables
long duration;
float distanceCm;
float distanceInch;
Variables to store the duration of the ultrasonic pulse and the calculated distances in centimeters and inches.

7. Setup Function
void setup() {
  Serial.begin(115200); // Start the serial communication for debugging
  pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
  pinMode(echoPin, INPUT); // Set the echoPin as an Input

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password); // Initialize the Blynk service with credentials
}
The setup function runs once when the ESP8266 starts:
Initializes serial communication for debugging.
Sets the pin modes for the ultrasonic sensor.
Initializes the Blynk service using the provided authentication token and WiFi credentials.

8. Loop Function
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

  // Delay for a second before the next
