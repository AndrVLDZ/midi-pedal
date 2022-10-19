/*
  MIDI message:
  https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
*/

void setup() {
  Serial.begin(9600); // enable serial communication
}

void MIDImessage(byte status, byte data1, byte data2)
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

// POTENTIOMETERS //
const int pot_1 = A0;  // potentiometer_1 pin
int potVal_1 = 0;
int lastPotVal_1 = 0;

const int pot_2 = A1;  // potentiometer_2 pin
int potVal_2 = 0;
int lastPotVal_2 = 0;

void readPots() {
  int diff = 8; // difference amount
  // READ POTENTIOMETERS //
  potVal_1 = analogRead(pot_1);
  potVal_2 = analogRead(pot_2);
  
  // CALCULATE DIFFERENCE BETWEEN NEW VALUE AND LAST RECORDED VALUE //
  int pot_diff_1 = potVal_1 - lastPotVal_1;
  int pot_diff_2 = potVal_2 - lastPotVal_2;

  // SEND MIDI MESSAGE //
  if (abs(pot_diff_1) > diff) // execute only if new and old values differ enough
  {
    MIDImessage(177, 1, map(potVal_1, 0, 1023, 0, 127)); // map sensor range to MIDI range
    lastPotVal_1 = potVal_1; // reset old value with new reading
  }
  
  if (abs(pot_diff_2) > diff)
  {
    MIDImessage(177, 2, map(potVal_2, 0, 1023, 0, 127)); // map sensor range to MIDI range
    lastPotVal_2 = potVal_2; // reset old value with new reading
  }
  
  delay(5); // small delay further stabilizes sensor readings
}

void loop() {
  readPots();         // read potentiometers
}
