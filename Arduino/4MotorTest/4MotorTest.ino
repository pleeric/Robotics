int mFL1 = 36; //IN1 Connected to 2 
int mFL2 = 3; //IN2 Connected to ~3

int mBL1 = 38; //IN1 Connected to 2 
int mBL2 = 5; //IN2 Connected to ~3

int mFR1 = 37; //IN1 Connected to 2 
int mFR2 = 6; //IN2 Connected to ~3

int mBR1 = 39; //IN1 Connected to 2 
int mBR2 = 9; //IN2 Connected to ~3


void setup() {

  Serial.begin(115200);
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
void loop() {


  if(Serial.available() > 0){
    char input = Serial.read();
    Serial.println(input == 'a');


    //ALL MOTORS ARE DRIVING FORWARD

    if(input == 'A'){
      digitalWrite(mFL1,LOW);
      digitalWrite(mFL2,HIGH);
    }
    if(input == 'B'){
      digitalWrite(mFR1,LOW);
      digitalWrite(mFR2,HIGH);      
    }
    if(input == 'C'){
      digitalWrite(mBL1,HIGH);
      digitalWrite(mBL2,LOW);
    }
    if(input == 'D'){
      digitalWrite(mBR1,LOW);
      digitalWrite(mBR2,HIGH);      
    }
    if(input == 'E'){
      digitalWrite(mFL1,LOW);
      digitalWrite(mFL2,LOW);

      digitalWrite(mFR1,LOW);
      digitalWrite(mFR2,LOW);

      digitalWrite(mBL1,LOW);
      digitalWrite(mBL2,LOW);

      digitalWrite(mBR1,LOW);
      digitalWrite(mBR2,LOW);
    }
    }

}
