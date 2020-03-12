#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <Adafruit_SSD1306.h>
Adafruit_BMP280 bmp;
BH1750 lightMeter;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char auth[] = "DCsDZhcKEmqpL-VFZe-CHjf2crsvhZ1T";
char ssid[] = "qh";
char pass[] = "12345678";

float bmpTemp;
float bmpPress;
float lux;

void setup() {

  Serial.begin(115200);

    if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);

  }

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);

  }

    lightMeter.begin();



  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }

  Serial.println("WiFi connected");
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);

}

void loop() {

  delay(1000);

  bmpTemp = bmp.readTemperature();

  lux = lightMeter.readLightLevel();

  Serial.println("--------------------------------");
  Serial.println("BMP280 Sensor:");
  Serial.print("Temperature = ");
  Serial.print(bmpTemp);
  Serial.println(" °C");
  Serial.println("BH1750 Sensor:");
  Serial.print("Light = ");
  Serial.print(lux);
  Serial.println(" lux");

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.println("BMP280:");
  display.setCursor(0, 10);
  display.setTextColor(BLACK, WHITE);
  display.print((char)247); // ' ° ' graden symbool
  display.print("C: ");
  display.print(bmpTemp, 1);

  display.setCursor(0, 30);
  display.setTextColor(WHITE);
  display.println("BH1750:");
  display.setCursor(0, 40);
  display.setTextColor(BLACK, WHITE);
  display.print("Light = ");
  display.print(lux);
  display.print(" lux");
  display.display();

  Blynk.run();
  Blynk.virtualWrite(V1, bmpTemp);
  Blynk.virtualWrite(V2, lux);

}
