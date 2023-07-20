#include <Pixy2.h>
Pixy2 pixy;

//50,51,52 cannot use 

#define S0 40 //S0 to 50
#define S1 10 //S1 to ~10
#define S2 11 //S2 to ~11
#define S3 31 //S3 to 51
#define sensorOut 34 //OUT to 52
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int rColour;
int gColour;
int bColour;

void setup() {
  pixy.init();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  Serial.begin(115200);
  

}


void loop(){
  WhiteCheck();
  delay(150);
  ballcheck();
  delay(150);
  

}


void ballcheck(){
  int i;
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
    Serial.print("Distance: ");
    Serial.println(1500/pixy.ccc.blocks[i].m_width);
  }
}

bool WhiteCheck() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  rColour = map(redFrequency, 40, 110, 255,0);
  delay(50);
  Serial.print(" R= ");
  Serial.print(rColour);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  gColour = map(greenFrequency,50,255,255,0);
  delay(50);
  Serial.print(" G= ");
  Serial.print(gColour);
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  delay(50);
  bColour = map(blueFrequency, 60, 250, 255,0);
  Serial.print(" B= ");
  Serial.println(bColour);
  if(bColour > 200 and rColour > 200 and gColour > 200){
    Serial.println("White detected");
    return true;
  }
}
