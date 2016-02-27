




bool DAS_CONTROLLER::receive(char received_byte){
  
  switch(received_byte){
    case',':
      running_checksum^=received_byte;
    case'$':
