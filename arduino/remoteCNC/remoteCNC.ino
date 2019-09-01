
#include <LiquidCrystal.h>


const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
const int sw1 = 6, sw2 = 7;
const int D3 = 8, D2 = 9, D1 = 10,  D0 = 11, D_SEL = 12, ANA_SEL = 13;
const int LED = 38;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void SendInt(int val);

unsigned char SelFlag = 0x00;
void writeSel();

unsigned int Contacts = 0x0000;
unsigned int oldContacts = 0x0000;
unsigned int posedgeContacts = 0x0000;
unsigned int negedgeContacts = 0x0000;
unsigned char JogButtons = 0x00;
void readContacts();

int Pot0 = 0x0000;
int Pot1 = 0x0000;
int Pot2 = 0x0000;
int Pot3 = 0x0000;
int JogX = 0x0000;
int JogY = 0x0000;
int JogZ = 0x0000;
int JogA = 0x0000;
void readAnalog();


int Pot0old = 0x0000;
int Pot1old = 0x0000;
int Pot2old = 0x0000;
int Pot3old = 0x0000;

float posX = 0;
float posY = 0;
float posZ = 0;

void SendData();

const int WarnTIME = 1000;
const int LedTIME = 70;
unsigned char MenuFlag = 0x00;
int MenuTimer = 0;

const int DebounceTime = 10;
int DebounceTimer = 0;

const int JogTime = 10;
int JogTimer = 0;


void PrintMode();
void PrintPosition();

void ChangeMode();
void Start();
void Stop();
void Step();
void Pause();
void Flood();
void ON();
void OFF();
void EnableJOG();
void DisableJOG();
void Dummy();

typedef void (* GenericFP)(void);
GenericFP PressEvents[16] = {Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Pause, Dummy, Flood, Dummy, EnableJOG, ON, Start, ChangeMode, Stop, Step};
GenericFP RelaseEvents[16] = {Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, DisableJOG, OFF, Dummy, Dummy, Dummy, Dummy};


void setup() 
{
  analogReadResolution(12);

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D_SEL, OUTPUT);
  pinMode(ANA_SEL, OUTPUT);
  
  pinMode(LED, OUTPUT);

  SerialUSB.begin(115200, SERIAL_8E1);

  lcd.begin(20, 4); 
  LCD_progress_bar_init();

  lcd.setCursor (0, 0);
  lcd.print("CNC pendant v1.0");
  lcd.setCursor (0, 1);
  lcd.print("have a good day and");
  lcd.setCursor (0, 2);
  lcd.print("I hope you don't ");
  lcd.setCursor (0, 3);
  lcd.print("break any endmill");
}

void loop() 
{ 
  readContacts();
  readAnalog();
  writeSel();


  DebounceTimer++;
  if(DebounceTimer > DebounceTime)
  {
    DebounceTimer = 0;
    
    posedgeContacts = Contacts & ~oldContacts;
    negedgeContacts = ~Contacts & oldContacts;
    oldContacts = Contacts;

    for(unsigned char i = 0; i<16; i++)
    {
      if(posedgeContacts & (0x01<<i)) (*PressEvents[i]) ();
      if(negedgeContacts & (0x01<<i)) (*RelaseEvents[i]) ();
    }

    if(abs(Pot0 - Pot0old)>20)
    {
      SerialUSB.write('0');
      SendInt(Pot0);
      Pot0old = Pot0;
    }

    if(abs(Pot1 - Pot1old)>20)
    {
      SerialUSB.write('1');
      SendInt(Pot1);
      Pot1old = Pot1;
    }

    if(abs(Pot2 - Pot2old)>20)
    {
      SerialUSB.write('2');
      SendInt(Pot2);
      Pot2old = Pot2;
    }

    if((abs(Pot3 - Pot3old)>20) && (MenuFlag & 0x08))
    {
      SerialUSB.write('3');
      SendInt(4096 - Pot3);
      Pot3old = Pot3;
    }

  }
  
  PrintMode();
  
  if(SerialUSB.available() > 0)
  {
    switch(SerialUSB.read())
    {
      case 'A':
        if((MenuFlag && 0x03) != 0x02)  PrintMode();
        MenuFlag &= ~(0x2B);
        MenuFlag |= 0x02;
        PrintPosition();
      break;

      case 'M':
        if((MenuFlag && 0x03) != 0x00)  PrintMode();
        MenuFlag &= ~(0x2B);
        MenuFlag |= 0x00;
        PrintPosition();
      break;

      case 'J':
        if((MenuFlag && 0x03) != 0x01)  PrintMode();
        MenuFlag &= ~(0x23);
        MenuFlag |= 0x01;
        PrintPosition();
      break;

      case 'I':
        char inStr[21];
        SerialUSB.readBytes(inStr, 20);
        inStr[20] = 0x00;
        MenuTimer = 0;
        lcd.setCursor (0, 0);
        lcd.print(inStr);
      break;

      case 'R':
        if(MenuFlag && 0x08)
        {
          SerialUSB.write('R');
          SendInt(JogX);
          SendInt(JogY);
          SendInt(JogZ);
          SendInt(JogA);
        } 
      break;

      default:
      break;
    }
  }

  delay(1);
}




void SendData()
{
    SerialUSB.write(0x55);
    SerialUSB.write(JogButtons);
    SendInt(Contacts);
    SendInt(Pot0);
    SendInt(Pot1);
    SendInt(Pot2);
    SendInt(Pot3);
    SendInt(JogX);
    SendInt(JogY);
    SendInt(JogZ);
    SendInt(JogA);
}












//
