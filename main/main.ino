byte numbers[]={0b00111111, //0
0b00000110, //1
0b01011011, //2
0b01001111, //3
0b01100110, //4
0b01101101, //5
0b01111101, //6
0b00000111, //7
0b01111111, //8
0b01101111 //9
};
int pins[]={5,18,32,33,25,26,27,15}; //pin Segments
int pinsDigit[]={2,0}; //pin Digit
enum pinsLed{Red=4,Yellow=16,Green=17};
enum light{isRed=-1,isGreen,isYellow};
int n=30,lightStatus=isGreen;
void setup() {
  for(int i=0;i<8;i++){
    pinMode(pins[i], OUTPUT);
    if(i%4==3)
      pinMode(pinsDigit[(i-3)/4], OUTPUT);
      digitalWrite(pinsDigit[(i-3)/4], HIGH);
  }
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);
}
void display(int digit, int number){
  for(int i=0;i<8;i++){
    digitalWrite(pins[i], HIGH);
    if(i%4==3)
      digitalWrite(pinsDigit[(i-3)/4], LOW);
  }
  digitalWrite(pinsDigit[digit],HIGH);
  byte* temp=&numbers[number];
  for(int i=0;i<8;i++){
    if((*temp>>i)&1)
      digitalWrite(pins[i], LOW);
  }
  delay(2);
  for(int i=0;i<8;i++){
    digitalWrite(pins[i], HIGH);
  }
}

unsigned long _time=0;
void loop() {
  int num[]={n/10,n%10};
  if(lightStatus==isYellow){
    digitalWrite(Yellow, HIGH);
    digitalWrite(Red, LOW);
    digitalWrite(Green, LOW);
  }
  if(lightStatus==isGreen){
    digitalWrite(Green, HIGH);
    digitalWrite(Red, LOW);
    digitalWrite(Yellow, LOW);
  }
  if(lightStatus==isRed){
    digitalWrite(Red, HIGH);
    digitalWrite(Yellow, LOW);
    digitalWrite(Green, LOW);
  }
  for(int i=0;i<2;i++){
    display(i,num[i]);
    }
  
  if(millis()-_time>=1000){
    _time=millis();
    n--;
  }
  if(n<0){
    switch(lightStatus){
      case isRed: 
        lightStatus=isGreen; 
        n=30;
        break;
      case isYellow: 
        lightStatus=isRed; 
        n=45;
        break;
      case isGreen: 
        lightStatus=isYellow; 
        n=3;
        break;
    }
  }
}
