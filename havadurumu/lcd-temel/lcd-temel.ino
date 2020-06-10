#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
lcd.begin(16, 2);  
lcd.print("ilker ozer"); 
lcd.setCursor(0, 1);  
lcd.print("Test");

delay(5000); 
lcd.clear(); 
lcd.print("LCD DISPLAY"); 
}

void loop() {

}
