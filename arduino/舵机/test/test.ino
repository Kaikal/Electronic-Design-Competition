#include <Servo.h> // 声明调用Servo.h库
Servo myserv1; // 创建一个舵机对象
Servo myserv2; // 创建一个舵机对象
Servo myserv3; // 创建一个舵机对象
Servo myserv;
int pos = 0; // 变量pos用来存储舵机位置
int m=0;
int ledPin1 = 11;
int ledPin2 = 12;
int ledPin3 = 7;
int ledPin;
void setup() {
myserv1.attach(8); // 将引脚9上的舵机与声明的舵机对象连接起来, 对象名.函数名()；不要忘了中间的“.”
myserv2.attach(9);
myserv3.attach(10);
Serial.begin(9600);
myserv1.write(pos); // 给舵机写入角度
myserv2.write(pos); 
myserv3.write(pos); 
pinMode(ledPin1,OUTPUT);
pinMode(ledPin2,OUTPUT);
pinMode(ledPin3,OUTPUT);
}

void Door(Servo myserv,int ledPin) {
  digitalWrite(ledPin, HIGH);
for(pos = 0; pos <= 180; pos += 2){ // 舵机从0°转到180°，每次增加1°
  myserv.write(pos); // 给舵机写入角度
  delay(15); // 延时15ms让舵机转到指定位置
}
for(pos = 180; pos>=1; pos-=2) { // 舵机从180°转回到0°，每次减小1°
  myserv.write(pos); // 写角度到舵机
  delay(15); // 延时15ms让舵机转到指定位置
  }
 digitalWrite(ledPin, LOW);
}

void loop() {
m=random(1,4);
Serial.println(m);
switch(m){
      case 1:
        myserv=myserv1;
        ledPin=ledPin1;
        Door(myserv,ledPin);
        delay(1000);
        break;
      case 2:
        myserv=myserv2;
        ledPin=ledPin2;
        Door(myserv,ledPin);
        delay(1000);
        break;
      case 3:
        myserv=myserv3;
        ledPin=ledPin3;
        Door(myserv,ledPin);
        delay(1000);
        break;
    }
}
