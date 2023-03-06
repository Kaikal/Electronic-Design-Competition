#include <Servo.h> // 声明调用Servo.h库

Servo myservo; // 创建一个舵机对象
Servo myserv1; // 创建一个舵机对象

int pos = 0; // 变量pos用来存储舵机位置
int bpos=0;
char mode=0;
String temp="close";
void setup() {
myservo.attach(9); // 将引脚9上的舵机与声明的舵机对象连接起来, 对象名.函数名()；不要忘了中间的“.”
//myserv1.attach(10);
Serial.begin(9600);
}

void loop() {
if(Serial.available()>0)
  {
    mode=Serial.read();
    Serial.print(mode);
    temp += mode;//写入缓存，  
                   //再次循环会判断写入是否成功 
  }
if(temp=="open"){
for(pos=0; pos < 180; pos += 1){ // 舵机从0°转到180°，每次增加1°
myservo.write(pos); // 给舵机写入角度
delay(15); // 延时15ms让舵机转到指定位置
break;
}
temp="";
}
if(temp="close"){
for(pos=180; pos>=1; pos-=1) { // 舵机从180°转回到0°，每次减小1°
myservo.write(pos); // 写角度到舵机
delay(15); // 延时15ms让舵机转到指定位置
break;
}
temp="";
}
}
