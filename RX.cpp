




bool DAS_CONTROLLER::receive(char received_byte,uint *parsed_data_bytes){
  
  bool valid_sentence=false;
  if ((sentence_length>5)&&(sentence_length<(6+data_length)))
    *parsed_data_bytes[sentence_length-6]=received_byte;
    sentence_length++;
  else if ((sentence_length>3)&&(sentence_length<6)){
    received_id[sentence_length-3];
    sentence_length++;
  }
  else if(sentence_length==6){
    data_length=retrieve_id_structure(atoi(received_id))
    *parsed_data_bytes=malloc(data_length);
  }
  else{ 
  switch(received_byte){
    case'$':
      sentence_begin=true;
      sentence_length++;
    case'M':
      sentence_length++;
    case'<':
      sentence_length++;
  }
  
  bool DAS_CONTROLLER::retrieve_id_structure(unit8_t id){
   uint8_t msp_structure[][]{{MSP_IDENT,7},{MSP_STATUS,11},{MSP_RAW_IMU,18},{MSP_SERVO,32},{MSP_MOTOR,32},{MSP_RC,32},{MSP_RAW_GPS,16},
                          {MSP_COMP_GPS,5},{MSP_ATTITUDE,6},{MSP_ALTITUDE,6},{MSP_ANALOG,7},{MSP_RC_TUNING,7},{MSP_PID,30},{MSP_BOX,20},
                          {MSP_MISC,22},{MSP_MOTOR_PINS,8},{MSP_SERVO_CONF,56}};
     while (first <= last) {
      if (msp_structure[middle][0] < id)
         first = middle + 1;    
      else if (msp_structure[middle][0] == id) {
         return (msp_structure[middle+1][1])
      }
      else
         last = middle - 1;
      middle = (first + last)/2;
   }
    
  }
