


struct SEND_DATA_STRUCTURE{
uint16_t raw_rc[8];
};

SEND_DATA_STRUCTURE stream;

int frequency = 30;

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
#define array_length 16
#define message_id 200


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
    transmit(selected_id,stream.raw_rc,length_in_bytes);  //read the buttons and the joysticks data
    DataUpdate();
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

float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  /*
   Serial.println(curve * 100, DEC);   // multply by 100 to preserve resolution  
   Serial.println();
   */

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float


  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {  
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
}
