int sensorpin=10;
int read;
void setup(){
  pinMode(sensorpin,INPUT);
  Serial.begin(9600);
}

void loop(){
  read=digitalRead(sensorpin);
  if(read==HIGH){
    Serial.print("motion detected");
    delay(500);
  }
  else{
    Serial.print("no motion");
        delay(500);

  }
}
