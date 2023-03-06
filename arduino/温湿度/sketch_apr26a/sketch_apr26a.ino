//实验项目7-2 - 实时温湿度检测器
#include <dht11.h>
#include <Wire.h>
dht11 DHT;
float T0,T1,T2,T3,T4,Tp;//存储每个端口的温度值，TP为平均
float T,RH;//浮点型的温湿度值
int a,b,c,d,x;//串口屏不能直接显示浮点型，用于将温湿度值整数小数分开再显示
#define DHT11_PIN 4
void setup(){
  Serial.begin(9600); // 设置串口波特率9600
  //串口输出” Type, status, Humidity(%), Temperature(C)”
}


void loop(){
  int chk; //chk用于存储DHT11传感器的数据
  Serial.print("DHT11, \t");
  //读取DHT11传感器的数据
  chk = DHT.read(DHT11_PIN);
  switch (chk){
  case DHTLIB_OK:
    Serial.print("OK,\t");
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
  case DHTLIB_ERROR_TIMEOUT:
    Serial.print("Time out error,\t");
    break;
  default:
    Serial.print("Unknown error,\t");
    break;
  }
    T=DHT.humidity;
    RH=DHT.temperature;
    a=T;
    c=RH;
    T0 = T;//存储温度值
  //串口显示温湿度
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write("page2.t8.txt=\"");
  Serial.print(c);
  Serial.write("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(1000);
  Serial.write("page2.t6.txt=\"");
  Serial.print(a);
  Serial.write("\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(1000);
}
