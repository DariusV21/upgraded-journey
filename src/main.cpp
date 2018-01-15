#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Keyboard.h>

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




word ConvertRGB(byte R, byte G, byte B)
{
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}





char msg[10];
int z = 0;
bool readNextChar = false;

float oldValue = 0;
float newValue = 0;

int iteration = 0;
bool isGreen = false;



void writeBTC(){
  newValue = atof(msg); // array to float

  if (newValue != oldValue) {

  if (newValue > oldValue) {
    tft.setTextColor(ST7735_Green);
    isGreen = true;
  } else if (newValue < oldValue) {
    tft.setTextColor(ST7735_Red);
    isGreen = false;
  }

  tft.fillRect(0, 0, tft.width(), 40, ST7735_Black);
  tft.drawLine(0, 40, 128, 40, ST7735_Cyan);

  tft.setCursor(15, 20);
  tft.setTextSize(2);
  tft.print(newValue);

}
  oldValue = newValue;

}


void drawGraph() {

if (!isGreen) {
  tft.drawLine(iteration, 50, iteration, 70, ST7735_Red);
} else {
  tft.drawLine(iteration, 50, iteration, 70, ST7735_Green);
}

iteration ++;


if (iteration >= 128) {
  iteration = 0;
  tft.fillRect(0, 41, tft.width(), tft.height(), ST7735_Black);
}






} // drawGraphEND









void setup(void) {
  Serial.begin(9600);

  tft.init();   // initialize a ST7735S chip,
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  // word color = ST7735_White;
  //fillStack();

} // SETUP END

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


} // LOOP END
