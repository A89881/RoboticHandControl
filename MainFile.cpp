```cpp
#include <Servo.h>  // Include the Servo library for controlling servos

int sensorData[5];  // Array to store sensor data from flex sensors

int servoMinPos = 1;  // Minimum position for servos
int servoMaxPos = 175;  // Maximum position for servos

int sensorMin[5] = { 1023, 1023, 1023, 1023, 1023 };  // Array to store minimum sensor values
int sensorMax[5] = { 0, 0, 0, 0, 0 };  // Array to store maximum sensor values

int sensorPins[5] = { 1, 2, 3, 4, 5 };  // Analog pins connected to flex sensors
int servoPins[5] = { 2, 3, 4, 5, 6 };  // Digital pins connected to servos
int servoPos[5];  // Array to store servo positions

Servo servos[5];  // Array of servo objects

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
  for (int i = 0; i < 5; i++) {  // Iterate through each servo
    servos[i].attach(servoPins[i]);  // Attach servo to its corresponding pin
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {  // Iterate through each flex sensor
    sensorData[i] = analogRead(sensorPins[i]);  // Read analog value from flex sensor
    sensorMin[i] = min(sensorMin[i], sensorData[i]);  // Update minimum sensor value
    sensorMax[i] = max(sensorMax[i], sensorData[i]);  // Update maximum sensor value
    servoPos[i] = map(sensorData[i], sensorMin[i], sensorMax[i], servoMinPos, servoMaxPos);  // Map sensor data to servo position
    servoPos[i] = constrain(servoPos[i], servoMinPos, servoMaxPos);  // Constrain servo position within min and max limits
    servos[i].write(servoPos[i]);  // Set servo position
    // Prints for debugging
    delay(100);  // Delay for stability
    Serial.print(i);  // Print sensor index
    Serial.print("::");
    Serial.print(" D: ");  // Print sensor data label
    Serial.print(sensorData[i]);  // Print sensor data
    Serial.print(" L:");  // Print sensor minimum label
    Serial.print(sensorMin[i]);  // Print sensor minimum value
    Serial.print(" H:");  // Print sensor maximum label
    Serial.print(sensorMax[i]);  // Print sensor maximum value
    Serial.print("  ");  // Print spacing
    Serial.print(servoPos[i]);  // Print servo position
    Serial.print("  ");  // Print spacing
  }
  Serial.print("\n");  // Move to the next line in serial monitor
}
```