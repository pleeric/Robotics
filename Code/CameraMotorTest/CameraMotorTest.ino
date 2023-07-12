
//Setup for 1 motor

//MOTOR DRIVER 5V CONNECTED TO ARDUINO VIN
//MOTOR DRIVER GROUND CONNECTED TO ARDUINO GROUND 

float heading, inital, ballDistance, ballDirection; 

int MFL1 = 36; //IN1 Connected to 2 
int MFL2 = 3; //IN2 Connected to ~3
int MFLA = 5; // ENB connected to ~5

int mBL1 = 38; //IN1 Connected to 2 
int mBL2 = 5; //IN2 Connected to ~3
int mBLA = 5; // ENB connected to ~5

int mFR1 = 37; //IN1 Connected to 2 
int mFR2 = 6; //IN2 Connected to ~3
int mFRA = 5; // ENB connected to ~5

int mBR1 = 39; //IN1 Connected to 2 
int mBR2 = 9; //IN2 Connected to ~3
int mBRA = 5; // ENB connected to ~5


void setup() {
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:   
  getBallInfo();

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