#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Keyboard.h>
#include <StackArray.h>

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



word ConvertRGB(byte R, byte G, byte B)
{
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}

void textOnScreen(char *text) {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 30);
  tft.setTextColor(ConvertRGB(0, 153, 255));
  tft.setTextSize(1);
  tft.println(text);
  delay(500);
}


void drawCircle(float lineWidth, word lineColor){
  word backgroundColor = ConvertRGB(0, 0, 0);
  tft.fillScreen(backgroundColor);
  // tft.drawCircle(tft.width()/2, tft.height()/2, 10, lineColor);
  // delay(1000);
  tft.fillCircle(32, 48, 20+(lineWidth/2), lineColor);
  tft.fillCircle(32, 48, 20-(lineWidth/2), backgroundColor);
  // tft.drawCircle(96, 48, 20, lineColor);
  delay(1000);
}

void drawRoundRectangle(float x0, float y0, uint16_t w, uint16_t h, uint16_t radius,
    float lineWidth, uint16_t color){
      word backgroundColor = ConvertRGB(0, 0, 0);
      tft.fillScreen(backgroundColor);
      tft.fillRoundRect(x0-(lineWidth/2), y0-(lineWidth/2), w+lineWidth, h+lineWidth, radius+lineWidth, color);
      tft.fillRoundRect(x0+(lineWidth/2), y0+(lineWidth/2), w-lineWidth, h-lineWidth, radius-lineWidth, backgroundColor);
      tft.drawRoundRect(10, 60, 100, 50, 10, ConvertRGB(0, 153, 255));
      delay(1000);
}


void slidingColor(){
  tft.fillScreen(ST7735_BLACK);
for (byte posY = 0; posY < 128; posY++) {
  for (byte posX = 0; posX < 128; posX++) {
    tft.drawPixel(posX, posY, ST7735_WHITE);
  }
}
for (byte posY = 0; posY < 128; posY++) {
  for (byte posX = 0; posX < 128; posX++) {
    tft.drawPixel(posX, posY, ST7735_BLACK);
  }
}

  // for (byte r = 0; r < 255; r++) {
  //   for (byte g = 0; g < 255; g++) {
  //     for (byte b = 0; b < 255; b++) {
  //       // tft.fillScreen(ConvertRGB(r, g, b));
  //       tft.drawPixel(r/2, r/2, (ConvertRGB(r, g, b)));
  //     }
  //   }
  // }
}

void colorTest1(){
  for (byte posY = 0; posY < 128; posY++) {
    for (byte posX = 0; posX < 128; posX++) {
      if (posX == 64) {
        tft.drawPixel(posX, posY, ST7735_GREEN);
      } else {
        tft.drawPixel(posX, posY, ConvertRGB(posX*2, posY*2, posY*2));
      }

    }
  }
  delay(3000);
}
void colorTest2(){
  for (byte posY = 0; posY < 128; posY++) {
    for (byte posX = 0; posX < 128; posX++) {
      if (posY == 64) {
        tft.drawPixel(posX, posY, ST7735_RED);
      } else {
        tft.drawPixel(posX, posY, ConvertRGB(posX*2, posX*2, posY*2));
      }
    }
  }
  delay(3000);
}
void colorTest3(){
  for (byte posY = 0; posY < 128; posY++) {
    for (byte posX = 0; posX < 128; posX++) {
      if (posX == 64) {
        tft.drawPixel(64, posY, ST7735_BLUE);
      } else {
        tft.drawPixel(posX, posY, ConvertRGB(posX*2, posY*2, posX*2));
      }
      if (posY == 64) {
        tft.drawPixel(posX, 64, ST7735_BLUE);
      }
    }
  }
  delay(3000);
}
void colorTest4(){
  for (byte posY = 0; posY < 128; posY++) {
    for (byte posX = 0; posX < 128; posX++) {

      tft.drawPixel(posX, posY, ConvertRGB(posY*2, posY*2, posY*2));
    }
  }
  delay(3000);
}


// drawEye(x,y){
//   byte nX = x
//   drawRoundRectangle(10, 0, 100, 50, 10, 4, ConvertRGB(0, 153, 255));
// }


char msg[10];
int z = 0;
bool readNextChar = false;

float oldValue = 0;
float newValue = 0;
int graphData[128];
int graphX = 0;
char color;

void writeBTC(){
  // tft.fillScreen(ST7735_Black);
  // tft.fillRect(0, 0, tft.width(), 40, ST7735_Black);
  // tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);

  newValue = atof(msg); // array to


  if (newValue > oldValue) {
    // tft.fillRect(0, 0, tft.width(), 40, ST7735_Green);
    color = ST7735_Green;
    tft.setTextColor(ST7735_Green);
  } else if (newValue < oldValue) {
    // tft.fillRect(0, 0, tft.width(), 40, ST7735_Red);
    color = ST7735_Red;
    tft.setTextColor(ST7735_Red);
  }
  // tft.setTextColor(color);
  tft.fillRect(0, 0, tft.width(), 40, ST7735_Black);
  tft.drawLine(0, 40, 128, 40, ST7735_Cyan);
  // tft.setTextColor(ST7735_White);
  tft.setCursor(15, 20);
  tft.setTextSize(2);
  tft.print(newValue);

  oldValue = newValue;

}


void drawGraph() {
    // 0, 44 -> 128,124
     int mapY = map(newValue, 13000, 15000, 44, 124);

    tft.drawPixel(graphX, mapY, ST7735_White);
    graphX++;

    if (graphX >= 128) {
      graphX = 0;
    }



}

// bool compare(char message){
//   // for (size_t i = 0; i < message.length; i++) {
//     float newFloat = atof(message);
//   // }
//
//
//
// }





void setup(void) {
  Serial.begin(9600);

  tft.init();   // initialize a ST7735S chip,
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  // word color = ST7735_White;

}

void loop() {

  while (Serial.available() > 0) {
    char c = Serial.read();
    int i = (int)c;


    if (i == 36) { // $
      readNextChar = true;
    } else if (i == 37) { // %
        readNextChar = false;
        z = 0;
        writeBTC();
        drawGraph();
        Serial.print(msg);
    } else if (readNextChar) {
        msg[z] = c;
        z++;
        if (z >= 10) z = 0;
    }

  }







    // if(i == 36) { //$
    //   tft.fillScreen(ST7735_Black);
    //   tft.setTextColor(ST7735_White);
    //   tft.setCursor(10, 25);
    //   tft.setTextSize(2);
    // } else {
    //   Serial.print(c);
    //   tft.print(c);
    // }
    // if(i == 37) { //%
    // tft.setTextColor(ST7735_Green);
    // }
    // if(i == 51) {
    // tft.setTextColor(ST7735_White);
    // }




    // if(i == 48) {
    //   Serial.println("REFRESH");
    //   tft.fillScreen(ST7735_BLACK);
    //   tft.setCursor(0, 0);
    // } else {
    //   Serial.print(c);
    //   tft.print(c);
    // }




  // textOnScreen("Platformio!");
  // drawCircle(5, ConvertRGB(0, 153, 255));
  // drawRoundRectangle(10, 0, 100, 50, 10, 4, ConvertRGB(0, 153, 255));
  // slidingColor();
  // colorTest1();
  // colorTest2();
  // colorTest3();
  // colorTest4();

}
