// TCS230 or TCS3200 pins wiring to Arduino

//VCC to 5V
#define S0 40 //S0 to 40
#define S1 10 //S1 to ~10
#define S2 11 //S2 to ~11
#define S3 31 //S3 to 31
#define sensorOut 52 //OUT to 52

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
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  gColour = map(greenFrequency,50,255,255,0);
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(gColour);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  bColour = map(blueFrequency, 60, 250, 255,0);
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(bColour);
  delay(100);



  if(bColour > 200 and rColour > 200 and gColour > 200){
    Serial.println("White detected");
  }
}