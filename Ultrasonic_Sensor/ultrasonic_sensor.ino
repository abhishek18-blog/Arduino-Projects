int trig=12;
int echo=11;
int dur;
int dis;

void setup(){
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(trig,LOW);
  delay(100);

 digitalWrite(trig,HIGH);
  delay(100);

 digitalWrite(trig,LOW);

  dur=pulseIn(echo,HIGH);
  dis=dur*0.034/2;
  Serial.println("the distancce is");
  Serial.print(dis);
}
