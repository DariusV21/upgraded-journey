// Libraries
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>

#define CONNECTED_TO_PC false



//// WiFi settings
const char* ssid     = "ssid"; //
const char* password = "pswrd"; //

// API server
const char* host = "api.coindesk.com";

uint16_t tm = 0;


void setup() {

  //Serial
  Serial.begin(9600);
  delay(10);



  // We start by connecting to a WiFi network
  if (CONNECTED_TO_PC) {
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (CONNECTED_TO_PC) Serial.print(".");
  }

  if (CONNECTED_TO_PC) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }



  
}

void loop() {

  // Connect to API
  if (CONNECTED_TO_PC) Serial.print("connecting to ");
  if (CONNECTED_TO_PC) Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    if (CONNECTED_TO_PC) Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/v1/bpi/currentprice.json";
  String historical_URL = "/v1/bpi/historical/close.json?for=yesterday";

  if (CONNECTED_TO_PC) Serial.print("Requesting URL: ");
  if (CONNECTED_TO_PC) Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(100);

  // Read all the lines of the reply from server and print them to Serial
  String answer;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    answer += line;
  }


  client.stop();
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("closing connection");


  ////////////// YESTERDAY

  // Connect to API
  if (CONNECTED_TO_PC) Serial.print("connecting to ");
  if (CONNECTED_TO_PC) Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client1;
  //const int httpPort = 80;
  if (!client1.connect(host, httpPort)) {
    if (CONNECTED_TO_PC) Serial.println("connection failed");
    return;
  }


  // This will send the request to the server ABOUT YESTERDAYS PRICE
  client1.print(String("GET ") + historical_URL + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
  delay(100);

  // Read all the lines of the reply from server and print them to Serial
  String yesterday_answer;
  while (client1.available()) {
    String yesterday_line = client1.readStringUntil('\r');
    yesterday_answer += yesterday_line;
  }

  client1.stop();
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("closing connection");

  // Process answer
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("Answer: ");
  if (CONNECTED_TO_PC) Serial.println(answer);

  // Process answer
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("Yesterday answer: ");
  if (CONNECTED_TO_PC) Serial.println(yesterday_answer);

  // Convert to JSON
  String jsonAnswer;
  int jsonIndex;

  String jsonYAnswer;
  int jsonYIndex;

  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '{') {
      jsonIndex = i;
      break;
    }
  }

  for (int i = 0; i < yesterday_answer.length(); i++) {
    if (yesterday_answer[i] == '{') {
      jsonYIndex = i;
      break;
    }
  }

  // Get JSON data
  jsonAnswer = answer.substring(jsonIndex);
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("JSON answer: ");
  if (CONNECTED_TO_PC) Serial.println(jsonAnswer);
  jsonAnswer.trim();

  // Get YJSON data
  jsonYAnswer = yesterday_answer.substring(jsonYIndex);
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("JSON yesterday answer: ");
  if (CONNECTED_TO_PC) Serial.println(jsonYAnswer);
  jsonYAnswer.trim();

  // Get rate as float
  int rateIndex = jsonAnswer.indexOf("rate_float");
  String priceString = jsonAnswer.substring(rateIndex + 12, rateIndex + 18);
  priceString.trim();
  float price = priceString.toFloat();

  // Get rate as float
  int rateYIndex = jsonYAnswer.indexOf("bpi");
  String priceYString = jsonYAnswer.substring(rateYIndex + 19, rateYIndex + 26);
  priceYString.trim();
  float priceY = priceYString.toFloat();


  // Print price
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("Bitcoin price: ");
  if (!CONNECTED_TO_PC) Serial.print("$");
  //Serial.print(price);
  if (!CONNECTED_TO_PC) Serial.print("%");

  // Print yesterdays price
  if (CONNECTED_TO_PC) Serial.println();
  if (CONNECTED_TO_PC) Serial.println("Yesterdays Bitcoin price: ");
  if (CONNECTED_TO_PC) Serial.print(priceY);
  float perc = -(100-(price/priceY)*100);


  if (CONNECTED_TO_PC) Serial.println("Change in percentage: ");
  if (CONNECTED_TO_PC) Serial.print(perc);







const size_t bufferSize = JSON_OBJECT_SIZE(3);
DynamicJsonBuffer jsonBuffer(bufferSize);

JsonObject& root = jsonBuffer.createObject();
root["price"] = price;
root["percentage"] = perc;
root["time"] = tm;

root.printTo(Serial);

    delay(2000);

    tm += 1;


  // Wait 30 seconds
  
}


