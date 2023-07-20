#include <Pixy2.h>
// TCS230 or TCS3200 pins wiring to Arduino
int mFL1 = 22; //IN1 Connected to 2 
int mFL2 = 3; //IN2 Connected to ~3

int mBL1 = 24; //IN1 Connected to 2 
int mBL2 = 5; //IN2 Connected to ~3

int mFR1 = 37; //IN1 Connected to 2 
int mFR2 = 6; //IN2 Connected to ~3

int mBR1 = 39; //IN1 Connected to 2 
int mBR2 = 9; //IN2 Connected to ~3

Pixy2 pixy;

void left(){
    digitalWrite(mFL1,HIGH);
    digitalWrite(mFL2,LOW);

    digitalWrite(mFR1,LOW);
    digitalWrite(mFR2,HIGH);  

    digitalWrite(mBL1,LOW);
    digitalWrite(mBL2,HIGH);

    digitalWrite(mBR1,LOW);
    digitalWrite(mBR2,HIGH);  
}
void right(){
    digitalWrite(mFL1,LOW);
    digitalWrite(mFL2,HIGH);

    digitalWrite(mFR1,HIGH);
    digitalWrite(mFR2,LOW);  

    digitalWrite(mBL1,HIGH);
    digitalWrite(mBL2,LOW);

    digitalWrite(mBR1,HIGH);
    digitalWrite(mBR2,LOW);  
}
void straight(){
    digitalWrite(mFL1,LOW);
    digitalWrite(mFL2,HIGH);

    digitalWrite(mFR1,LOW);
    digitalWrite(mFR2,HIGH);   

    digitalWrite(mBL1,HIGH);
    digitalWrite(mBL2,LOW);

    digitalWrite(mBR1,LOW);
    digitalWrite(mBR2,HIGH);  
}  

void off(){
    digitalWrite(mFL1,LOW);
    digitalWrite(mFL2,LOW);
    digitalWrite(mFR1,LOW);
    digitalWrite(mFR2,LOW);      
    digitalWrite(mBL1,LOW);
    digitalWrite(mBL2,LOW);
    digitalWrite(mBR1,LOW);
    digitalWrite(mBR2,LOW);  
}


//VCC to 5V
#define S0 40 //S0 to 50
#define S1 10 //S1 to ~10
#define S2 11 //S2 to ~11
#define S3 31 //S3 to 51
#define sensorOut 34 //OUT to 52

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int rColour;
int gColour;
int bColour;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(115200);
  pixy.init();
  straight();
}
void loop() {
  WhiteCheck();
  delay(100);
  ballcheck();
  delay(100);
}
void WhiteCheck(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  rColour = map(redFrequency, 40, 110, 255,0);
  Serial.print("R = ");
  Serial.print(rColour);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  gColour = map(greenFrequency,50,255,255,0);
  Serial.print(" G = ");
  Serial.print(gColour);
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  bColour = map(blueFrequency, 60, 250, 255,0);
  Serial.print(" B = ");
  Serial.println(bColour);
  if(bColour > 200 and rColour > 200 and gColour > 200){
    Serial.println("White detected");
    off();
  }
}

void ballcheck(){
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks)
  {
    if (pixy.ccc.blocks[0].m_x > 280){
      Serial.println("Right");
      right();
    }
    else if (pixy.ccc.blocks[0].m_x < 100){

      Serial.println("Left");
      left();
    }
    else{
      Serial.println("Middle");
      straight();
    }
    Serial.print("Distance: ");
    Serial.println(1500/pixy.ccc.blocks[0].m_width);
  }
}