#include "OneWire.h"
#include "DallasTemperature.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

OneWire oneWire(13);
DallasTemperature tempSensor(&oneWire);

const char *ssid = "Hwan";
const char *password = "------"; //password

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  tempSensor.begin();
  
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP(ssid, password);

}

int j=0;

void loop() {
  // put your main code here, to run repeatedly:

  tempSensor.requestTemperaturesByIndex(0);

  float temp = tempSensor.getTempCByIndex(0);
  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
      // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        j++;
        
        String temp_str = String(temp);
        String seq_str = String(j);
        String geturl = "http://ec2-34-229-114-134.compute-1.amazonaws.com:8080/temp_sample?device_id=20&temperature_value=";
        geturl += temp_str;
        geturl += "&sequence_number=";
        geturl += seq_str;
        
        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin(geturl); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(60000);
}
