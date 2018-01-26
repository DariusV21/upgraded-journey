#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Keyboard.h>

#include <PacketSerial.h>

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

PacketSerial serial_Price;
PacketSerial serial_Time;

// Function to convert RGB color to this... sh!t.
word ConvertRGB(byte R, byte G, byte B) {
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}





char msg[10];
char msgP[10];
char msgT[5];
int z = 0;
int p = 0;
int t = 0;
bool readNextChar = false;
bool readPercChar = false;
bool readTimeChar = false;

float newValue = 0;
float oldValue = 0;

float perc = 0.0;
bool isPositive = false;
int timeLine = 0;



void drawTriangle() {
  //tft.fillRect(0, 41, 128, 128, ST7735_Black);
  perc = atof(msgP);
  if (perc > 0) {
    isPositive = true;
  } else {
    isPositive = false;
  }

  if (isPositive){
    tft.fillTriangle(64, 52, 49, 82, 79, 82, ST7735_GREEN);
    tft.setTextSize(2);
    tft.setCursor(20, 100);
    tft.setTextColor(ST7735_GREEN);
    tft.print("+");
    tft.print(perc);
    tft.print(" %");
  } else {
    tft.fillTriangle(64, 82, 49, 52, 79, 52, ST7735_RED);
    tft.setTextSize(2);
    tft.setCursor(20, 100);
    tft.setTextColor(ST7735_RED);
    tft.print(perc);
    tft.print(" %");
  }
}


void flashOnChange(bool green) {
  if (green) {
    for (size_t i = 250; i > 0; i-=25) {
      tft.fillScreen(ConvertRGB(0, i, 0));
      //delay(1);
    }
  } else {
    for (size_t i = 250; i > 0; i-=25) {
      tft.fillScreen(ConvertRGB(i, 0, 0));
      //delay(1);
    }
  }


}

void waitingLine() {
  timeLine = atoi(msgT); // array to float

  // tft.fillRect(0, 40, 30, 60, ST7735_Black);
  // tft.setCursor(0, 40);
  // tft.setTextSize(1);
  // tft.print(timeLine);

  tft.drawLine(0, 127, timeLine*4+4, 127, ST7735_LightGrey);

}



void writeBTC(){
  newValue = atof(msg); // array to float

if (newValue != oldValue) {
  if (newValue > oldValue) {
    flashOnChange(true);
  } else {
    flashOnChange(false);
  }

  if (isPositive) {
    tft.setTextColor(ST7735_GREEN);
  } else {
    tft.setTextColor(ST7735_RED);
  }

  //tft.fillRect(0, 0, tft.width(), 40, ST7735_Black);
  // tft.drawLine(0, 40, 128, 40, ST7735_Cyan);

  tft.setCursor(15, 15);
  tft.setTextSize(2);
  tft.print(newValue);
}

  tft.fillRect(0, 126, tft.width(), tft.height(), ST7735_Black);
  oldValue = newValue;

} // writeBTC END

// This is our handler callback function.
// When an encoded packet is received and decoded, it will be delivered here.
// The `buffer` is a pointer to the decoded byte array. `size` is the number of
// bytes in the `buffer`.


// Man reikia persiusti kas 30sek: CurrentPrice, YesterdayPrice
// Kas 1sek: TimeLeft
// BUFFER = []

void onPriceReceived(const uint8_t* buffer, size_t size) {
      tft.setTextColor(ST7735_GREEN);
        tft.fillRect(0, 0, tft.width(), 80, ST7735_Black);
       tft.setCursor(0, 0);
       tft.setTextSize(1);
       tft.print(buffer[0]);
       tft.setCursor(0, 15);
       tft.setTextSize(1);
       tft.print(buffer[1]);

} // onPriceReceived function END

   void onTimeReceived(const uint8_t* buffer, size_t size) {

     // if (sender == &serial_Price) {
     //      // Do something with the packet from myPacketSerial.

      //     tft.setCursor(0, 0);
      //     tft.setTextSize(1);
      //     tft.print(buffer[0]);
      //     tft.setCursor(0, 15);
      //     tft.setTextSize(1);
      //     tft.print(buffer[1]);
      // }
      // else if (sender == &serial_Time) {
          // Do something with the packet from myOtherPacketSerial.
          tft.fillRect(0, 90, tft.width(), tft.height(), ST7735_Black);
          tft.setTextColor(ST7735_GREEN);
          tft.setCursor(0, 100);
          tft.setTextSize(1);
          tft.print(buffer[0]);
      // }
   } // onTimeReceived function END

  // // Make a temporary buffer.
  // uint8_t tempBuffer[size];
  //
  // // Copy the packet into our temporary buffer.
  // memcpy(tempBuffer, buffer, size);
  //
  //
  // if (tempBuffer[17] == true) {
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   delay(1000);
  // } else if (tempBuffer[17] == false){
  //   digitalWrite(LED_BUILTIN, LOW);
  //   delay(1000);
  // }












void setup(void) {

  serial_Price.begin(9600);
  serial_Price.setPacketHandler(&onPriceReceived);

  serial_Time.begin(115200);
  serial_Time.setPacketHandler(&onTimeReceived);

  //Serial.begin(115200);

  tft.init();   // initialize a ST7735S chip,
  tft.setRotation(1);
  tft.fillScreen(ST7735_GreenYellow);
  // word color = ST7735_White;
  //fillStack();

} // SETUP END

void loop() {
  //tft.fillScreen(ST7735_BLACK);


  serial_Price.update();
  serial_Time.update();



  delay(1000);


  // tft.setCursor(15, 15);
  // tft.setTextColor(ST7735_GREEN);
  // tft.setTextSize(1);
  // tft.print("Waiting for server data");
  //
  // while (Serial.available() > 0) {
  //   char c = Serial.read();
  //   Serial.print(c);
  //   int i = (int)c;
  //
  //
  //   if (readNextChar) {
  //       msg[z] = c;
  //       z++;
  //       if (z >= 10) z = 0;
  //   }
  //
  //   if (readPercChar) {
  //       msgP[p] = c;
  //       p++;
  //       if (p >= 10) p = 0;
  //   }
  //
  //   if (readTimeChar) {
  //       msgT[t] = c;
  //       t++;
  //       if (t >= 8) t = 0;
  //   }
  //
  //   if (i == 36) { // $
  //     readNextChar = true;
  //   } else if (i == 37) { // %
  //       readNextChar = false;
  //       z = 0;
  //       writeBTC();
  //   }
  //
  //   if (i == 38) { // &
  //     readPercChar = true;
  //   } else if (i == 42) { // *
  //       readPercChar = false;
  //       p = 0;
  //       drawTriangle();
  //       timeLine = 0;
  //   }
  //
  //   if (i == 64) { // @
  //     readTimeChar = true;
  //   } else if (i == 35) { // #
  //       readTimeChar = false;
  //       t = 0;
  //       waitingLine();
  //   }
  //
  //
  // } // Serial available END
} // LOOP END
