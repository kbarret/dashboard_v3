void actionButton(){
  Serial.println(analogRead(A1));
  if(13 < analogRead(A1) && analogRead(A1) < 17 && table[0] == false){
    displaySelect++;
    if(displaySelect > numberOfScreen){
      displaySelect = 1;
    }
    table[0] = true;
  }
  if(analogRead(A1) > 1000 && table[0] == true){
    table[0] = false;
  }

 
  if(digitalRead(switchClutch) == HIGH && table[12] == false){
    Serial.println("clutch");
    canMsg2.can_id = 0x500;
    canMsg2.can_dlc = 2;
    canMsg2.data[0] = 0xFF;
    mcp2515.sendMessage(&canMsg2);
    table[12] = true;
  }
  if(digitalRead(switchClutch) == LOW && table[12] == true){
    canMsg2.can_id = 0x500;
    canMsg2.can_dlc = 2;
    canMsg2.data[0] = 0x00;
    mcp2515.sendMessage(&canMsg2);
    table[12] = false;
  }

  if(digitalRead(switchBrake) == HIGH && table[13] == false){
    Serial.println("brake");
    canMsg2.can_id = 0x500;
    canMsg2.can_dlc = 2;
    canMsg2.data[1] = 0xFF;
    mcp2515.sendMessage(&canMsg2);
    table[13] = true;
  }
  if(digitalRead(switchBrake) == LOW && table[13] == true){
    table[13] = false;
    canMsg2.can_id = 0x500;
    canMsg2.can_dlc = 2;
    canMsg2.data[1] = 0x00;
    mcp2515.sendMessage(&canMsg2);
  }
//  if(digitalRead(switchDisplay) == LOW && table[0] == false){
//    displaySelect++;
//    if(displaySelect > numberOfScreen){
//      displaySelect = 1;
//    }
//    table[0] = true;
//  }
//  if(digitalRead(switchDisplay) == HIGH && table[0] == true){
//    table[0] = false;
//  }
  
  if(digitalRead(switchInitTime) == LOW && table[5] == false){
    table[5] = true;
  }
  if(digitalRead(switchInitTime) == HIGH && table[5] == true){
    average = 0;
    sampling = 0;
    consoAverage = 0;
    eepromUpdate();
    table[5] = false;
  }
  valeurA0 = analogRead(A0);
  valeurA1 = analogRead(A1);
 

  if(valeurA0 < 1000 || valeurA1< 1000){
    switch (valeurA0) {
      
    case 33 ... 34:
      canMsg1.can_id = 0x0F6;
      canMsg1.can_dlc = 6;
      canMsg1.data[0] = 0xFF;
      canMsg1.data[1] = 0x00;
      canMsg1.data[2] = 0x00;
      canMsg1.data[3] = 0x00;
      canMsg1.data[4] = 0x00;
      canMsg1.data[5] = 0x00;
      mcp2515.sendMessage(&canMsg1);
      break;
      
    case 13 ... 15:
      canMsg1.can_id = 0x0F6;
      canMsg1.can_dlc = 6;
      canMsg1.data[0] = 0x00;
      canMsg1.data[1] = 0xFF;
      canMsg1.data[2] = 0x00;
      canMsg1.data[3] = 0x00;
      canMsg1.data[4] = 0x00;
      canMsg1.data[5] = 0x00;
      mcp2515.sendMessage(&canMsg1);
      break;
      
    case 23 ... 25:
      canMsg1.can_id = 0x0F6;
      canMsg1.can_dlc = 6;
      canMsg1.data[0] = 0x00;
      canMsg1.data[1] = 0x00;
      canMsg1.data[2] = 0xFF;
      canMsg1.data[3] = 0x00;
      canMsg1.data[4] = 0x00;
      canMsg1.data[5] = 0x00;
      mcp2515.sendMessage(&canMsg1);
      break;
    }
    switch (valeurA1) {
      
      case 33 ... 34:
        canMsg1.can_id = 0x0F6;
        canMsg1.can_dlc = 6;
        canMsg1.data[0] = 0x00;
        canMsg1.data[1] = 0x00;
        canMsg1.data[2] = 0x00;
        canMsg1.data[3] = 0xFF;
        canMsg1.data[4] = 0x00;
        canMsg1.data[5] = 0x00;
        mcp2515.sendMessage(&canMsg1);
        break;
        
      case 13 ... 15:
//        canMsg1.can_id = 0x0F6;
//        canMsg1.can_dlc = 6;
//        canMsg1.data[0] = 0x00;
//        canMsg1.data[1] = 0x00;
//        canMsg1.data[2] = 0x00;
//        canMsg1.data[3] = 0x00;
//        canMsg1.data[4] = 0xFF;
//        canMsg1.data[5] = 0x00;
//        mcp2515.sendMessage(&canMsg1);
        break;
        
      case 23 ... 25:
        canMsg1.can_id = 0x0F6;
        canMsg1.can_dlc = 6;
        canMsg1.data[0] = 0x00;
        canMsg1.data[1] = 0x00;
        canMsg1.data[2] = 0x00;
        canMsg1.data[3] = 0x00;
        canMsg1.data[4] = 0x00;
        canMsg1.data[5] = 0xFF;
        mcp2515.sendMessage(&canMsg1);
        break;
    }
   }
   else{
    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 6;
    canMsg1.data[0] = 0x00;
    canMsg1.data[1] = 0x00;
    canMsg1.data[2] = 0x00;
    canMsg1.data[3] = 0x00;
    canMsg1.data[4] = 0x00;
    canMsg1.data[5] = 0x00;
    mcp2515.sendMessage(&canMsg1);
   }
}
