#include "mecaunm.h"
#include "Adafruit_NeoPixel.h"

/*
 * 串口0用於打印測試數據，baud: 115200
 * 串口2連接機械手臂UART2，baud: 115200
 * 串口3連接藍芽，baud: 115200
 */
uint16_t previousMillis = 0;   //存储上次更新RGB的时间
 
#define PIXEL_PIN    25  // RGB燈條連接的數字引腳
#define PIXEL_COUNT 8  // 燈珠數量

Adafruit_NeoPixel rgb(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);   // 創建RGB燈對象

void setColor(uint8_t r,uint8_t g,uint8_t b)  // 設置燈組全部燈珠顏色
{
  rgb.clear();
  for(int i = 0 ;i < 8; i++)
  {
    rgb.setPixelColor(i, rgb.Color(r,g,b));
    rgb.show();
  }
}
void colorF(uint8_t r,uint8_t g,uint8_t b, int wait)   // 小車前進燈珠兩側流水
{
  int i = 3;
  while(Serial3.read()>= 0){};
  while(1)
  {
    uint16_t currentMillis = millis();  // MCU運行以來經過之毫秒數
    if(currentMillis - previousMillis >= wait)
    {
      previousMillis = currentMillis;
      rgb.setPixelColor(i,r,g,b);
      rgb.setPixelColor(7-i,r,g,b);         
      rgb.show();
      i--;
    }
    if(i < 0){
      rgb.clear();
      i = 3;
    }
    if(Serial3.available())  break;
  }
}
void colorB(uint8_t r,uint8_t g,uint8_t b,  int wait)   // 小車後退紅燈閃爍
{
  while(Serial3.read()>= 0){};
  int rgbStatus = 0;
  while(1)
  {
    uint16_t currentMillis = millis();  // MCU運行以來經過之毫秒數
    if(currentMillis - previousMillis >= wait)
    {
      previousMillis = currentMillis;
      if(rgbStatus == 0)
      {
        for(int i = 0 ;i < 8; i++)
        {
          rgb.setPixelColor(i, rgb.Color(r,g,b));
          rgb.show();
        }
        rgbStatus = 1;
      }
      else
      {
        rgb.clear();
        rgb.show();
        rgbStatus = 0;
      }
    }
    if(Serial3.available())  break;
  }
}
void colorR(uint8_t r,uint8_t g,uint8_t b, int wait)  // 小車右平移燈珠向右側流水
{
  int i = 0;
  while(Serial3.read()>= 0){};
  while(1)
  {
    uint16_t currentMillis = millis();  // MCU運行以來經過之毫秒數
    if(currentMillis - previousMillis >= wait)
    {
      previousMillis = currentMillis;
      rgb.setPixelColor(i,r,g,b);         
      rgb.show();
      i++;
    }
    if(i == 8)
    {
      rgb.clear();
      i = 1;
    }
    if(Serial3.available())  break;
  }
}
void colorL(uint8_t r,uint8_t g,uint8_t b, int wait)  // 小車左平移燈珠向右側流水
{
  int i = 7;
  while(Serial3.read()>= 0){};
  while(1)
  {
    uint16_t currentMillis = millis();  // MCU運行以來經過之毫秒數
    if(currentMillis - previousMillis >= wait)
    {
      previousMillis = currentMillis;
      rgb.setPixelColor(i,r,g,b);         
      rgb.show();
      i--;
    }
    if(i < 0)
    {
      rgb.clear();
      i = 7;
    }
    if(Serial3.available())  break;
  }
}
/*************************************************************************************************************/
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial3.begin(115200);    //藍芽
    Serial2.begin(115200);    //機械臂
    Mecaunm_Pid_Init();
    Motor_Init();
    Encoder_Init();
    //    Set_Mecaunm_Position(1000,100);
    
    rgb.begin();
    rgb.clear();
    for(int i = 0 ;i < 8; i++)
    {
    rgb.setPixelColor(i, rgb.Color(0, 0, 255));
    rgb.show(); 
    delay(80);
    rgb.clear();
    }
    for(int i = 8 ;i > 0; i--)
    {
    rgb.setPixelColor(i, rgb.Color(0, 0, 255));
    rgb.show(); 
    delay(80);
    rgb.clear();
    }
    rgb.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial2.available()){ // 打印機械臂返回數據
    uint8_t _receive = Serial2.read();
    Serial3.write(_receive);
  }
  UART_B(); // 藍芽
}
/**********************************************************************************************************/
uint8_t Car_en; 
uint8_t Car_data; 
void UART_B(){  // 藍芽3接收
  while(Serial3.available()){
    uint8_t _receive = Serial3.read();
    Serial.write(_receive);

    if(Car_en==1){
      if((_receive>=48)&&(_receive<=57)){
        Car_data = Car_data*10+(_receive-48);
      }
      else if(_receive == 0x0d){// 回車指令
        Car_en=0;
        Car_do(); // 底盤執行指令
      }
    }
    else if((_receive=='W')||(_receive=='w')){
      Car_en=1;     // 下一條指令為運動代碼
      Car_data=0;   // 清除計算
    }
    else{ //转发
      Serial2.write(_receive);
    }
  }
}
void Car_do(void)     // 小車動作指令
{
  rgb.clear();
  Serial.print("指令");
  Serial.println(Car_data);
  switch(Car_data){
    case 0:   STOP();       setColor(255,0,0);       break;
    case 8:   ADVANCE();    colorF(0,0,255,200);     break;
    case 2:   BACK();       colorB(255,0,0,500);     break;
    case 4:   LEFT_2();     colorL(153,102,0,100);   break;
    case 6:   RIGHT_2();    colorR(153,102,0,100);   break;
    case 7:   LEFT_1();     colorL(153,102,0,100);   break;
    case 1:   LEFT_3();     colorL(153,102,0,100);   break;
    case 9:   RIGHT_1();    colorR(153,102,0,100);   break;
    case 3:   RIGHT_3();    colorR(153,102,0,100);   break;
    case 10:  CCW();        colorL(153,102,0,100);   break;
    case 11:  CW();         colorR(153,102,0,100);   break;
    default: break;
  }
}
