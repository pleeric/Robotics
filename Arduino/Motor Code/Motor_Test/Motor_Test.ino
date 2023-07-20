
//Setup for 1 motor

//MOTOR DRIVER 5V CONNECTED TO ARDUINO VIN
//MOTOR DRIVER GROUND CONNECTED TO ARDUINO GROUND 

int motor2pin1 = 39; //IN1 Connected to 2 
int motor2pin2 = 5; //IN2 Connected to ~2
int motor2Analog = 3; // ENA/ENB connected to ~3


void setup() {
  // put your setup code here, to run once:
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  //pinMode(motor2Analog, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:   

  //analogWrite(5,50);
  //delay(1000);
  //analogWrite(5,100);
  //delay(1000);
  //analogWrite(5,150);
  //delay(1000);
  //analogWrite(5,200);
  //delay(1000);
  //analogWrite(5,250);
  //delay(1000);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2,HIGH);

}