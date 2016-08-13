#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Arduino.h>

class ServoMotor {
    public:
        ServoMotor(int fwdPin, int revPin, int pwm, int rd);
        ~ServoMotor();

        void initialize(int min, int max, int base);
        void update();
        void shutdown();

        void setTarget(int t);
        void setTargetPercentage(int t);
        void stop();

    private:
        void moveToTarget(int currentValue);
        double percentageToTarget(int currentValue);
        
        const int forwardPin;
        const int reversePin;
        const int pwmPin;       
        const int readPin;

        int rangeMin;
        int rangeMax;
        int pwmBase;

        int target;
};

#endif

