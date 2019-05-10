#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SimpleDHT.h>

#define pinDHT11  D1
SimpleDHT11 dht11(pinDHT11);

const char* ssid = "Lol";
const char* password = "arya12345";

String apiKey = "V5ERXL36WM9Z13QU";

///GEThttps://api.thingspeak.com/update?api_key=V5ERXL36WM9Z13QU&field1=0

int t = 0;

void setup () {

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }
  Serial.println("Wifi Connected");

}

void loop() {

  Serial.println("Started Sending");
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
      return;
    }

    HTTPClient http;  //Declare an object of class HTTPClient

    String url = "http://api.thingspeak.com/update?api_key=" + apiKey + "&field1=" + temperature;
    Serial.println(url);

    http.begin(url);

    //http2.setTimeout(500);
    //http2.addHeader("Content-Type", "application/json");  //Specify content-type header

    int httpCode = http.GET();                                                                  //Send the request

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection
  }
  Serial.println("Waiting");
  t++;
  if (t > 180)
    t = 0;
  delay(15000);    //Send a request every 30 seconds
}
