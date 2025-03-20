#include <Servo.h>

#define SERVO_PIN 10
#define LED 13

Servo curtainServo;

const int TEMP_THRESHOLD = 30;
const int HUMIDITY_THRESHOLD = 60;
const int PRESSURE_THRESHOLD = 500;

void setup() {
  Serial.begin(9600);
  curtainServo.attach(SERVO_PIN);
  pinMode(LED, OUTPUT);
  curtainServo.write(0);
  Serial.println("Enter temperature, humidity, and pressure values:");
}

void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim(); // Remove leading/trailing whitespace

    int commaIndex1 = inputString.indexOf(',');
    int commaIndex2 = inputString.indexOf(',', commaIndex1 + 1);

    if (commaIndex1 != -1 && commaIndex2 != -1) {
      String tempString = inputString.substring(0, commaIndex1);
      String humidityString = inputString.substring(commaIndex1 + 1, commaIndex2);
      String pressureString = inputString.substring(commaIndex2 + 1);

      float temperature = tempString.toFloat();
      float humidity = humidityString.toFloat();
      int pressureValue = pressureString.toInt();

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" *C, Humidity: ");
      Serial.print(humidity);
      Serial.print(" %, Pressure:");
      Serial.println(pressureValue);

      if (temperature > TEMP_THRESHOLD && humidity > HUMIDITY_THRESHOLD) {
        digitalWrite(LED, HIGH);
        curtainServo.write(180);
        Serial.println("AC ON, Curtains CLOSED");
      } else {
        digitalWrite(LED, LOW);
        curtainServo.write(0);
        Serial.println("AC OFF, Curtains OPEN");
      }

      if (pressureValue > PRESSURE_THRESHOLD) {
        Serial.println("Diaper Change Needed!");
        delay(5000);
      }
      Serial.println("Enter temperature, humidity, and pressure values (separated by commas):");
    } else {
      Serial.println("Invalid input format. Please enter values separated by commas.");
      Serial.println("Enter temperature, humidity, and pressure values (separated by commas):");
    }
  }
  delay(100); // Small delay to prevent excessive serial reading.
}