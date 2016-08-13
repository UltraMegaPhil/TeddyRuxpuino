#ifndef RUXPIN_H
#define RUXPIN_H

#include "servo_motor.h"

class Ruxpin {
    public:
        enum Feature {
            EYES            = 0,
            MOUTH,

            NUM_FEATURES
        };
    
        enum FeatureStates {
            FULLY_OPEN      = 0,
            THIRD_OPEN,
            THIRD_CLOSED,
            FULLY_CLOSED,

            NUM_STATES
        };

        Ruxpin();
        ~Ruxpin();

        void initialize();
        void update();
        void shutdown();

        void enable();
        void disable();

        void setFeatureState(Feature feature, FeatureStates state);

    private:
        ServoMotor eyes;
        ServoMotor mouth;    
};

#endif

