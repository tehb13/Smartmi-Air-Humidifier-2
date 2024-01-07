#include <TouchKey.h>

byte Tray[] = {0xFA, 0x29, 0x03, 0x00, 0x00, 0x00, 0x00, 0x14, 0x9A, 0x00, 0x00, 0x00, 0x03, 0x77, 0x72, 0x71, 0x03, 0x00, 0x6C, 0x4C, 0x3B, 0x03, 0x2F, 0x15, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x03, 0xE8, 0x00, 0x2c, 0x02, 0x6D, 0x37, 0xD2, 0x00};
byte checksum;
byte SensorMap;
int SensorRaw;
extern volatile __xdata uint16_t touchRawValue[];

void setup()                    
{
  Serial0_begin(9600);
  TouchKey_begin(1 << 1); 
}

void loop()                    
{    
  SensorRaw = touchRawValue[1];
  
  if(SensorRaw < 3) SensorMap = 125; 
  else SensorMap = constrain(map(SensorRaw, 5555, 5, 0, 120), 0, 120);

  Tray[11] = SensorMap;
  checksum = 0;

  for(int i = 0; i < 42; i++) checksum ^= Tray[i];

  checksum ^= 0xA0;
  Tray[42] = checksum;

  int e = sizeof(Tray);
  for(int i = 0; i < e; i++) Serial0_write(Tray[i]);
  
  delay(100);
}
