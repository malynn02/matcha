#include <Wire.h>         // I2C Library for Accelerometer
#define ADDR 0x18         // I2C Address for Accelerometer

void initAccel(){
  Wire.begin(33, 32);   // Change SDA/SCL Assignments
  //Serial.println("Accel Attached!");
}

// Read the Accelerometer of a Given Axis 
int readAccel(int a){
  uint8_t r1, r2;
  if(a == 0){r1 = 0x02; r2 = 0x03;} // X Axis 
  if(a == 1){r1 = 0x04; r2 = 0x05;} // Y Axis 
  if(a == 2){r1 = 0x06; r2 = 0x07;} // Z Axis 

  int accel;
  byte LSB = i2c_readRegisterByte(ADDR, r1);
  byte MSB = i2c_readRegisterByte(ADDR, r2);

  LSB = LSB & 0b11110000;           // Mask away 4 lower bytes of LSB
  accel = (((int)MSB) << 8) | LSB;  // Combine LSB and MSB

  return accel;
}

byte i2c_readRegisterByte (uint8_t deviceAddress, uint8_t registerAddress) {
  byte registerData;
  Wire.beginTransmission(deviceAddress);              // set sensor target
  Wire.write(registerAddress);                        // set memory pointer
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)deviceAddress, (uint8_t)1); // request one byte
  registerData = Wire.read(); 
  return registerData;           // the returned byte from this function is the content from registerAddress
}

byte i2c_writeRegisterByte (uint8_t deviceAddress, uint8_t registerAddress, uint8_t newRegisterByte)  {
  byte result;
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);  
  Wire.write(newRegisterByte); 
  result = Wire.endTransmission(); // Wire.endTransmission(); returns 0 if write operation was successful

  if(result > 0) {Serial.print(F("FAIL in I2C register write! Error code: "));Serial.println(result);}
  return result;
}

byte i2c_setRegisterBit (uint8_t deviceAddress, uint8_t registerAddress, uint8_t bitPosition, bool state){ 
  byte registerByte, result;
  registerByte = i2c_readRegisterByte ( deviceAddress,  registerAddress ); // load the current register byte

  if (state) {   // when state = 1
    registerByte |= (1 << bitPosition);   //bitPosition of registerByte now = 1
  }  
  else {
    registerByte &= ~(1 << bitPosition);   // bitPosition now = 0
  }
  result = i2c_writeRegisterByte ( deviceAddress,  registerAddress,  registerByte );
  return result;   // result = 0 if the byte was successfully written to the register
}

void printByte(int b, int n){
  for(int i = (n - 1); i >= 0; i--){Serial.print(bitRead(b,i));}  
  Serial.println();
}
