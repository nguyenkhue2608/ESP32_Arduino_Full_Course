#include <Arduino.h>
#include "DHT.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <string.h>
const char* ssid = "Nha Tao";
const char* password = "25251325" ;
#define DHTPIN 12     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
String UrlThingspeak = "https://api.thingspeak.com/update?api_key=J69MXGIE0KLMA27C";

String httpGETRequest(const char* Url);
void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx to Thingspeak!"));

  dht.begin();
    //setup wifi
  WiFi.begin(ssid,password);
  Serial.println("conecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Wait a few seconds between measurements.
  delay(10000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println(" %");
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(" oC");
  char para[50];
  sprintf(para,"&field1=%6.2f&field2=%6.2f",t,h);
  String Url = UrlThingspeak + String(para);
  httpGETRequest(Url.c_str());
}

String httpGETRequest(const char* Url)
{
  HTTPClient http;
  http.begin(Url);
  int responseCode = http.GET();
  String responseBody = "{}";
  if(responseCode > 0)
  {
    Serial.print("responseCode:");
    Serial.println(responseCode);
    responseBody = http.getString();
  }
  else 
  {
    Serial.print("Error Code: ");
    Serial.println(responseCode);
  }
  http.end();
  return responseBody;
}