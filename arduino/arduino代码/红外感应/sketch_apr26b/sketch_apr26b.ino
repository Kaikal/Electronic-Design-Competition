const int sensorPin = A0; //定义人体红外传感器的引脚
const int ledPin = 10;    //定义LED灯的引脚
int sensorValue = 0;      //声明传感器数据变量
#include <Servo.h>

Servo myservo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量
int val;
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);  
  pinMode(sensorPin, INPUT);  
  myservo.attach(9); 
}
 
void loop()
{
  sensorValue = analogRead(sensorPin);   //读取传感器数据
  Serial.println(sensorValue);
  if(sensorValue > 650){                 //判断是否有人接近
      digitalWrite(ledPin,HIGH);         //点亮LED灯
      pos = pos +1;
      if(pos >= 90){
        pos = 90;
        }
     myservo.write(pos); //写入舵机的角度
  }else{
    digitalWrite(ledPin,LOW);          //关闭LED灯
    pos = pos -1;
    if(pos <= 0){
      pos = 0;
      }
    myservo.write(pos); //写入舵机的角度
    
  }
}
