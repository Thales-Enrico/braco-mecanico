#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define NUM_SERVOS 7
#define MAX_SERVO1 180
#define MAX_SERVO2 180
#define MAX_SERVO3 180
#define MAX_SERVO4 180
#define MAX_SERVO5 180
#define MAX_SERVO6 180
#define MAX_SERVO7 180
int maxServos[NUM_SERVOS] = {MAX_SERVO1, MAX_SERVO2,
    MAX_SERVO3, MAX_SERVO4, MAX_SERVO5, MAX_SERVO6, MAX_SERVO7};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void writeServos(int position, int time);
void beginServos();

void setup() {
    Serial.begin(9600); 
    beginServos(); 
    delay(300);
}

void loop() {
  if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n'); 
        serialRead(command);
    }
}
void serialRead(String command) {
    // emxemplo: -010+000+000-100+000+000+000
    int sign, value, speed;
    for (int i = 0; i < NUM_SERVOS; i++){
        sign = (command.charAt(i*4) == '-') ? -1 : 1;
        value = command.substring(i*4 + 1, i*4 + 4).toInt() * sign;

        if(value > maxServos[i]) value = maxServos[i];

        writeServos(i, value);
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

    #define FREQUENCY 50    

    pwm.begin(); 
    pwm.setPWMFreq(FREQUENCY); 
}
