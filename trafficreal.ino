const int red=5;
const int yellow=6;
const int green=7; 
int i;

void setup() {
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  
}

void loop() {
 
  for(i=0;i<3;i++){
     digitalWrite(red,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW);
  delay(1000);
  digitalWrite(red,HIGH);
  delay(500);
  }

 digitalWrite(red,LOW);
  digitalWrite(yellow,HIGH);
  digitalWrite(green,LOW);
  delay(1000);
   for(i=0;i<3;i++){
  digitalWrite(yellow,HIGH);
  delay(500)    ;
  }
 digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,HIGH);
  delay(1000);
 for(i=0;i<3;i++){
  digitalWrite(green,HIGH);
  delay(500);    
  }while(true);
}
