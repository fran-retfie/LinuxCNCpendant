
const unsigned char LCDsize = 20;

void LCD_progress_bar_init()
{   
  /* LCD Progress Bar Characters, create your custom bars */

  byte bar1[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
  byte bar2[8] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
  byte bar3[8] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
  byte bar4[8] = { 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
  byte bar5[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
  lcd.createChar(1, bar1);
  lcd.createChar(2, bar2);
  lcd.createChar(3, bar3);
  lcd.createChar(4, bar4);
  lcd.createChar(5, bar5);
}

void LCD_progress_bar (int row, int var, int minVal, int maxVal)
{
  int block = map(var, minVal, maxVal, 0, LCDsize);         // Block represent the current LCD space (modify the map setting to fit your LCD)
  int line = map(var, minVal, maxVal, 0, (LCDsize*5));      // Line represent the theoretical lines that should be printed
  int bar = (line-(block*5));                               // Bar represent the actual lines that will be printed

  lcd.setCursor (0, row);
  for (int x = 0; x < block; x++) lcd.write(1023);
                           
  if (bar != 0) lcd.write (bar);
  if (block == 0 && line == 0) lcd.write(1022); 
 
  for (int x = (block+1); x < LCDsize; x++) lcd.write (1022);
}


void WarnClear()
{
  lcd.setCursor (0, 0);
  if(MenuFlag & 0x01)   lcd.print("JOG Mode            ");
  else                  lcd.print("MDI Mode            ");
  lcd.setCursor (0, 1);
  lcd.print("X:");
  lcd.setCursor (0, 2);
  lcd.print("Y:");
  lcd.setCursor (0, 3);
  lcd.print("Z:");
}
