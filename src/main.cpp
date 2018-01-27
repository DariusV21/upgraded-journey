// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
//
// This example shows how to deserialize a JSON document with ArduinoJson.
#include <Arduino.h>
#include <ArduinoJson.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int itteration = 0;
// float prc;


byte btcChar[8] = {
  B01010,
    B11110,
    B10001,
    B11110,
    B10001,
    B10001,
    B11110,
    B01010
};




void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Initialize serial port
  Serial.begin(9600);


  lcd.createChar(0, btcChar);





}

void loop() {

  // This line is useless on UNO
  //while (!Serial) continue;

  // Memory pool for JSON object tree.
  //
  // Inside the brackets, 200 is the size of the pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  const size_t bufferSize = JSON_OBJECT_SIZE(3) + 50;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  // StaticJsonBuffer allocates memory on the stack, it can be
  // replaced by DynamicJsonBuffer which allocates in the heap.
  //
  // DynamicJsonBuffer  jsonBuffer(200);

  // JSON input string.
  //
  // It's better to use a char[] as shown here.
  // If you use a const char* or a String, ArduinoJson will
  // have to make a copy of the input in the JsonBuffer.
  //char json[] = "{\"price\":11200.34,\"percentage\":12.34,\"time\":20}";

  // Root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.parseObject(Serial);



  // Test if parsing succeeds.
  if (!root.success()) {
    //Serial.println("parseObject() failed");
    // lcd.clear();
    // lcd.write("parse failed");
    return;
  } else {
    // Fetch values.
    //
    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do root["time"].as<long>();
    float price = root["price"]; // 11200.34
    float percentage = root["percentage"]; // 12.34
    int time = root["time"]; // 20

    // Print values.
    lcd.clear();
    //Serial.println(price);
    //Serial.println(percentage);
    //Serial.println(time);
    lcd.setCursor(0, 0);
    lcd.write(byte(0)); // Bitcoin Symbol
    lcd.print(" = ");
    lcd.print(price);
    lcd.print(" USD");
    lcd.setCursor(0, 1);
    lcd.print(percentage);
    lcd.print("%");
    lcd.setCursor(12, 1);
    lcd.print(time);
  }



  // not used in this example

// Serial.println("Itteration:");
// Serial.print(itteration);


// const size_t bufferSize = JSON_OBJECT_SIZE(3) + 50;
// DynamicJsonBuffer jsonBuffer(bufferSize);
//
// JsonObject& dataGet = jsonBuffer.createObject();
//
//
// dataGet["price"] = random(11000.00, 15000.00);
// dataGet["percentage"] = 12.34;
// dataGet["time"] = itteration;
//
// dataGet.printTo(Serial);
// itteration += 1;
// Serial.println();



}

// See also
// --------
//
// The website arduinojson.org contains the documentation for all the functions
// used above. It also includes an FAQ that will help you solve any
// deserialization problem.
// Please check it out at: https://arduinojson.org/
//
// The book "Mastering ArduinoJson" contains a tutorial on deserialization.
// It begins with a simple example, like the one above, and then adds more
// features like deserializing directly from a file or an HTTP request.
// Please check it out at: https://arduinojson.org/book/
