
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

void SendData();

const int WarnTIME = 200;
const int LedTIME = 7;
unsigned char MenuFlag = 0x00;
int MenuTimer = 0;

void WarnClear();

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

  SerialUSB.begin(9600);

  lcd.begin(20, 4); 
  LCD_progress_bar_init();

  lcd.setCursor (0, 0);
  lcd.print("CNC pendant v1.0");
}

void loop() 
{ 
  readContacts();
  readAnalog();
  writeSel();

  posedgeContacts = Contacts & ~oldContacts;
  negedgeContacts = ~Contacts & oldContacts;
  oldContacts = Contacts;

  for(unsigned char i = 0; i<16; i++)
  {
    if(posedgeContacts & (0x01<<i)) (*PressEvents[i]) ();
    if(negedgeContacts & (0x01<<i)) (*RelaseEvents[i]) ();
  }
  
  MenuTimer++;
  
  if(MenuTimer > LedTIME)
  {
    digitalWrite(LED,LOW);
  }
  
  if(MenuTimer > WarnTIME)
  {
    WarnClear();
    MenuTimer = 0;
  }
  
  if(SerialUSB.read() != -1)
  {  
    SendData();
  }

  delay(10);
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
