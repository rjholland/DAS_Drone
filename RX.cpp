




bool DAS_CONTROLLER::receive(char received_byte){
  bool valid_sentence=false;
  switch(received_byte){
    case',':
      running_checksum^=received_byte;
    case'$':
      sentence_begin=true;
    
