#include "ruxpin.h"

// Motor A (mouth)
const int PWMA = 3;             // Speed control 
const int AIN1 = 4;             // Direction
const int AIN2 = 5;             // Direction
const int POTA = 7;             // Potentiometer
const int RANGE_MIN_A = 300;    // Mouth closed
const int RANGE_MAX_A = 940;    // Mouth open


// Motor B (eyes)
const int PWMB = 9;             // Speed control
const int BIN1 = 7;             // Direction
const int BIN2 = 8;             // Direction
const int POTB = 6;             // Potentiometer
const int RANGE_MIN_B = 300;    // Eyes open
const int RANGE_MAX_B = 665;    // Eyes closed

const int STBY_PIN = 6;

// Feature state percentage values
const int FEATURE_VALUES[2][4] = {
    {   0, 33, 66, 100 },
    { 100, 66, 33,   0 }
};

Ruxpin::Ruxpin() :
    eyes(BIN1, BIN2,  PWMB, POTB),
    mouth(AIN1, AIN2,  PWMA, POTA) {}

Ruxpin::~Ruxpin() {}

void Ruxpin::initialize() {
    eyes.initialize(RANGE_MIN_B, RANGE_MAX_B, 32);
    mouth.initialize(RANGE_MIN_A, RANGE_MAX_A, 96);
}

void Ruxpin::update() {
    eyes.update();
    mouth.update();    
}

void Ruxpin::shutdown() {
    eyes.shutdown();
    mouth.shutdown();    
}

void Ruxpin::enable() {
    digitalWrite(STBY_PIN, HIGH);
}

void Ruxpin::disable() {
    digitalWrite(STBY_PIN, LOW);    
}

void Ruxpin::setFeatureState(Feature feature, FeatureStates state) {
    int percentage = FEATURE_VALUES[feature][state];

    switch(feature) {
        case EYES:
            eyes.setTargetPercentage(percentage);
            break;

        case MOUTH:
            mouth.setTargetPercentage(percentage);
            break;

        default:
            break;
    }
}

