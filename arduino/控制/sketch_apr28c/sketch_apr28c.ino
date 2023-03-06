int LEDPin=13;
char inByte = 0; //串口接收的数据 
String temp = "";//缓存
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
while (Serial.available()!=0) //判断串口是否有数据  
  {  
    inByte = Serial.read();//读取数据，串口一次只能读1个字符  
    temp += inByte;//写入缓存，  
                   //再次循环会判断写入是否成功  
   }  
   if(temp != "")   //判断临时变量是否为空  
   {
    if(temp.equals("1")){
   digitalWrite(LED_BUILTIN, HIGH);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page1.t0.bco=33808");
    Serial.write("page1.t1.bco=65535");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
  }else if(temp.equals("0")){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write("page1.t0.bco=65535");
    Serial.write("page1.t1.bco=33808");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
   }
   }
    temp = "";//清空变量  
  //myservo.write(angle);  //控制舵机转动相应的角度。这里不要超多舵机的最大角度，有的舵机是60度，也有360度的舵机  
  delay(50);//延时50ms，这里的延时并不影响舵机的速度，只是限制你下一次输入的间隔     
}
