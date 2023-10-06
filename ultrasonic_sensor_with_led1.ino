int trig = 9; 
int echo = 10;
int led1 = 11; 


long duration = 0; 
int cm = 0; 
int in = 0;

void setup()
{
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);
  pinMode(led1, OUTPUT); 

  Serial.begin(9600); 
  Serial.println("Serial Started..."); 
}

void loop()
{
  digitalWrite(trig, LOW); 
  digitalWrite(trig, HIGH); 
  digitalWrite(trig, LOW);
  
  int duration = pulseIn (echo, HIGH); 
  cm = duration*0.034/2;
  in = duration*0.0133/2;
  
  Serial.println(in); 
  
 if (in <= 36 ){
    digitalWrite(led1, HIGH); 
    delay(300); 
  }
  else{
        digitalWrite(led1, LOW); 
    delay(300);
}
}