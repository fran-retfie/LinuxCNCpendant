


void readContacts()
{
  //read from pins and write to contacts reg
  unsigned char Dval = 0x00;
  
  if(digitalRead(D0)) Dval |= 0x01;
  if(digitalRead(D1)) Dval |= 0x02;
  if(digitalRead(D2)) Dval |= 0x04;
  if(digitalRead(D3)) Dval |= 0x08;

  Contacts &= ~( ((unsigned int) 0x000F) << SelFlag );    //clear old data
  Contacts |= ( ((unsigned int) Dval) << SelFlag );       //write new data

  //read jog buttons
  JogButtons = 0x00;
  if(digitalRead(sw1)) JogButtons |= 0x01;
  if(digitalRead(sw2)) JogButtons |= 0x02;
}


void readAnalog()
{
  int aV0 = analogRead(A5);
  int aV1 = analogRead(A4);
  int aV2 = analogRead(A3);
  Pot2 = analogRead(A2);
  Pot3 = analogRead(A1);

  if(SelFlag & 0x08)
  {
    JogX = aV0;
    JogZ = aV1;
    Pot0 = aV2;
  }
  else
  {
    JogY = aV0;
    JogA = aV1;
    Pot1 = aV2;    
  }
}

void writeSel()
{
  //update SelFLag
  SelFlag += 0x04;
  if(SelFlag & 0xF0) SelFlag = 0;
  
  //write SelFLag to pins
  digitalWrite(D_SEL, SelFlag & 0x04);
  digitalWrite(ANA_SEL, SelFlag & 0x08); 
}

void SendInt(int val)
{
  char arr[2];
  arr[0] = (char) (val    & 0xFF);
  arr[1] = (char) (val>>8 & 0xFF);

  SerialUSB.write(arr[0]);
  SerialUSB.write(arr[1]);
}
