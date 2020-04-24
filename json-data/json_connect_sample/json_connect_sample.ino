
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid     = "wifi_agi";
const char* password = "wifi_sifre";
boolean wifi_status=false;

const char* host = "http://jsonplaceholder.typicode.com/posts/1";

boolean connect_wifi()
{
  
}
void setup()
{
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  

  // Wifi modunu belirtip kullanıcı adı ve şifre ile giriş yapıyorum.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wifi'ye bağlanmazsa 15 saniye boyunca dene ve bitir
  int try_count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    
    if (try_count > 15)
      break;

    try_count++;
    delay(500);
  }

  
  if (WiFi.status()==WL_CONNECTED)
  {
    wifi_status = true;
    Serial.println("İnternete bağlandı.");
    Serial.println("Wifi Status : "+String(wifi_status));
    
  } else  Serial.println("İnternete bağlanamadı."); 

  if(wifi_status)
  {

    WiFiClient client;
    HTTPClient http;
    
    const int httpPort = 80;

    
    if(http.begin(client,host))
    {
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0)
      {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          String payload = http.getString();
          Serial.println(payload);

          StaticJsonBuffer<1000> jsonBuffer;
          JsonObject& jsonRoot = jsonBuffer.parseObject(payload);

          if (jsonRoot.success())
          {
            String veri = jsonRoot["userId"];

            Serial.println(veri);
            
            Serial.println(jsonRoot["title"].asString());
          }else
          {
              Serial.println(">>> Client Timeout !");
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
