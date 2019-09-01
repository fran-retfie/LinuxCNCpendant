

void ChangeMode()
{
  MenuFlag ^= 0x01;
  WarnClear();
}


void Start()
{
  MenuTimer = 0;

  lcd.setCursor (0, 0);
  lcd.print("Programm started    ");
}


void Stop()
{
  MenuTimer = 0;
  
  lcd.setCursor (0, 0);
  lcd.print("Programm stopped    ");
}


void Step()
{
  MenuTimer = 0;
  digitalWrite(LED,HIGH);
}


void Pause()
{
  MenuTimer = 0;
  
  lcd.setCursor (0, 0);
  lcd.print("Programm paused    ");
}


void Flood()
{
  MenuTimer = 0;
  MenuFlag ^= 0x02;
  
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x02)
  {
    lcd.print("Flood: ON           ");
  }
  else
  {
    lcd.print("Flood: OFF          ");
  }
}

void Dummy()
{
  
}

void ON()
{
  MenuTimer = 0;
  
  lcd.setCursor (0, 0);
  lcd.print("Machine: ON         ");
}

void OFF()
{
  MenuTimer = 0;
  
  lcd.setCursor (0, 0);
  lcd.print("Machine: OFF        ");
}

void EnableJOG()
{
  
  MenuTimer = 0;
  lcd.setCursor (0, 0);
  MenuFlag |= 0x04;
  if(MenuFlag & 0x01)
  {
    lcd.print("JOG: ENABLED        ");
  }
  else 
  {
    lcd.print("switch to JOG Mode  ");
  }

}

void DisableJOG()
{
  MenuTimer = 0;
  MenuFlag &= ~(0x04);
  lcd.setCursor (0, 0);
  lcd.print("JOG: DISABLED       ");
}
