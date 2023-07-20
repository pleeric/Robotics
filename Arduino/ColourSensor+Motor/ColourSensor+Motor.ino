// TCS230 or TCS3200 pins wiring to Arduino
int mFL1 = 22; //IN1 Connected to 2 
int mFL2 = 3; //IN2 Connected to ~3

int mBL1 = 24; //IN1 Connected to 2 
int mBL2 = 5; //IN2 Connected to ~3

int mFR1 = 37; //IN1 Connected to 2 
int mFR2 = 6; //IN2 Connected to ~3

int mBR1 = 39; //IN1 Connected to 2 
int mBR2 = 9; //IN2 Connected to ~3


void left(){
    digitalWrite(mFL1,HIGH);
    digitalWrite(mFL2,LOW);

    digitalWrite(mFR1,HIGH);
    digitalWrite(mFR2,LOW);  

    digitalWrite(mBL1,HIGH);
    digitalWrite(mBL2,LOW);

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
  straight();
}
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  rColour = map(redFrequency, 40, 110, 255,0);
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(rColour);
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  gColour = map(greenFrequency,50,255,255,0);
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(gColour);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  bColour = map(blueFrequency, 60, 250, 255,0);
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(bColour);

  if(bColour > 200 and rColour > 200 and gColour > 200){
    Serial.println("White detected");
    off();
  }
}