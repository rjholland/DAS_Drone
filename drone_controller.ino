#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#include <RX_TX.h>
#include <math_func.h>


struct SEND_DATA_STRUCTURE{
uint16_t raw_rc[8];
};

SEND_DATA_STRUCTURE stream;

int frequency = 30;
bool rc_active=false;
uint8_t array_length=200;
#define virbrationMotorPin 2
#define control_factor 3
#define zero 800
#define full 2000
#define neutral 1500
#define mid_upper_range 523
#define max_range 1023
#define mid_lower_range 500
#define max_height_dif 100
#define max_height_dif_thrust 100
#define height_lock_factor 0

#define rc_control_id 200
DAS_CONTROLLER DS;
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  InitIO();             //Initialize the inputs/outputs and the buffers
  
}

void InitIO() {
  for (int i = 0; i < 5; i++) pinMode(i, INPUT);
  pinMode(virbrationMotorPin, OUTPUT);
  digitalWrite(virbrationMotorPin, LOW); // Stop shacking of the gamepad
}

uint32_t timer = 0;

void loop()
{
  if (millis() - timer > frequency) { // manage the updating freq of all the controlling information
    DataUpdate();
    DS.transmit(rc_control_id,stream.raw_rc,array_length);
    timer = millis();
  }
}
     
void DataUpdate() {
 for (int i = 0; i < 4; i++)
    stream.raw_rc[i] = control_mapper(analogRead(i + 2),control_factor);
}

uint16_t control_mapper(uint16_t signal,uint8_t factor){
 uint16_t augmented_signal;
 if (signal < mid_lower_range)
   augmented_signal=fscale(0,mid_lower_range,1000,1500,signal,(factor*-1));
 else if (signal > mid_upper_range)
   augmented_signal=fscale(mid_upper_range,max_range,1500,2000,signal,factor);
 else
   augmented_signal=neutral;
 return(augmented_signal);
}
