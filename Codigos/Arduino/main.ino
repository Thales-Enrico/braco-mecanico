#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define NUM_SERVOS 7

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void writeServos(int position, int time);
void beginServos();

void setup() {
    Serial.begin(9600); 
    beginServos(); 
    delay(300);
}

void loop() {
  
}
void serialRead(String command, int nServo) {
    while (command.length() > 0) {
        int motorIndex = command.charAt(0 + (nServo * 3)) - '0'; 
        int sign = (command.charAt(1) == '-') ? -1 : 1; 
        int value = command.substring(2, 5).toInt(); 
        int speed = sign * value; 

        moveServo(motorIndex, speed);

        command = command.substring(5); 
    }
}

void writeServos(int nServo, int position) {
    #define SERVOMIN  205 
    #define SERVOMAX  409 

    if (position > 180) position = 180; 
    int pos = map(abs(position), 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(nServo, 0, pos);
    if (position > 0) {
        // horario
        pwm.setPWM(nServo, 0, position);
        } 
    else if (position < 0) {
        // anti-horario
        pwm.setPWM(nServo, 0, SERVOMAX - position);
        }
}

void beginServos() {

    #define Frequency 50    

    pwm.begin(); 
    pwm.setPWMFreq(Frequency); 
}
