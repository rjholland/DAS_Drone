/* Dynamic Automated Sytems
   MSP Compatible Drone Controller
   Author: Reece Holland
   
   Primary Header File.
*/



#ifndef das_drone.h
#define das_drone.h

//Standard Librarys
#include <stdlib.h>

//Custom Files
#include <rx.cpp>
#include <tx.cpp>
#include <das_drone.cpp>
#include <math_func.cpp>

//From flight controller
#define MSP_IDENT 100,
#define MSP_STATUS 101
#define MSP_RAW_IMU 102
#define MSP_SERVO 103
#define MSP_MOTOR 104
#define MSP_RC 105
#define MSP_RAW_GPS 106
#define MSP_COMP_GPS 107
#define MSP_ATTITUDE 108
#define MSP_ALTITUDE 109
#define MSP_ANALOG 110
#define MSP_RC_TUNING 111
#define MSP_PID 112
#define MSP_BOX 113
#define MSP_MISC 114
#define MSP_MOTOR_PINS 115
#define MSP_BOXNAMES 116
#define MSP_PIDNAMES 117
#define MSP_WP 118
#define MSP_SERVO_CONF 120
#define MSP_BOXIDS 119


//To flight controller
#define MSP_SET_MOTOR 214
#define MSP_SET_RAW_RC 200
#define MSP_SET_RAW_GPS 201
#define MSP_SET_RC_TUNING 204
#define MSP_SET_PID 202
#define MSP_SET_BOX 203
#define MSP_SET_MISC 207
#define MSP_SET_SERVO_CONF 212
#define MSP_ACC_CALIBRATION 205
#define MSP_MAG_CALIBRATION 206
#define MSP_RESET_CONF 208
#define MSP_SELECT_SETTING 210
#define MSP_SET_HEAD 211
#define MSP_BIND 240
#define MSP_EEPROM_WRITE 250

//Prototypes
void setup();
void InitIO();
void loop();
void DataUpdate();
uint16_t control_mapper(uint16_t signal,uint8_t factor);
float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve);
bool DAS_CONTROLLER::transmit(uint8_t data_id,uint16_t send_data[],unit8_t data_size);
bool DAS_CONTROLLER::receive(char received_byte,uint *parsed_data_bytes);

class DAS_CONTROLLER{
  private:
    uint8_t running_checksum;
    bool sentence_begin;
    bool transmit_successful;
    uint8_t transmit_running_xor;
    uint8_t sentence_length;
    char received_id[4];
    char received_length[4];
    uint8_t first;
    uint8_t last;
    uint8_t middle;
    uint8_t n;
    uint8_t data_length;
    uint8_t receive_running_xor;
    unit8_t received_data_bytes;
    char CS[4];
    
}
#endif
