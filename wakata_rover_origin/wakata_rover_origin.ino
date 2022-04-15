#include "mecaunm.h"
#include "Adafruit_NeoPixel.h"

/*
 * 串口0用于打印测试数据，波特率115200
 * 串口2连接机械臂UART2，波特率115200
 * 串口3连接蓝牙，波特率115200
 */
uint16_t previousMillis = 0;   //存储上次更新RGB的时间
 
#define PIXEL_PIN    25  // RGB灯条连接的数字引脚
#define PIXEL_COUNT 8  // 灯珠数量

Adafruit_NeoPixel rgb(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);   //创建RGB灯对象

void setColor(uint8_t r,uint8_t g,uint8_t b)  //设置灯组全部灯珠颜色
{
  rgb.clear();
  for(int i = 0 ;i < 8; i++)
  {
    rgb.setPixelColor(i, rgb.Color(r,g,b));
    rgb.show();
  }
}
void colorF(uint8_t r,uint8_t g,uint8_t b, int wait)   //小车前进灯珠向两侧流水
{
  int i = 3;
  while(Serial3.read()>= 0){};
  while(1)
  {
    uint16_t currentMillis = millis();  //单片机运行以来经过的毫秒数
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
void colorB(uint8_t r,uint8_t g,uint8_t b,  int wait)   //小车后退红灯闪烁
{
  while(Serial3.read()>= 0){};
  int rgbStatus = 0;
  while(1)
  {
    uint16_t currentMillis = millis();  //单片机运行以来经过的毫秒数
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
void colorR(uint8_t r,uint8_t g,uint8_t b, int wait)  //小车右平移灯珠向右侧流水
{
  int i = 0;
  while(Serial3.read()>= 0){};
  while(1)
  {
    uint16_t currentMillis = millis();  //单片机运行以来经过的毫秒数
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
void colorL(uint8_t r,uint8_t g,uint8_t b, int wait)  //小车右平移灯珠向右侧流水
{
  int i = 7;
  while(Serial3.read()>= 0){};
  while(1)
  {
    uint16_t currentMillis = millis();  //单片机运行以来经过的毫秒数
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
    Serial3.begin(115200);   //蓝牙
    Serial2.begin(115200);  //机械臂
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
    while(Serial2.available()){ //打印机械臂返回数据
    uint8_t _receive = Serial2.read();
    Serial3.write(_receive);
  }
  UART_B(); //蓝牙接收
}
/**********************************************************************************************************/
uint8_t Car_en; 
uint8_t Car_data; 
void UART_B(){  //蓝牙3接收
  while(Serial3.available()){
    uint8_t _receive = Serial3.read();
    Serial.write(_receive);

    if(Car_en==1){
      if((_receive>=48)&&(_receive<=57)){
        Car_data = Car_data*10+(_receive-48);
      }
      else if(_receive == 0x0d){//回车指令
        Car_en=0;
        Car_do(); //底盘执行指令
      }
    }
    else if((_receive=='W')||(_receive=='w')){
      Car_en=1;     //下一条指令为运动代码
      Car_data=0;   //清除计算
    }
    else{ //转发
      Serial2.write(_receive);
    }
  }
}
void Car_do(void)     //小车动作指令
{
  rgb.clear();
  Serial.print("电机指令：");
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
