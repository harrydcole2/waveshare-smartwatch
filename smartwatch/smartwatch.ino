#include <Arduino.h>
#include "LCD_Test.h"

//screen size globals
UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5); // sda, scl, rst, irq

void setup() {
  //Serial printing is for the terminal
  Serial.begin(115200);
  touch.begin(); // init touch sensor

  //PSRAM Initialize; check if this component works
  if(paramInit()) {
    Serial.println("\nPSRAM is correctly initialized");
  } else {
    Serial.println("PSRAM not available");
  }
  if ((BlackImage = (UWORD *)ps_malloc(Imagesize)) == NULL) {
    Serial.println("Failed to apply for black memory...");
    exit(0);
  }

  if(DEV_Module_Init() != 0) {
    Serial.println("GPIO Init Fail");
  } else {
    Serial.println("GPIO Init successful!");
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);

    // 1. Create a new image cache named IMAGE_RGB and fill it with white
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // GUI init with different numbers
    Serial.println("drawing... \r\n");
    delay(2000);
    LCD_1IN28_Clear(RED);
    delay(2000);
    LCD_1IN28_Clear(GREEN);
    delay(2000);
    LCD_1IN28_Clear(BLUE);
    delay(2000);

    // 2. Drawing on the image
    #if 1
      Paint_Clear(WHITE);
      Paint_Drawpoint(50, 41, BLACK, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP);
      Paint_Drawpoint(50, 46, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
      Paint_Drawpoint(50, 51, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
      Paint_Drawpoint(50, 56, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
      Paint_Drawpoint(50, 61, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);

      Paint_DrawLine(60, 40, 90, 70, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
      Paint_DrawLine(60, 70, 90, 40, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

      Paint_DrawRectangle(60, 40, 90, 70, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
      Paint_DrawRectangle(100, 40, 130, 70, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

      Paint_DrawLine(135, 55, 165, 55, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
      Paint_DrawLine(150, 40, 150, 70, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTEN);

      Paint_DrawNum(50, 80, 9.87654321, &Font20, 3, WHITE, BLACK);
      Paint_DrawString_EN(50, 100, "ABC", &Font20, 0x000f, 0xfff0);
      Paint_DrawString_EN(50, 161, "Waveshare", &Font16, RED, WHITE);

      // 3. Refresh the picture in RAM to LCD
      LCD_1IN28_Display(BlackImage);
      DEV_Delay_ms(1000);
    #endif
  }

}

void loop() {
  delay(2); // allow the CPU to switch to other tasks

}
