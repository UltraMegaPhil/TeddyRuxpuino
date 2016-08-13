#include "ruxpin.h"
#include "serial_debugger.h"
#include <Wire.h>

////////////////////////////////////////////////////////////////////////////////
//
//     Motor control protocol (1 byte)
//     -------------------------------
//
//
//                                    -- Target drive mode    Direct drive mode
//                                    |   0 = Fully open       0 = Stop motors
//                                    |   1 = 2/3 open         1 = Forward
//                                    |   2 = 1/3 open         2 = Reverse
//                                    |   3 = Closed           3 = Invalid
//                                    |                           (stop motors)
//                                    ------
//                                    |    |
//    [ 7 ][ 6 ][ 5 ][ 4 ][ 3 ][ 2 ][ 1 ][ 0 ]
//      |                        |
//      |                        +---------------- Target or direct drive mode
//      -- Feature to be controlled                    0 = Target
//            0 = eyes                                 1 = Direct drive
//            1 = mouth
//
//

//
//
//     Wiring diagram
//     --------------
//
//
// ------+-------------------------+-------------------------------- +5v
// ---+--|-----------------------+-|-------------------------------- GND 
// ---|--|-----------------------|-|-+------------------------------ +3.7v
//    |  |                       | | |
//    |  |                       | | +-> [ VM+]----------|
//    |  |                       | +---> [ Vcc]          |
//    |  |                       +-----> [ GND]          [MOTB] --> Eyes (black)
//    |  |  x[ 10]-----------[  9] ----> [PWMB]          [MOTB] --> Eyes (white)
//    |  |  x[ 11]     A     [  8] ----> [BIN2] ADAFRUIT [ GND]
//    |  |  x[ 12]     R     [  7] ----> [BIN1]          [ GND]
//    |  |  x[ 13]     D     [  6] ----> [STBY]  TB6612  [MOTA] --> Mouth (brown)
//    |  |  x[ A0]     U     [  5] ----> [AIN1]          [MOTA] --> Mouth (red)
//    |  |  x[ A1]     I     [  4] ----> [AIN2]          | 
//    |  |  x[ A2]     N     [  3] ----> [PWMA]----------|
//    |  |  x[ A3]     O     [  2]x 
//    |  +-> [Vcc]           [GND]
//    |     x[RST]    PRO    [RST]x
//    +----> [GND]    MINI   [RX1]  ----+--- Serial debugging
//          x[RAW]-----------[TX0]  ----+
//
//            [ A7] ---------------------------> Mouth motor pot (yellow) 
//            [ A6] ---------------------------> Eyes motor pot (yellow)
//
//            [ A5] ---> I2C (SCL) ---> Raspberry Pi GPIO03
//            [ A4] ---> I2C (SDA) ---> Raspberry Pi GPIO02
//
//
////////////////////////////////////////////////////////////////////////////////



Ruxpin ruxpin;                              // The bear controller
const int I2C_SLAVE_ADDRESS     = 0x04;     // Address "4" on the I2C bus

void setup() {
    // Initialize debugging output
    serial_init();

    // Initialize bear controller
    ruxpin.initialize();
    ruxpin.enable();

    // Initialize I2C as a slave
    Wire.begin(I2C_SLAVE_ADDRESS);
    Wire.onReceive(receiveI2C);
    Wire.onRequest(sendI2C);

    serial_println("Teddy Ruxpin Online!");
}

void loop() {
    ruxpin.update();  
}

void receiveI2C(int byteCount) {
    while(Wire.available()) {
        int readByte = Wire.read();
        if(readByte >= 0) {
            serial_println_val("Received:", byteCount);
            
            Ruxpin::Feature feature     = (Ruxpin::Feature)((readByte & 0x80) >> 7);
            Ruxpin::FeatureStates state = (Ruxpin::FeatureStates)(readByte & 0x03);

            if(feature == Ruxpin::MOUTH) {
                serial_println("  Moving mouth");    
            } else {
                serial_println("  Moving eyes");                
            }
            serial_println_val("    State: ", state);

            ruxpin.setFeatureState(feature, state);
        }
    }
}

void sendI2C() {
    // Nothing required right now    
}

