// change this to make the song slower or faster
int tempo = 150;

int melody[] = {

 // notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
// This code uses PROGMEM to fit the melody to flash as it was to long to fit
// in SRAM. It may not work on other Arduino arquitectures other than AVR
  
  
  NOTE_G5, 4, NOTE_C6, 8, NOTE_D6, 8, NOTE_C6, 8, NOTE_D6, 8, NOTE_E6, 8, NOTE_D6, 8, NOTE_E6, 8,
  NOTE_G6, 2, NOTE_A7, 4, NOTE_F7, 8, NOTE_E7, 8, NOTE_G6, 8, NOTE_E6, 8, NOTE_D6, 8, NOTE_C6, 8,
  NOTE_G5, 8, NOTE_E5, 8, NOTE_C5, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_E4, 4, NOTE_C4, 4, NOTE_G4, 2,
  NOTE_G5, 2, NOTE_G4, 8, NOTE_G5, 8, NOTE_A4, 4, NOTE_A5, 4, NOTE_F5, 4, NOTE_F6, 4, NOTE_C5, 2 
};
