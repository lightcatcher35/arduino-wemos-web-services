#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
 
LiquidCrystal lcd(D9,D8,D5,D4,D3,D2);


char* ssid ="wifi_agi";
char* password="wifi_sifre";

boolean wifi_status=false;

String weather_api="http://api.openweathermap.org/data/2.5/";

boolean connect_wifi(char* username,char* pass)
{

  lcd.begin(16,2);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Aga Baglaniyor");
  
  delay(1000);
  Serial.println();
  Serial.print("Bağlanıyor...");
  Serial.println(username);

  WiFi.mode(WIFI_STA);
  WiFi.begin(username,pass);

  int try_count=0;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(username);
  lcd.setCursor(0,1);
  while(WiFi.status()!=WL_CONNECTED)
  {
    
    lcd.print(".");
    Serial.print(".");
    if(try_count>14) break;

    try_count++;

    delay(500);
  }

  if(WiFi.status()==WL_CONNECTED)
  {
    wifi_status=true;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wifi'ye baglandi");
    
    Serial.println("Wifi'ye bağlandı.");
    
    
  }else{
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wifi'ye baglanirken");
    lcd.setCursor(0,1);
    lcd.print("hata olustu.");
    
    Serial.println("Wifi'ye bağlanırken hata oluştu.");
  }

  
    return wifi_status;
}

String http_get_request(String host)
{

   WiFiClient client;
   HTTPClient http;

    const int httpPort=80;

    if(http.begin(client,host))
    {
      
      Serial.println("Http isteği gönderildi.");

      int httpCode = http.GET();

      if(httpCode>0)
      {
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
          {
            String payload = http.getString();

            return payload;
           
          }
        
      }else
      {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      
    }
    else
    {
      
      Serial.print("Http isteği gönderilemedi.");
    }

  
}



void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  connect_wifi(ssid,password);
  
  



}

void loop() {
  // put your main code here, to run repeatedly:




  if(wifi_status)
  {

      String payload=http_get_request(weather_api+"weather?q=izmir&appid=dea52beea184f7f0c99c3fea5787dd88&units=metric&lang=tr");

      
      Serial.println(payload);
    
      StaticJsonBuffer<2000> jsonBuffer;

      JsonObject& JsonRoot=jsonBuffer.parseObject(payload);

      if(JsonRoot.success())
      {
        String weather_desc=JsonRoot["weather"][0]["description"];
        float weather_C=JsonRoot["main"]["temp"];

        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(weather_desc);
        lcd.setCursor(0,1);
        lcd.print("hava "+String((int)weather_C)+" derece");
        
        Serial.println("hava durumu : "+weather_desc);
        
        Serial.println("hava "+String((int)weather_C)+" derece");

        
      }

    
    delay(10000);  
  }
  

}
