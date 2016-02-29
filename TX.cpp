



DAS_CONTROLLER::DAS_CONTROLLER()
  : received_id[3]('/0')
  , first(0)
  , last(n-1)
  , middle(first+last/2)


bool transmit(uint8_t data_id,uint16_t rc_data[],unit8_t data_size){

  Serial1.print("$M<");
  Serial1.print(data_size);
  transmit_running_xor=data_size;
  Serial1.print(data_id);
  transmit_running_xor^=data_id;
  for(int i=0;i<data_size;i++){
    Serial1.print(rc_data[i]);
    transmit_running_xor^=rc_data[i];
    }
  Serial1.print(transmit_running_xor);
  return transmit_successful;
  }
