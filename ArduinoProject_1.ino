#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define timer 5000
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT interior(2,DHT11);
DHT exterior(4,DHT11);

void setup() {
  Serial.begin(9600); //DESCOMENTAR PARA DEBUG

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;){
      Serial.println(F("¡¡ERROR!! NO SE ENCUENTRA LA PANTALLA!"));
      delay(2000);
    } //NO INICIA LECTURA, AD INFINITUM Y AVISA POR SERIE(9600)
  }
  display.clearDisplay();
  interior.begin();
  exterior.begin();
}

void loop() {
  int tempIn = getTempIn();
  int humIn = getHumIn();
  int tempOut = getTempOut();
  int humOut = getHumOut();
  printInfoIn(tempIn, humIn);
  display.clearDisplay();
  printInfoOut(tempOut, humOut);
}

int getTempIn() {
  int temp = interior.readTemperature();
  return temp;
}

int getHumIn() {
  int hum = interior.readHumidity();
  return hum;
}

int getTempOut() {
  int temp = exterior.readTemperature();
  return temp;
}

int getHumOut() {
  int hum = exterior.readHumidity();
  return hum;
}

void printInfoIn(int printInfoIn, int humIn){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("TEMPERATURA  INTERIOR");
  display.setCursor(10,20);
  display.setTextSize(5);
  display.print(printInfoIn);
  display.setTextSize(2);
  display.setCursor(83,15);
  display.print("o");
  display.setTextSize(4);
  display.setCursor(95,20);
  display.print("C");
  display.display();
  delay(timer);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("  HUMEDAD  INTERIOR  ");
  display.setCursor(10,20);
  display.setTextSize(5);
  display.print(humIn);
  display.setTextSize(3);
  display.setCursor(80,20);
  display.print("%");
  display.display();
  delay(timer);
}

void printInfoOut(int printInfoOut, int humOut){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("TEMPERATURA  EXTERIOR");
  display.setCursor(10,20);
  display.setTextSize(5);
  display.print(printInfoOut);
  display.setTextSize(2);
  display.setCursor(83,15);
  display.print("o");
  display.setTextSize(4);
  display.setCursor(95,20);
  display.print("C");
  display.display();
  delay(timer);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("  HUMEDAD  EXTERIOR  ");
  display.setCursor(10,20);
  display.setTextSize(5);
  display.print(humOut);
  display.setTextSize(3);
  display.setCursor(80,20);
  display.print("%");
  display.display();
  delay(timer);
}