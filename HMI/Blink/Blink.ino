#include <Servo.h>    // 声明调用Servo.h库
Servo myservo;        // 创建一个舵机对象
int pos = 0;
int flag=1;
char inByte = 0; //串口接收的数据  
int angle = 90;  //初始角度值，这里180度的舵机，中立点就是90。  
String temp = "";//缓存
String passWord="1111";
#define Feng 11
int LED=13;

// 变量pos用来存储舵机位置
void setup() {
   Serial.begin(9600);        //串口波特率(使用蓝牙串口必需此句)
   //舵机引出三根线。一根是红色，连到+5V上。一根棕色（有些是黑的），连到GND。
   //还有一根是黄色或者橘色，连到数字引脚9。
   myservo.attach(9);  // 将引脚9上的舵机与声明的舵机对象连接起来
    pinMode(Feng, OUTPUT);   //定义板载LED灯端口为输出
    pinMode(LED, OUTPUT);  //定义外接LED灯端口为输出
    digitalWrite(Feng, LOW);  //板载LED 初始为熄灭状态
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
 while (Serial.available()!=0) //判断串口是否有数据  
  {  
    inByte = Serial.read();//读取数据，串口一次只能读1个字符  
    temp += inByte;//写入缓存，  
                   //再次循环会判断写入是否成功  
   }  
   if(temp != "")   //判断临时变量是否为空  
   {
    if(temp.equals("1")){
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }else if(temp.equals("0")){
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   }
   }
  temp = "";//清空变量  
  //myservo.write(angle);  //控制舵机转动相应的角度。这里不要超多舵机的最大角度，有的舵机是60度，也有360度的舵机  
  delay(50);//延时50ms，这里的延时并不影响舵机的速度，只是限制你下一次输入的间隔        
}
