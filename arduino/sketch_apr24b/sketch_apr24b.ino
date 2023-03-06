int led = 13;
int sensor = 12;
int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(led, sensor);
  digitalWrite(led, state);

  Serial.print("sensor_state:");
  Serial.println(state);
  delay(10);
}
