
#include <ESP8266WiFi.h>


const char* ssid     = "wifi_agi";
const char* password = "wifi_sifre";

boolean wifi_status=false;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wifi modunu belirtip kullanıcı adı ve şifre ile giriş yapıyorum.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wifi'ye bağlanmazsa 15 saniye boyunca 
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

}

void loop() {
  // put your main code here, to run repeatedly:

}
