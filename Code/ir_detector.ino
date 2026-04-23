#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define SENSOR_PIN 26   // GP26 (ADC0)
#define BUZZER 15       // GP15

int threshold = 2000;   // adjust later

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER, OUTPUT);

  // I2C for OLED
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();

  // OLED init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while(1);
  }

  display.clearDisplay();
}

void loop() {

  int value = analogRead(SENSOR_PIN);

  // Serial debug
  Serial.println(value);

  // Buzzer logic
  if(value > threshold) {
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.print("IR Value: ");
  display.println(value);

  display.setCursor(0,15);
  display.print("Threshold: ");
  display.println(threshold);

  // Bar graph
  int bar = map(value, 0, 4095, 0, 120);
  display.drawRect(0, 30, 120, 10, WHITE);
  display.fillRect(0, 30, bar, 10, WHITE);

  // Status
  display.setCursor(0, 50);
  if(value > threshold) {
    display.println("DETECTED!");
  } else {
    display.println("Scanning...");
  }

  display.display();

  delay(100);
}

