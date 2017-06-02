int controlLeftMotorB=8;//define I1 interface
int controlLeftMotorA=11;//define I2 interface 
int speedControlLeft=9;//enable motor Left
int controlRightMotorA=13;//define I4 interface 
int controlRightMotorB=12;//define I3 interface 
int speedControlRight=10;//enable motor Right

const char CMD_FORWARD = 'F';
const char CMD_BACKWARD = 'B';
const char CMD_TURN_LEFT = 'L';
const char CMD_TURN_RIGHT = 'R';
const char CMD_STOP = 'S';
const char CMD_SPEED_UP = 'U';
const char CMD_SPEED_DOWN = 'D';
const int MAX_SPEED = 255; 
const int MIN_SPEED = 195; // Update this according to your motors. With 24V motors speed bellow this doesn't make the motor move.

char command;
char currentDirection;
int speed;
boolean leftInMotion = false;
boolean rightInMotion = false;
 
void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  pinMode(controlLeftMotorB,OUTPUT);
  pinMode(controlLeftMotorA,OUTPUT);
  pinMode(speedControlLeft,OUTPUT);

  pinMode(controlRightMotorB,OUTPUT);
  pinMode(controlRightMotorA,OUTPUT);
  pinMode(speedControlRight,OUTPUT);
  speed = (MAX_SPEED + MIN_SPEED) / 2;
}

void loop()
{
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    //Change pin mode only if new command is different from previous.   
    Serial.print("Received command: ");
    Serial.println(command);
    switch(command){
    case CMD_FORWARD:  
      forward();
      leftInMotion = true;
      rightInMotion = true;
      break;
    case CMD_BACKWARD:  
      backward();
      leftInMotion = true;
      rightInMotion = true;
      break;
    case CMD_TURN_LEFT:  
      left();
      leftInMotion = false;
      rightInMotion = true;
      break;
    case CMD_TURN_RIGHT:
      right();
      leftInMotion = true;
      rightInMotion = false;
      break;
    case CMD_STOP:
      stop();
      leftInMotion = false;
      rightInMotion = false;
      break;
    case CMD_SPEED_UP:
      speedUp();
      break;
    case CMD_SPEED_DOWN:
      speedDown();
      break;
    }
  } 
}

 
void forward() // Move forward
{
    Serial.println("Forward");
    setMotorLeftForward();
    setMotorRightForward();
    runLeft();
    runRight();
}

void backward() // Move backward
{
    Serial.println("Backward");
    setMotorLeftBackward();
    setMotorRightBackward();
    runLeft();
    runRight();
}

void left() // turn left
{
    Serial.println("Left");
    setMotorRightForward();
    stopLeft();
    runRight();
}

void right() // turn right
{
    Serial.println("Right");
    setMotorLeftForward();
    stopRight();
    runLeft();
}


void setMotorLeftForward(){
     digitalWrite(controlLeftMotorA,LOW); //turn Left DC Motor A move anticlockwise
     digitalWrite(controlLeftMotorB,HIGH);
}

void setMotorLeftBackward(){
     digitalWrite(controlLeftMotorA,HIGH); //turn Left DC Motor A move clockwise
     digitalWrite(controlLeftMotorB,LOW);
}

void setMotorRightForward(){
     digitalWrite(controlRightMotorA,HIGH);//turn Right motor forward (clockwise)
     digitalWrite(controlRightMotorB,LOW);
}

void setMotorRightBackward(){
     digitalWrite(controlRightMotorA,LOW);//turn Right motor backward (anitclockwise)
     digitalWrite(controlRightMotorB,HIGH);
}


void stop(){
  stopLeft();
  stopRight();
}

void speedUp(){
  speed = speed + 10;
  if (speed > MAX_SPEED) 
    speed = MAX_SPEED;

  updateRunSpeed();
}

void speedDown(){
  speed = speed - 10;
  if (speed < MIN_SPEED) 
    speed = MIN_SPEED;
  updateRunSpeed();
}

void updateRunSpeed(){
  if (leftInMotion) runLeft();
  if (rightInMotion) runRight();
  Serial.print("New speed: ");
  Serial.println(speed);
}


void stopLeft(){
  setSpeedLeft(0);  
}

void runLeft(){
  setSpeedLeft(speed);  
}

void stopRight(){
  setSpeedRight(0);  
}

void runRight(){
  setSpeedRight(speed);  
}

void setSpeedLeft(int newSpeed) {
     analogWrite(speedControlLeft,newSpeed);
}

void setSpeedRight(int newSpeed) {
     analogWrite(speedControlRight,newSpeed);
}



