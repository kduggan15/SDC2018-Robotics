/*
Code for extending and retracting the shell of the bot, as well as for raising and lowering the back door. 

*/


#define MShellSpeed 10
#define MShellDir 30
#define ShellEndRetracted 23
#define ShellEndExtended 25

#define MDoorSpeed 11
#define MDoorDir 32
#define DoorEndRaised 27
#define DoorEndLowered 29

void BodyMotionInit(){

  pinMode(MShellSpeed, OUTPUT);
  pinMode(MShellDir, OUTPUT);
  pinMode(ShellEndRetracted, INPUT);
  pinMode(ShellEndExtended, INPUT);
  pinMode(MDoorSpeed, OUTPUT);
  pinMode(MDoorDir, OUTPUT);
  pinMode(DoorEndRaised, INPUT);
  pinMode(DoorEndLowered, INPUT);
  
}

void ShellRetract(){

  digitalWrite(MShellDir, LOW);
  
  while(digitalRead(ShellEndRetracted) != 1){
    analogWrite(MShellSpeed, 150);
  }
  analogWrite(MShellSpeed, 0);
}

void ShellExtend(){
  digitalWrite(MShellDir, HIGH);
  
  while(digitalRead(ShellEndExtended) != 1){
    analogWrite(MShellSpeed, 150);
  }
  analogWrite(MShellSpeed, 0);
}


void DoorRaise(){
    digitalWrite(MDoorDir, LOW);
  
  while(digitalRead(DoorEndRaised) != 1){
    analogWrite(MDoorSpeed, 150);
  }
  analogWrite(MDoorSpeed, 0);


}

void DoorLower(){
    digitalWrite(MDoorDir, HIGH);
  
  while(digitalRead(DoorEndLowered) != 1){
    analogWrite(MDoorSpeed, 150);
  }
  analogWrite(MDoorSpeed, 0);
  
}

void setup() {
  // put your setup code here, to run once:
 BodyMotionInit();
}

void loop() {
  // put your main code here, to run repeatedly:

}
