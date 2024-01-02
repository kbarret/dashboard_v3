void displayTime(){ //Screen 1 
  clearLCD(1);
  displayHour();
  displayDate();
}
// Call the EMUcan lib with every received frame:
if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
  emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
 }

// Serial out every second:
currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
  previousMillis = currentMillis;
  if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND) || testDisplay == true {
    
    void displayPerf1(){ //Screen 2
      clearLCD(2);
      cursor(0,0);
      lcd.print("Lambda:");
      lcd.print(emucan.emu_data.wboLambda);
      
      cursor(0,1);
      lcd.print("Target:");
      lcd.print(emucan.emu_data.lambdaTarget);
      
      cursor(0,2);
      lcd.print("MAP:");
      lcd.print(emucan.emu_data.MAP);
      if(emucan.emu_data.MAP < 100){
        lcd.print(" ");
      }
      
      cursor(0,3);
      lcd.print("IAT:");
      lcd.print(emucan.emu_data.IAT);
      if(emucan.emu_data.IAT < 100){
        lcd.print(" ");
      }
      if(emucan.emu_data.IAT < 10){
        lcd.print(" ");
      } 
    }
    void displayPerf2(){ //Screen 3
      clearLCD(3); 
      
      cursor(0,0);
      lcd.print("Vitesse:");
      lcd.print(emucan.emu_data.vssSpeed);
      if(emucan.emu_data.vssSpeed < 100){
        lcd.print(" ");
      }
      if(emucan.emu_data.vssSpeed < 10){
        lcd.print(" ");
      }
           
      cursor(0,1);
      lcd.print("RPM:");
      lcd.print(emucan.emu_data.RPM);
      if(emucan.emu_data.RPM < 1000){
        lcd.print(" ");
      }
      if(emucan.emu_data.RPM < 100){
        lcd.print(" ");
      }
      if(emucan.emu_data.RPM < 10){
        lcd.print(" ");
      }
          
      cursor(0,2);
      lcd.print("CLT:");
      lcd.print(emucan.emu_data.CLT);
      if(emucan.emu_data.CLT < 100){
        lcd.print(" ");
      }
      if(emucan.emu_data.CLT < 10){
        lcd.print(" ");
      }
      
      cursor(0,3);
      lcd.print("Batt:");
      lcd.print(emucan.emu_data.Batt);
      
      cursor(14,0);
      lcd.print("MODE:");      
      if (emucan.emu_data.flags1 & emucan.F_TABLE_SET) {
        lcd.print("H");     
      }
      else{
        lcd.print("S"); 
      }
      
      cursor(14,1);
      lcd.print("GEAR:");      
      lcd.print(emucan.emu_data.gear);
    }

    void displayPerf3(){ //Screen 4
      clearLCD(4);
      
      cursor(0,0);     
      lcd.print("EGT:");
      lcd.print(emucan.emu_data.Egt1); 
      
      cursor(0,1);
      lcd.print("Ign:");
      lcd.print(emucan.emu_data.IgnAngle);

      cursor(0,2);
      lcd.print("Instant:");
      if(emucan.emu_data.vssSpeed > 20){
        lcd.print(conso,1);
        if(conso < 10){
          lcd.print(" ");
        }
      }
      else{
        lcd.print("... ");
      }
      
      cursor(0,3);
      lcd.print("Average:");
      lcd.print(consoAverage,1);
          
      cursor(14,0);
      lcd.print("MODE:");      
      if (emucan.emu_data.flags1 & emucan.F_TABLE_SET) {
        lcd.print("H");     
      }
      else{
        lcd.print("S"); 
      }
      
      cursor(14,1);
      lcd.print("GEAR:");      
      lcd.print(emucan.emu_data.gear);
    }           
  }
}

else {
  lcd.clear
  cursor(0,0);
  lcd.print("No communication");
}
