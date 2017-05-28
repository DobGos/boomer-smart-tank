//*** 1- Documentation
//This program is used to control a robot car using a app that communicates with Arduino trough a bluetooth module

#include <AFMotor.h>

//creates two objects to control the terminal 3 and 4 of motor shield 
AF_DCMotor motor1(1); 
AF_DCMotor motor2(3); 

int speed;
int updateStep;

char command; 
char direction;

void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  speed = 255;
  updateStep = 5;
}

void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      direction = command;
      break;
    case 'B':  
      back();
      direction = command;
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    case 'S':
      Stop();
      direction = command;
      break;
    case 'U':
      speedUp();
      break;
    case 'D':
      speedDown();
      break;
    }
  } 
}

void forward()
{
  motor1.setSpeed(speed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(speed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(speed); 
  motor1.run(BACKWARD); //rotate the motor counterclockwise
  motor2.setSpeed(speed); 
  motor2.run(BACKWARD); //rotate the motor counterclockwise
}

void left()
{
  motor1.setSpeed(speed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}

void right()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE); //turn motor1 off
  motor2.setSpeed(speed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void Stop()
{
  motor1.setSpeed(0);
  motor2.run(RELEASE); //turn motor1 off
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}

void speedUp()
{
  speed = speed + updateStep; 
  if (speed > 255) speed = 255;
  updateSpeed();
}

void speedDown()
{
  speed = speed - updateStep; 
  if (speed < 190) speed = 190; 
  updateSpeed();
}

void updateSpeed()
{
   switch(direction){
    case 'F':  
      forward();
      break;
    case 'B':  
      back();
      break;
    case 'S':  
      break;
   }
    Serial.print(direction);
    Serial.print(" -> ");
    Serial.println(speed);
}

