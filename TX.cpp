



DAS_CONTROLLER::DAS_CONTROLLER()
  : received_id[3]('/0')
  , CS[4]('/0')
  , receive_length[3]('/0')
  , first(0)
  , last(17-1)
  , middle(first+last/2)


bool DAS_CONTROLLER::transmit(uint8_t data_id,uint16_t send_data[],unit8_t data_size){

  Serial1.print("$M<");
  Serial1.print(data_size);
  transmit_running_xor=data_size;
  Serial1.print(data_id);
  transmit_running_xor^=data_id;
  for(int i=0;i<data_size;i++){
    Serial1.print(send_data[i]);
    transmit_running_xor^=rc_data[i];
    }
  Serial1.print(transmit_running_xor);
  return transmit_successful;
  }
