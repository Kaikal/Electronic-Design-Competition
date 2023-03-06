#include <Servo.h> // 声明调用Servo.h库
#include <dht11.h>
#include <Wire.h>
dht11 DHT;
float T0,T1,T2,T3,T4,Tp;//存储每个端口的温度值，TP为平均
float T,RH;//浮点型的温湿度值
int a,b,c,d,x;//串口屏不能直接显示浮点型，用于将温湿度值整数小数分开再显示
#define DHT11_PIN 4
Servo myserv; // 创建一个舵机对象
Servo myserv1; // 创建一个舵机对象
Servo myserv2; // 创建一个舵机对象
Servo myserv3; // 创建一个舵机对象
int pos = 180; // 变量pos用来存储舵机位置
int bpos=0,m=0;
char mode=0,inByte=0;
String temp="",flagNum1="";
int sersorValue=0;
int sersorPin=6;
int ledPin1 = 11,ledPin2 = 12,ledPin3 = 7,ledPin;     //定义指示灯的引脚
int fengPin=A3;
int flag=1;
const int sensorPin = A0; //定义人体红外传感器的引脚
int sensorValue = 0;      //声明传感器数据变量


void setup() {
  pinMode(sersorPin,INPUT);
  pinMode(13,OUTPUT);
  myserv2.attach(9); // 将引脚9上的舵机与声明的舵机对象连接起来, 对象名.函数名()；不要忘了中间的“.”
  myserv3.attach(10);
  myserv1.attach(8);
  Serial.begin(9600);
  myserv1.write(pos); // 给舵机写入角度
  myserv2.write(pos); 
  myserv3.write(pos); 
  pinMode(ledPin1,OUTPUT);
pinMode(ledPin2,OUTPUT);
pinMode(ledPin3,OUTPUT);
  pinMode(fengPin,OUTPUT);
  pinMode(sensorPin, INPUT);      //定义人体红外感应为输入
}


