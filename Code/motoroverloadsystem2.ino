#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin definitions
const int PIN_IN1   = 23;   // L298N IN1
const int PIN_IN2   = 19;   // L298N IN2
const int PIN_RELAY = 18;   // Relay
const int PIN_BUZZ  = 5;    // Buzzer
const int PIN_ACS   = 34;   // ACS712 analog output
const int PIN_LM35  = 35;   // LM35 analog output

// ACS712 variables
const float ACS_SENSITIVITY = 0.185; // V/A (5A model)
const float ACS_ZERO_V = 2.5;
const float VREF = 3.3;
const int ADC_MAX = 4095;
const float thresholdA = 0.7; // Overload threshold (Amps)

void setup() {
  Serial.begin(115200);

  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_BUZZ, OUTPUT);

  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_BUZZ, LOW);

  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Motor Overload System");
  display.display();
  delay(1000);
}

float readCurrentA(int samples = 20) {
  long sum = 0;
  for (int i = 0; i < samples; ++i) {
    sum += analogRead(PIN_ACS);
    delay(2);
  }
  float avg = sum / (float)samples;
  float voltage = (avg / ADC_MAX) * VREF;
  float current = (voltage - ACS_ZERO_V) / ACS_SENSITIVITY;
  return fabs(current);
}

float readTemperatureC() {
  int raw = analogRead(PIN_LM35);
  float voltage = (raw * VREF) / ADC_MAX; // volts
  float tempC = voltage * 100;            // °C
  return tempC;
}

void showOLED(float I, float tempC) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.printf("Temp: %.1f C\n", tempC);

  display.setTextSize(2);
  display.printf("I=%.2fA\n", I);

  display.setTextSize(1);
  if (I > thresholdA) {
    display.println("!!! OVERLOAD !!!");
  } else {
    display.println("Running Normal");
  }
  display.display();
}

void loop() {
  float I = readCurrentA(30);
  float tempC = readTemperatureC();

  Serial.print("Current (A): ");
  Serial.print(I);
  Serial.print("   Temp (C): ");
  Serial.println(tempC);

  if (I > thresholdA) {
    digitalWrite(PIN_RELAY, LOW);
    digitalWrite(PIN_BUZZ, HIGH);
    showOLED(I, tempC);

    while (readCurrentA(20) > (thresholdA * 0.9)) {
      delay(200);
    }

    digitalWrite(PIN_BUZZ, LOW);
    digitalWrite(PIN_RELAY, HIGH);

  } else {
    digitalWrite(PIN_BUZZ, LOW);
    digitalWrite(PIN_RELAY, HIGH);
    showOLED(I, tempC);
  }

  delay(200);
}



