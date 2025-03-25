#include <Servo.h>

// Define servo objects
Servo servo1;
Servo servo2;

// Define ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 8;

long duration;
int distance;

void setup() {
    // Attach the servo motors to pins 7 and 6
    servo1.attach(7);
    servo2.attach(6);

    // Initialize both servos to the open position (0 degrees)
    servo1.write(0);
    servo2.write(0);
    delay(2000); // Wait for 2 seconds

    // Configure ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Start serial communication for debugging
    Serial.begin(9600);
}

void loop() {
    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send a 10-microsecond pulse to the trigPin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the echo time
    duration = pulseIn(echoPin, HIGH);

    // Calculate distance (cm)
    if (duration == 0) {
        distance = 0;
        Serial.println("No echo received");
    } else {
        distance = duration * 0.034 / 2;
    }

    // Display distance on Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    // If an object is detected within 25 cm, close the barriers
    if (distance <= 25 && distance > 0) {
        servo1.write(90); // Close barrier 1 (90 degrees)
        servo2.write(90); // Close barrier 2 (90 degrees)
        Serial.println("Object detected! Barriers closing...");
        delay(3000); // Wait for 3 seconds
    } else {
        servo1.write(0); // Open barrier 1 (0 degrees)
        servo2.write(0); // Open barrier 2 (0 degrees)
        Serial.println("No object detected. Barriers open.");
    }

    delay(500); // Short delay before the next reading
}