void HMI(){
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
    if(T>50){
      digitalWrite(fengPin,HIGH);
    }else{
      digitalWrite(fengPin,LOW);
    }
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


void DoorON(Servo myserv,int ledPin) {
digitalWrite(ledPin, HIGH);
for(pos = 180; pos >= 0; pos -= 2){ // 舵机从0°转到180°，每次增加1°
  myserv.write(pos); // 给舵机写入角度
  delay(15); // 延时15ms让舵机转到指定位置
}
}

void DoorOFF(Servo myserv,int ledPin) {
  myserv.write(180); // 写角度到舵机
  delay(15); // 延时15ms让舵机转到指定位置
 digitalWrite(ledPin, LOW);
}

void loop(){
  while (Serial.available()!=0) //判断串口是否有数据  
  {  
    inByte = Serial.read();//读取数据，串口一次只能读1个字符  
    temp += inByte;//写入缓存，  
                   //再次循环会判断写入是否成功  
   }  
   if(temp != "")   //判断临时变量是否为空  
   {
    if(temp.equals("1")){
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page1.t0.bco=33808");
    Serial.write("page1.t1.bco=65535");
    Serial.write("\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    flagNum1="1";
    }
   while(flagNum1.equals("1")){
   sensorValue = analogRead(sensorPin);   //读取传感器数据
   if(sensorValue > 650&&flag==1){                 //判断是否有人接近
    m=random(1,4);//产生随机数随机控制舵机
    switch(m){
      case 1:
        myserv=myserv1;
        ledPin=ledPin1;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t8.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(1000);
        break;
      case 2:
        myserv=myserv2;
        ledPin=ledPin2;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t6.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(1000);
        break;
      case 3:
        myserv=myserv3;
        ledPin=ledPin3;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t7.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(1000);
        break;
      } 
      m=0;
      temp=""; 
      inByte="";
      while (Serial.available()!=0) //判断串口是否有数据  
      {
    inByte = Serial.read();//读取数据，串口一次只能读1个字符  
    temp += inByte;//写入缓存，  
                   //再次循环会判断写入是否成功  
   } if(temp != "")   //判断临时变量是否为空  
   {
      if(temp.equals("-1")){
       DoorOFF(myserv1,ledPin1);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t8.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv2,ledPin2);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t6.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv3,ledPin3);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t7.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write("page1.t0.bco=33808");
      Serial.write("page1.t1.bco=65535");
      Serial.write("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      flagNum1="0";
      flag=1;
      break;}
   }delay(5000);
  }else{
    DoorOFF(myserv1,ledPin1);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t8.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv2,ledPin2);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t6.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv3,ledPin3);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t7.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    flag=1;
    while (Serial.available()!=0) //判断串口是否有数据  
      {
    inByte = Serial.read();//读取数据，串口一次只能读1个字符  
    temp += inByte;//写入缓存，  
                   //再次循环会判断写入是否成功  
   } if(temp != "")   //判断临时变量是否为空  
   {
      if(temp.equals("-1")){
       DoorOFF(myserv1,ledPin1);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t8.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv2,ledPin2);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t6.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv3,ledPin3);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t7.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write("page1.t0.bco=33808");
      Serial.write("page1.t1.bco=65535");
      Serial.write("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      flagNum1="0";
      flag=1;
      break;}
      if(temp.equals("open01")){
    if(flagNum1="1"){
      myserv=myserv1;
        ledPin=ledPin1;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t8.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(1000);myserv=myserv1;
        ledPin=ledPin1;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t8.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
   }
   if(temp.equals("open02")){
    if(flagNum1="1"){
      myserv=myserv2;
        ledPin=ledPin2;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t6.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
   }
   if(temp.equals("open03")){
    if(flagNum1="1"){
      myserv=myserv3;
        ledPin=ledPin3;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t7.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
   }
   if(temp.equals("speakOFF")){
      DoorOFF(myserv1,ledPin1);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t8.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv2,ledPin2);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t6.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv3,ledPin3);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t7.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write("page1.t0.bco=33808");
      Serial.write("page1.t1.bco=65535");
      Serial.write("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      flag=1;
   }
   if(temp.equals("openFeng")){
      digitalWrite(fengPin,HIGH);
   }
   if(temp.equals("OFFFeng")){
      digitalWrite(fengPin,LOW);
   }
   }
  }
   }
   if(temp.equals("on")){
    while(1){
      HMI();
      if(temp.equals("off")){
        break;
      }
      }
   }
   if(temp.equals("open01")){
    if(flag==1){
      myserv=myserv1;
        ledPin=ledPin1;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t8.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(1000);myserv=myserv1;
        ledPin=ledPin1;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t8.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
   }
   if(temp.equals("open02")){
    if(flag==1){
      myserv=myserv2;
        ledPin=ledPin2;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t6.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
   }
   if(temp.equals("open03")){
    if(flag==1){
      myserv=myserv3;
        ledPin=ledPin3;
        DoorON(myserv,ledPin);
        flag=0;
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write("page0.t7.txt=\"开\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
   }
   if(temp.equals("speakOFF")){
      DoorOFF(myserv1,ledPin1);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t8.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv2,ledPin2);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t6.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    DoorOFF(myserv3,ledPin3);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page0.t7.txt=\"关\"");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write("page1.t0.bco=33808");
      Serial.write("page1.t1.bco=65535");
      Serial.write("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      flag=1;
   }
   if(temp.equals("openFeng")){
      digitalWrite(fengPin,HIGH);
   }
   if(temp.equals("OFFFeng")){
      digitalWrite(fengPin,LOW);
   }
   }
  temp = "";//清空变量
  //myservo.write(angle);  //控制舵机转动相应的角度。这里不要超多舵机的最大角度，有的舵机是60度，也有360度的舵机  
  delay(50);//延时50ms，这里的延时并不影响舵机的速度，只是限制你下一次输入的间隔 
}
