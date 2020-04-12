int led[3] = {15, 4, 17};
int gnd[3] = {2, 16, 5};

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 1);
    
    pinMode(gnd[i], OUTPUT);
    digitalWrite(gnd[i], 0);
  }
  Serial.begin(115200);
}
int j=20;

void loop() {
  int a=3;
  int b=0, c=3;
  // put your main code here, to run repeatedly:
  for (int k=0; k<10; k++) {
    b=a*j;
    c=(k+j)%3;
    digitalWrite(led[c], 1);
    delay(b);
    digitalWrite(led[c], 0);
    delay(b);
    j=j+200;
    j++;
    if(j>1000)
      j=j%50;
    Serial.printf("j:%d\n",j);
  }
}
