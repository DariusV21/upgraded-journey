#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>

// set up pins we are going to use to talk to the screen
#define TFT_SCLK 13         // SPI clock (SCK)
#define TFT_MOSI 11         // SPI Data
#define TFT_CS   10         // Display enable (Chip select), if not enabled will not talk on SPI bus
#define TFT_RST   9         // Display reset pin, you can also connect this to the Arduino reset
                            // in which case, set this #define pin to -1!
#define TFT_DC     8        // register select (stands for Data Control perhaps!)

/*
LED -   3.3V
SCK -   13
SDA -   11
A0 -    8
RESET - 9
CS -    10
GND -   GND
VCC -   5V

*/

#define ST7735_Black           0x0000      /*   0,   0,   0 */
#define ST7735_Navy            0x000F      /*   0,   0, 128 */
#define ST7735_DarkGreen       0x03E0      /*   0, 128,   0 */
#define ST7735_DarkCyan        0x03EF      /*   0, 128, 128 */
#define ST7735_Maroon          0x7800      /* 128,   0,   0 */
#define ST7735_Purple          0x780F      /* 128,   0, 128 */
#define ST7735_Olive           0x7BE0      /* 128, 128,   0 */
#define ST7735_LightGrey       0xC618      /* 192, 192, 192 */
#define ST7735_DarkGrey        0x7BEF      /* 128, 128, 128 */
#define ST7735_Blue            0x001F      /*   0,   0, 255 */
#define ST7735_Green           0x07E0      /*   0, 255,   0 */
#define ST7735_Cyan            0x07FF      /*   0, 255, 255 */
#define ST7735_Red             0xF800      /* 255,   0,   0 */
#define ST7735_Magenta         0xF81F      /* 255,   0, 255 */
#define ST7735_Yellow          0xFFE0      /* 255, 255,   0 */
#define ST7735_White           0xFFFF      /* 255, 255, 255 */
#define ST7735_Orange          0xFD20      /* 255, 165,   0 */
#define ST7735_GreenYellow     0xAFE5      /* 173, 255,  47 */
#define ST7735_Pink            0xF81F

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

float p = 3.1415926;


void textOnScreen(char *text) {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1);
  tft.println(text);
  delay(1000);
}

void drawCircles(float lineWidth){
  tft.fillScreen(ST7735_BLACK);
  tft.drawCircle(tft.width()/2, tft.height()/2, 10, ST7735_GREEN);
  delay(1000);

  // for (float i = 0; i < lineWidth; i+= 0.5) {
  //   tft.drawCircle(32, 48, 20-i, ST7735_RED);
  //   tft.drawCircle(96, 48, 20-i, ST7735_RED);
  // }


  // tft.drawCircle(32, 48, 20, ST7735_RED);
  tft.fillCircle(32, 48, 20+(lineWidth/2), ST7735_RED);
  // tft.drawCircle(32, 48, 20-(lineWidth/2), ST7735_RED);
  tft.fillCircle(32, 48, 20-(lineWidth/2), ST7735_BLACK);

  tft.drawCircle(96, 48, 20, ST7735_RED);



  delay(5000);
}



void setup(void) {
  tft.init();   // initialize a ST7735S chip,
}

void loop() {
  textOnScreen("Platformio!");
  drawCircles(5);
}
