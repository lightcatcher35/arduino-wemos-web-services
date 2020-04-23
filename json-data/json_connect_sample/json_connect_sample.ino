
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "wifi_agi";
const char* password = "wifi_sifre";
boolean wifi_status=false;

const char* host = "api.openweathermap.org";

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
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {

      Serial.println("connection failed");
      return;
    }
    
    String url = "/data/2.5/weather?q=Izmir,TR&appid=5485a5c443e83636374329f55e49120d";

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
                 
    unsigned long timeout = millis();
    
    while (client.available() == 0) {
      if (millis() - timeout > 7000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    while (client.available())
    {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
