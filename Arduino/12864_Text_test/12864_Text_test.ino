#include <U8g2lib.h>
#include <U8x8lib.h>

#include <Arduino.h>
#include <SPI.h>

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

int phototran = A1;//////////

void setup(void) {
  u8g2.begin();
}

void loop(void) {

  int sensorValue = analogRead(phototran);//////////
  
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_13_tf);
    //u8g2.drawStr(0,16,"Temp: 26.5C");
    //u8g2.drawStr(0,36,"Humidity: 85%");
    //u8g2.drawStr(0,56,"Light level: 250");
    //u8g2.setCursor(0,16);
    //u8g2.print("Temp: 26.5C");
    //Light level print
    u8g2.setCursor(0,56);
    u8g2.print("Light: ");
    u8g2.setCursor(44,56);
    u8g2.print(sensorValue);    
  } while ( u8g2.nextPage() );
  
  delay(300);
}
