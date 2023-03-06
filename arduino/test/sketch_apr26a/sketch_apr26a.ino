void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  String t1="2",t2="4";
  // put your main code here, to run repeatedly:
  Serial.write("page2.t6.txt=\"t1\"");
//  Serial.print("+"+t1);
//   Serial.write("\"");
  Serial.write(0XFF);
  Serial.write(0XFF);
  Serial.write(0XFF);
  delay(3000);
  Serial.write("page2.t8.txt=\"t2\"");
//  Serial.print("+"+t2);
//   Serial.write("\"");
  Serial.write(0XFF);
  Serial.write(0XFF);
  Serial.write(0XFF);
  delay(3000);
}
