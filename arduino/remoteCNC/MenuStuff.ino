

void ChangeMode()
{
  switch(MenuFlag & 0x03)
  {
  case 0x00:
    SerialUSB.write('G');
  break;

  case 0x01:
    SerialUSB.write('A');
  break;

    case 0x02:
    SerialUSB.write('M');
  break;
  }
  lcd.setCursor (0, 0);
  lcd.print("Switching Mode      ");
  MenuFlag |= 0x20;
}


void Start()
{
  MenuTimer = 0;
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x10)
  {
    if(MenuFlag &= 0x02)
    {
      lcd.print("Programm started    ");
      SerialUSB.write('S');
    }
    else lcd.print("not in AUTO mode    ");  
  }
  else   lcd.print("turn on the machine "); 
}


void Stop()
{
  MenuTimer = 0;
  
  lcd.setCursor (0, 0);
  lcd.print("Programm alted      ");
  SerialUSB.write('T');  
}


void Step()
{
  MenuTimer = 0;
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x10)
  {
    if(MenuFlag &= 0x02)
    {
      digitalWrite(LED,HIGH);
      SerialUSB.write('P');
    }
    else lcd.print("not in AUTO mode    ");
  }
  else   lcd.print("turn on the machine ");
}


void Pause()
{
  MenuTimer = 0;
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x10)
  {
    if(MenuFlag &= 0x02)
    {
      lcd.print("Programm paused    ");
      SerialUSB.write('E');
    }
    else lcd.print("not in AUTO mode    ");
  }
  else   lcd.print("turn on the machine ");
}


void Flood()
{
  MenuTimer = 0;
  MenuFlag ^= 0x04;
  
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x04)
  {
    lcd.print("Flood: ON           ");
    
    SerialUSB.write('F');
  }
  else
  {
    lcd.print("Flood: OFF          ");
    
    SerialUSB.write('f');
  }
}

void Dummy()
{
  
}

void ON()
{
  MenuTimer = 0;
  MenuFlag |= 0x10;
  lcd.setCursor (0, 0);
  lcd.print("Machine: ON         ");

  SerialUSB.write('O');
}

void OFF()
{
  MenuTimer = 0;
  MenuFlag &= ~(0x18);
  lcd.setCursor (0, 0);
  lcd.print("Machine: OFF        ");

  SerialUSB.write('o');
}

void EnableJOG()
{  
  MenuTimer = 0;
  
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x10)
  {
    if(MenuFlag & 0x01)
    {
      lcd.print("JOG: ENABLED        ");
      MenuFlag |= 0x08;
      SerialUSB.write('J');
    }
    else lcd.print("not in JOG Mode     ");
  }
  else   lcd.print("turn on the machine ");
}

void DisableJOG()
{
  MenuTimer = 0;
  if(MenuFlag & 0x08)
  {
    MenuFlag &= ~(0x08);
    lcd.setCursor (0, 0);
    lcd.print("JOG: DISABLED       ");
    SerialUSB.write('j');
  }
}
