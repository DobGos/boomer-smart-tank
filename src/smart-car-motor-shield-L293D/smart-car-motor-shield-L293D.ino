//*** 1- Documentation
//This program is used to control a robot car using a app that communicates with Arduino trough a bluetooth module

#include <AFMotor.h>

//creates two objects to control the terminal 3 and 4 of motor shield 
AF_DCMotor motorL(1); 
AF_DCMotor motorR(3); 

const char CMD_FORWARD = 'F';
const char CMD_BACKWARD = 'B';
const char CMD_TURN_LEFT = 'L';
const char CMD_TURN_RIGHT = 'R';
const char CMD_STOP = 'S';
const char CMD_SPEED_UP = 'U';
const char CMD_SPEED_DOWN = 'D';
const int MAX_SPEED = 255; 
const int MIN_SPEED = 195; // Update this according to your motors. With 24V motors speed bellow this doesn't make the motor move.
const int SPEED_UPDATE_STEP = 5;


char command; 
char currentDirection;
int speed;

void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  speed = (MAX_SPEED + MIN_SPEED) / 2;
  currentDirection = CMD_STOP;
  updateSpeed();
  Serial.println("Application started.");
}

void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
//    stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    Serial.print("Received command: ");
    Serial.println(command);
    switch(command){
    case CMD_FORWARD:  
      forward();
      currentDirection = CMD_FORWARD;
      break;
    case CMD_BACKWARD:  
      backward();
      currentDirection = CMD_BACKWARD;
      break;
    case CMD_TURN_LEFT:  
      left();
      break;
    case CMD_TURN_RIGHT:
      right();
      break;
    case CMD_STOP:
      stop();
      currentDirection = CMD_STOP;
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

void forward()
{
  Serial.println("Forward");
  if (currentDirection == CMD_BACKWARD) stop();
  motorL.setSpeed(speed); //Define maximum velocity
  motorL.run(FORWARD); //rotate the motor clockwise
  motorR.setSpeed(speed); //Define maximum velocity
  motorR.run(FORWARD); //rotate the motor clockwise
}

void backward()
{
  if (currentDirection == CMD_FORWARD) stop();
  Serial.println("Backward");
  motorL.setSpeed(speed); 
  motorL.run(BACKWARD); //rotate the motor counterclockwise
  motorR.setSpeed(speed); 
  motorR.run(BACKWARD); //rotate the motor counterclockwise
}

void right()
{
  Serial.println("Right");
  motorL.setSpeed(speed); //Define maximum velocity
  if (currentDirection == CMD_BACKWARD) {
    motorL.run(BACKWARD); //rotate the motor clockwise
  } else {  
    motorL.run(FORWARD); //rotate the motor clockwise
  }
  motorR.setSpeed(0);
  motorR.run(RELEASE); //turn motorR off
}

void left()
{
  Serial.println("Left");
  motorL.setSpeed(0);
  motorL.run(RELEASE); //turn motorL off
  motorR.setSpeed(speed); //Define maximum velocity
  if (currentDirection == CMD_BACKWARD) {
    motorR.run(BACKWARD); //rotate the motor clockwise
  } else {
    motorR.run(FORWARD); //rotate the motor clockwise
  }
}

void stop()
{
  Serial.println("Stop");
  motorL.setSpeed(0);
  motorR.run(RELEASE); //turn motorL off
  motorR.setSpeed(0);
  motorR.run(RELEASE); //turn motorR off
  delay(200);
}

void speedUp()
{
  speed = speed + SPEED_UPDATE_STEP; 
  if (speed > MAX_SPEED) speed = MAX_SPEED;
  updateSpeed();
}

void speedDown()
{
  speed = speed - SPEED_UPDATE_STEP; 
  if (speed < MIN_SPEED) speed = MIN_SPEED; 
  updateSpeed();
}

void updateSpeed()
{
   switch(currentDirection){
    case CMD_FORWARD:  
      forward();
      break;
    case CMD_BACKWARD:  
      backward();
      break;
    case CMD_STOP:  
      break;
   }
    Serial.print(currentDirection);
    Serial.print(" -> ");
    Serial.println(speed);
}


