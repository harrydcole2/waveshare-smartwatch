#include <TFT_eSPI.h>
#include <SPI.h>

// Set up the display
TFT_eSPI tft = TFT_eSPI();

// Constants for watch face
#define CENTER_X 120
#define CENTER_Y 120
#define RADIUS 100

void setup() {
  tft.init();
  tft.setRotation(1);  // Set orientation as needed
  tft.fillScreen(TFT_BLACK);
  drawWatchFace();
}

void loop() {
  drawTime();
  delay(1000);
}

void drawWatchFace() {
  // Draw outer circle
  tft.drawCircle(CENTER_X, CENTER_Y, RADIUS, TFT_WHITE);

  // Draw hour marks
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
  // Get the current time (replace with RTC logic if using an RTC module)
  int hours = (millis() / 3600000) % 12;
  int minutes = (millis() / 60000) % 60;
  int seconds = (millis() / 1000) % 60;

  // Clear previous hands
  tft.fillCircle(CENTER_X, CENTER_Y, RADIUS - 20, TFT_BLACK);

  // Calculate angles for each hand
  float secAngle = seconds * 6 * DEG_TO_RAD;
  float minAngle = minutes * 6 * DEG_TO_RAD + seconds * 0.1 * DEG_TO_RAD;
  float hourAngle = hours * 30 * DEG_TO_RAD + minutes * 0.5 * DEG_TO_RAD;

  // Draw hour hand
  int hx = CENTER_X + (RADIUS - 50) * cos(hourAngle);
  int hy = CENTER_Y + (RADIUS - 50) * sin(hourAngle);
  tft.drawLine(CENTER_X, CENTER_Y, hx, hy, TFT_RED);

  // Draw minute hand
  int mx = CENTER_X + (RADIUS - 30) * cos(minAngle);
  int my = CENTER_Y + (RADIUS - 30) * sin(minAngle);
  tft.drawLine(CENTER_X, CENTER_Y, mx, my, TFT_GREEN);

  // Draw second hand
  int sx = CENTER_X + (RADIUS - 20) * cos(secAngle);
  int sy = CENTER_Y + (RADIUS - 20) * sin(secAngle);
  tft.drawLine(CENTER_X, CENTER_Y, sx, sy, TFT_BLUE);
}