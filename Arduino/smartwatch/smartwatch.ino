#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include "time.h"

// Replace with your network credentials
const char* ssid = "Unit18";
const char* password = "Vegas18!";

// NTP server settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -25200; // Adjust for your timezone (e.g., -18000 for EST)
const int daylightOffset_sec = 3600; // Adjust for daylight savings if applicable

TFT_eSPI tft = TFT_eSPI();

// Constants for watch face
#define CENTER_X 120
#define CENTER_Y 120
#define RADIUS 100

void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  drawWatchFace();
}

void loop() {
  drawTime();
  delay(1000);
}

void drawWatchFace() {
  tft.drawCircle(CENTER_X, CENTER_Y, RADIUS, TFT_WHITE);

  for (int i = 0; i < 12; i++) {
    float angle = i * 30 * DEG_TO_RAD;
    int x0 = CENTER_X + (RADIUS - 10) * cos(angle);
    int y0 = CENTER_Y + (RADIUS - 10) * sin(angle);
    int x1 = CENTER_X + RADIUS * cos(angle);
    int y1 = CENTER_Y + RADIUS * sin(angle);
    tft.drawLine(x0, y0, x1, y1, TFT_WHITE);
  }
}

void drawTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Time not set");
    return;
  }

  int hours = timeinfo.tm_hour % 12;
  int minutes = timeinfo.tm_min;
  int seconds = timeinfo.tm_sec;

  tft.fillCircle(CENTER_X, CENTER_Y, RADIUS - 19, TFT_BLACK);

  float secAngle = seconds * 6 * DEG_TO_RAD;
  float minAngle = minutes * 6 * DEG_TO_RAD + seconds * 0.1 * DEG_TO_RAD;
  float hourAngle = hours * 30 * DEG_TO_RAD + minutes * 0.5 * DEG_TO_RAD;

  int hx = CENTER_X + (RADIUS - 50) * cos(hourAngle);
  int hy = CENTER_Y + (RADIUS - 50) * sin(hourAngle);
  tft.drawLine(CENTER_X, CENTER_Y, hx, hy, TFT_RED);

  int mx = CENTER_X + (RADIUS - 30) * cos(minAngle);
  int my = CENTER_Y + (RADIUS - 30) * sin(minAngle);
  tft.drawLine(CENTER_X, CENTER_Y, mx, my, TFT_GREEN);

  int sx = CENTER_X + (RADIUS - 20) * cos(secAngle);
  int sy = CENTER_Y + (RADIUS - 20) * sin(secAngle);
  tft.drawLine(CENTER_X, CENTER_Y, sx, sy, TFT_BLUE);
}
