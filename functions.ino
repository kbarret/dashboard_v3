void initDisplay(){
  lcd.init();
  lcd.backlight();
}

void initEmuCan(){
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void initButton(){
  pinMode(switchDisplay, INPUT);
  pinMode(switchInitTime, INPUT);
  pinMode(switchClutch, INPUT);
  pinMode(switchBrake, INPUT);
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  digitalWrite(switchDisplay, HIGH);
  digitalWrite(switchInitTime, HIGH);
  digitalWrite(switchClutch, HIGH);
  digitalWrite(switchBrake, HIGH);
}

void cursor(int colonne, int ligne){
  lcd.setCursor(colonne,ligne);
}

void conditionZero(int valeur, int colonne, int ligne){
  if(valeur < 10){
    lcd.print(0);
    cursor(colonne, ligne);
    lcd.print(valeur);
  }
  else{
    lcd.print(valeur);
  }
}

void displayHour(){
  cursor(0,0);
  conditionZero(myRTC.hours, 1, 0);
  cursor(2,0);
  lcd.print(":");
  cursor(3,0);
  conditionZero(myRTC.minutes, 4, 0);
  cursor(5,0);
  lcd.print(":");
  cursor(6,0);
  conditionZero(myRTC.seconds, 7, 0);
  
}
 
void displayDate(){
  cursor(5,3);
  conditionZero(myRTC.dayofmonth, 6, 3);
  cursor(7,3);
  lcd.print("/");
  cursor(8,3);
  conditionZero(myRTC.month, 9, 3);
  cursor(10,3);
  lcd.print("/");
  cursor(11,3);
  lcd.print(myRTC.year);
}

void displayToLCD(){
  switch(displaySelect){
    case 1:
      displayTime();
      break;
    case 2:
      displayPerf1();
      break;
    case 3:
      displayPerf2();
      break;
    case 4:
      displayPerf3();
      break;
  }  
}

void clearLCD(int screen){
  //Serial.println(table[4]);
  if(table[screen] == false){
    lcd.clear();
    table[screen] = true;
    for(int i = 1; i != numberOfScreen+1; i++){
      if(i != screen){
        table[i] = false;
        
      }     
    }   
  }
}

void calculConso(){
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }
  if(emucan.emu_data.vssSpeed > 20){
    speedVss = emucan.emu_data.vssSpeed;
    rpm = emucan.emu_data.RPM;
    pulseWidth = emucan.emu_data.pulseWidth;
    conso = rpm*pulseWidth;
    conso = conso*120;
    conso = conso/1000;
    conso = conso/60;
    conso = conso*injectorSize;
    conso = conso/1000;
    conso = (conso*100)/speedVss;
    average = average + conso;
    sampling++;
    eepromUpdate();
    consoAverage = average/(sampling/100);
    consoAverage = consoAverage*0.01;
  }
}

void eepromUpdate(){ 
  EEPROM.put(0, average);
  EEPROM.put(8, sampling);
}

void eepromRead(){
  if(EEPROM.read(20) > 100){
    EEPROM.write(20, 0);
    EEPROM.put(0, average);
    EEPROM.put(8, sampling);
    EEPROM.get(0, average);
    EEPROM.get(8, sampling);
  }
  else{
    //EEPROM.write(20, 255);
    EEPROM.get(0, average);
    EEPROM.get(8, sampling);
    consoAverage = average/(sampling/100);
    consoAverage = consoAverage*0.01;
    if(average == 0 && sampling == 0){
      consoAverage = 0;
    }
  } 
}
