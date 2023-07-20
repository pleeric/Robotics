int mFL1 = 22; //IN1 Connected to 2 
int mFL2 = 3; //IN2 Connected to ~3

int mBL1 = 24; //IN1 Connected to 2 
int mBL2 = 5; //IN2 Connected to ~3

int mFR1 = 37; //IN1 Connected to 2 
int mFR2 = 6; //IN2 Connected to ~3

int mBR1 = 39; //IN1 Connected to 2 
int mBR2 = 9; //IN2 Connected to ~3


void left(){
    digitalWrite(mFL1,LOW);
    digitalWrite(mFL2,LOW);
    digitalWrite(mFR1,LOW);
    digitalWrite(mFR2,HIGH);      
    digitalWrite(mBL1,LOW);
    digitalWrite(mBL2,HIGH);
    digitalWrite(mBR1,LOW);
    digitalWrite(mBR2,LOW);  
}
void right(){
    digitalWrite(mFL1,LOW);
    digitalWrite(mFL2,HIGH);
    digitalWrite(mFR1,LOW);
    digitalWrite(mFR2,LOW);      
    digitalWrite(mBL1,LOW);
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
#include <Pixy2.h>




// This is the main Pixy object 
Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  pixy.init();
  pinMode(mBL1, OUTPUT);
  pinMode(mBL2, OUTPUT);

  pinMode(mBR1, OUTPUT);
  pinMode(mBR2, OUTPUT);

  pinMode(mFL1, OUTPUT);
  pinMode(mFL2, OUTPUT);

  pinMode(mFR1, OUTPUT);
  pinMode(mFR2, OUTPUT);
  digitalWrite(mFL1,LOW);
  digitalWrite(mFL2,LOW);

  digitalWrite(mFR1,LOW);
  digitalWrite(mFR2,LOW);

  digitalWrite(mBL1,LOW);
  digitalWrite(mBL2,LOW);

  digitalWrite(mBR1,LOW);
  digitalWrite(mBR2,LOW);  
}
  
void loop()
{ 
  int i; 
  // grab blocks!
  
  pixy.ccc.getBlocks();
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    if (pixy.ccc.blocks[i].m_x > 280){
      Serial.println("Right");
      right();
    }
    else if (pixy.ccc.blocks[i].m_x < 100){

      Serial.println("Left");
      left();
    }
    else{
      Serial.println("Middle");
      straight();
    }
    Serial.print("Distance: ");
    Serial.println(1500/pixy.ccc.blocks[i].m_width);

    
  }  
  else{
    off();
  }
}
