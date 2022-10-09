/*
  MIDI message:
  https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
*/


void MIDImessage(byte status, byte data1, byte data2)
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}


// POTENTIOMETERS //

const int pot1 = A0;  // potentiometer pins
int potVal1 = 0;
int lastPotVal1 = 0;


void readPots() {

  int diff = 2; // difference amount

  // READ POTENTIOMETERS //
  
  potVal1 = analogRead(pot1);
  // CALCULATE DIFFERENCE BETWEEN NEW VALUE AND LAST RECORDED VALUE //
  
  int potVal1diff = potVal1 - lastPotVal1;

  // SEND MIDI MESSAGE //
  
  if (abs(potVal1diff) > diff) // execute only if new and old values differ enough
  {
    MIDImessage(176, 0, map(potVal1, 0, 1023, 0, 127)); // map sensor range to MIDI range
    lastPotVal1 = potVal1; // reset old value with new reading
  }
  
  delay(5); // small delay further stabilizes sensor readings

}

void setup() {

  Serial.begin(9600); // enable serial communication
  
}

void loop() {
  readPots();         // read potentiometers
}
