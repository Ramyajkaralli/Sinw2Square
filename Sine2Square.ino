#define NUM_LEDS     8

int delayTime = 100;                                    // duration to pause
int latchPin = 5;                                       // setting the latch LOW will send the 8 bits in storage to the output pins
int clockPin = 6;                                       // the pin connected to the clock pin, SRCLK (pin 11 of the shift register)
int dataPin = 4;                                        // the pin connected to the serial data pin, SER (pin 14 of the shift register)

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

/******** function which sends the stored byte to the output pins by setting the latch pin LOW************/
void updateShiftRegister(byte storageByte)
{
  // set the latch pin LOW
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, storageByte);    // send the storage byte to the shift register with the LSB first
  
  digitalWrite(latchPin, HIGH);                          // set the latch pin HIGH again
}

/******* The code in here will run continuously until we turn off the Arduino Dock*******/
void loop()
{
  byte storageByte = 0x01;                              // initialize to 00000001, representing the first LED on

  for (int i = 0; i < NUM_LEDS-1; i++)
  {
    updateShiftRegister(storageByte);                   // send the 8 bits to the shift register and set latch LOW

    storageByte = storageByte << 1;                     // bitwise shift to the left by 1 bit

    delay(delayTime);   
  }

  for (int i = 0; i < NUM_LEDS-1; i++)
  {
    updateShiftRegister(storageByte);

    storageByte = storageByte >> 1;

    delay(delayTime);   
  }
}
