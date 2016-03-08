#include <RX_TX.h>




bool DAS_CONTROLLER::transmit(uint8_t data_id,uint16_t send_data[],uint8_t data_size){

  Serial1.print('$M<');
  Serial1.print(data_size);
  transmit_running_xor=data_size;
  Serial1.print(data_id);
  transmit_running_xor^=data_id;
  for(int i=0;i<data_size;i++){
    Serial1.print(send_data[i]);
    transmit_running_xor^=send_data[i];
    }
  Serial1.print(transmit_running_xor);
  return transmit_successful;
  }

  bool DAS_CONTROLLER::receive(char received_byte,uint16_t *parsed_data_bytes){
  
  bool valid_sentence=false;
  if ((sentence_length>=(8+data_length))&&(sentence_length>(8+3+data_length))){
    CS[data_length-8]=received_byte;
    sentence_length++;
      if(sentence_length==(data_length+11)){
         if((atoi(CS)!=receive_running_xor))
         return valid_sentence;
      }
  }
  else if ((sentence_length>=8)&&(sentence_length<=(8+data_length))){
      parsed_data_bytes[sentence_length-8]=received_byte;
      sentence_length++;
  }
   else if ((sentence_length>3)&&(sentence_length<6)){             //Assuming size is sent in format 016-1byte
      received_length[sentence_length-4]=received_byte;
      sentence_length++;
         if (sentence_length==6){
            parsed_data_bytes=(uint16_t*)calloc(atoi(received_length),sizeof(uint16_t));
			}
			}
  else if ((sentence_length>5)&&(sentence_length<8)){                //Use transmitted length to assign bytes via malloc
    received_id[sentence_length-6];
    sentence_length++;
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
  }
  }
