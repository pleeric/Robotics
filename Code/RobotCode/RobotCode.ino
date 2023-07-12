#include <Arduino.h>
#include <Wire.h>
#include <HMC5883L_Simple.h>
#include <Pixy2.h>

#define BAUD_RATE 115200

Pixy2 pixy;
HMC5883L_Simple Compass;

float heading, inital, ballDistance, ballDirection; 
int redFrequency, greenFrequency, blueFrequency;
int rColour,gColour, bColour;

int MFL1 = 2; //IN1 Connected to 2 
int MFL2 = 3; //IN2 Connected to ~3
int MFLA = 5; // ENB connected to ~5

int mBL1 = 2; //IN1 Connected to 2 
int mBL2 = 3; //IN2 Connected to ~3
int mBLA = 5; // ENB connected to ~5

int mFR1 = 2; //IN1 Connected to 2 
int mFR2 = 3; //IN2 Connected to ~3
int mFRA = 5; // ENB connected to ~5

int mBR1 = 2; //IN1 Connected to 2 
int mBR2 = 3; //IN2 Connected to ~3
int mBRA = 5; // ENB connected to ~5

#define S0 50 //S0 to 50
#define S1 10 //S1 to ~10
#define S2 11 //S2 to ~11
#define S3 51 //S3 to 51
#define sensorOut 52 //OUT to 52

void setup() {
  Serial.begin(BAUD_RATE);
  pixy.init();
  Wire.begin();
  SensorSetup();

}

void loop() {
  getBearing();
  getBallInfo();
  delay(100);
  if(isWhite){
    WillSurviveIfCopsCome();
  }
}

void TurnToBall(){
  if(ballDirection > 280){
    //Turn right a bit
    Turn(1);
  }
  else if (ballDirection < 100){
    //Turn left a bit
    Turn(0);
  }
  else{
    GoStraight();
    //go forward
  }
}

void GoStraight(){
  digitalWrite(mFL1,HIGH);
  digitalWrite(mFL2,LOW);

  digitalWrite(mFR1,HIGH);
  digitalWrite(mFR2,LOW);

  digitalWrite(mBL1,HIGH);
  digitalWrite(mBL2,LOW);

  digitalWrite(mBR1,HIGH);
  digitalWrite(mBR2,LOW);
}


void WillSurviveIfCopsCome(){
  //Go backwards and turn towards goal/ball
  digitalWrite(mFL1,LOW);
  digitalWrite(mFL2,HIGH);

  digitalWrite(mFR1,LOW);
  digitalWrite(mFR2,HIGH);

  digitalWrite(mBL1,LOW);
  digitalWrite(mBL2,HIGH);

  digitalWrite(mBR1,LOW);
  digitalWrite(mBR2,HIGH);

  delay(1000);

  digitalWrite(mFL1,HIGH);
  digitalWrite(mFL2,LOW);

  digitalWrite(mFR1,HIGH);
  digitalWrite(mFR1,LOW);

  digitalWrite(mBL1,HIGH);
  digitalWrite(mBL1,LOW);

  digitalWrite(mBR1,HIGH);
  digitalWrite(mBR1,LOW);
  getBallInfo();
}

bool isWhite(){
  if(bColour > 200 and rColour > 200 and gColour > 200){
    return true;
  return false;
  }
}

void SensorSetup(){
  Compass.SetDeclination(23, 35, 'E');  
  Compass.SetSamplingMode(COMPASS_SINGLE);
  Compass.SetScale(COMPASS_SCALE_130);
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  initial = Compass.GetHeadingDegrees();

  // Setting the Pin Modes
  pinMode(S0, OUTPUT);  //S1-4 are color sensor pins
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  pinMode(mBL1, OUTPUT);
  pinMode(mBL2, OUTPUT);
  pinMode(mBLA, OUTPUT);

  pinMode(mBR1, OUTPUT);
  pinMode(mBR2, OUTPUT);
  pinMode(mBR1A, OUTPUT);

  pinMode(mFL1, OUTPUT);
  pinMode(mFL2, OUTPUT);
  pinMode(mFLA, OUTPUT);

  pinMode(mFR1, OUTPUT);
  pinMode(mFR2, OUTPUT);
  pinMode(mFRA, OUTPUT);

  // Setting colour sensor frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void getBallInfo(){
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
    ballDirection = pixy.ccc.blocks[0].m_x;
    ballDistance = 1500/pixy.ccc.blocks[i].m_width;
    TurnToBall();
  }
  else{
    while !(pixy.ccc.numBlocks){
      digitalWrite(mBR1,LOW);
      digitalWrite(mBR1,HIGH);   
      
      digitalWrite(mFR1,LOW);
      digitalWrite(mFR1,HIGH);   
    }

    digitalWrite(mBR1,HIGH);
    digitalWrite(mBR1,LOW);   

    digitalWrite(mFR1,HIGH);
    digitalWrite(mFR1,LOW);   
    //Rotate until find ball
  }
}


void getBearing(){
  heading = Compass.GetHeadingDegrees();
   if(heading - initial > 0){
    heading = heading - initial;
   }else{
     heading = heading - initial + 360;
   }
}

void Turn(int a){
  //0 for left, 1 for right
  if(a == 1){
    digitalWrite(mBR1,LOW);
    digitalWrite(mBR1,LOW);   

    digitalWrite(mFR1,LOW);
    digitalWrite(mFR1,LOW);
    delay(150);

    //Turn Front Right and Back Right motors off for 150 ms

    digitalWrite(mBR1,HIGH);
    digitalWrite(mBR1,LOW);   

    digitalWrite(mFR1,HIGH);
    digitalWrite(mFR1,LOW);
  }
  else{
    digitalWrite(mBL1,LOW);
    digitalWrite(mBL1,LOW);   

    digitalWrite(mFL1,LOW);
    digitalWrite(mFL1,LOW);
    delay(150);

    //Turn Front Right and Back Right motors off for 150 ms

    digitalWrite(mBL1,HIGH);
    digitalWrite(mBL1,LOW);   

    digitalWrite(mFL1,HIGH);
    digitalWrite(mFL1,LOW);
  }
}