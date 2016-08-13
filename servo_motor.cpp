#include "servo_motor.h"

ServoMotor::ServoMotor(int fwdPin, int revPin, int pwm, int rd) :
    forwardPin(fwdPin),
    reversePin(revPin),
    pwmPin(pwm),
    readPin(rd),
    pwmBase(128),
    target(-1) {}

ServoMotor::~ServoMotor() {}

void ServoMotor::initialize(int min, int max, int base) {
    rangeMin = min;
    rangeMax = max;
    pwmBase = base;

    pinMode(pwmPin, OUTPUT);
    pinMode(forwardPin, OUTPUT);
    pinMode(reversePin, OUTPUT);
}

void ServoMotor::update() {
    double input = analogRead(readPin);

    if(target != -1) {
        moveToTarget(input);
    }
}

void ServoMotor::shutdown() {
    stop();    
}

void ServoMotor::setTarget(int t) {
    if(t > rangeMax)
        target = rangeMax;
    else if(t < rangeMin)
        target = rangeMin;
    else
        target = t;
}

void ServoMotor::setTargetPercentage(int t) {
    if(t < 0)
        t = 0;
    else if(t > 100)
        t = 100;

    int rangeVal = map(t, 0, 100, rangeMin, rangeMax);
    setTarget(rangeVal);
}

void ServoMotor::stop() {
    digitalWrite(forwardPin, LOW);
    digitalWrite(reversePin, LOW);
    analogWrite(pwmPin, 0);
    target = -1;
}

void ServoMotor::moveToTarget(int currentValue) {
    double targetPercentage = percentageToTarget(currentValue);
    if(targetPercentage < 0.02) {
        stop();
        return;    
    }

    int pwmSpeed = min(pwmBase + (int)((255 - pwmBase) * targetPercentage), 255);
    boolean pinA = HIGH;
    boolean pinB = LOW;
    if(currentValue < target) {
        pinA = LOW;
        pinB = HIGH;
    }

    digitalWrite(forwardPin, pinA);
    digitalWrite(reversePin, pinB);
    analogWrite(pwmPin, pwmSpeed);
}

double ServoMotor::percentageToTarget(int currentValue) {
    double delta = abs(currentValue - target);
    double range = (rangeMax - rangeMin);
    return (delta / range);
}

