int led[3] = {15, 4, 17};
int gnd[3] = {2, 16, 5};
int trig = 12;
int echo = 14;

void setup() {
  // put your setup code here, to run once:
  //set led pin
  for (int i=0; i<3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 1);
    
    pinMode(gnd[i], OUTPUT);
    digitalWrite(gnd[i], 0);
  }
  Serial.begin(115200);

  //set hc pin
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT); 
}

void loop() {
  //make high pulse from trig
  digitalWrite(trig, LOW);
  delayMicroseconds(2);   
  digitalWrite(trig, HIGH);     
  delayMicroseconds(10);   
  digitalWrite(trig, LOW);
  
  //measure distance by using pulsein
  int distance = pulseIn(echo, HIGH) * 17 / 1000;      
  Serial.print(distance);    
  Serial.println("cm");      

  if(distance >=50){
    //if distance is bigger than 50cm turn three lights together
    digitalWrite(led[0], 1);
    digitalWrite(led[1], 1);
    digitalWrite(led[2], 1);
    delay(100);
    digitalWrite(led[0], 0);
    digitalWrite(led[1], 0);
    digitalWrite(led[2], 0);
    delay(100);
   }
   else if(distance >=20){
    //if distance is bigger than 20cm and smaller than 50cm turn light in order
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 1);
      delay(50);
      digitalWrite(led[k], 0);
      delay(100);
     }
   
   }
   else{
    //if distance is smaller than 20cm turn two lights together
     for (int k=0; k<3; k++) {
      int a=(k+1)%3;
      digitalWrite(led[k], 1);
      digitalWrite(led[a], 1);
      delay(100);
      digitalWrite(led[k], 0);
      digitalWrite(led[a], 0);
      delay(100);
     }
   } 

  delay(100);
}
