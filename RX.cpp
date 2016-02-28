




bool DAS_CONTROLLER::receive(char received_byte){
  bool valid_sentence=false;
  if ((sentence_length>3)&&(sentence_length<6)){
    received_id[sentence_length-3];
    sentence_length++;
  }
  else if(sentence_length==6){
    retrieve_id_structure();
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
  
  bool DAS_CONTROLLER::retrieve_id_structure(){
    switch()
  }
