#include <SPI.h> 
#include <math.h> 
#include <MIDI.h>
#include <EEPROM.h>
 
MIDI_CREATE_DEFAULT_INSTANCE();

/*Static parameters*/
const int PIN_CS = 10;
const int PIN_LDAC = 9;
const int GAIN_1 = 0x1;
const int GAIN_2 = 0x0;

const int PIN_LED = 2; 
const int PIN_GATE1 = 3; 
const int PIN_GATE2 = 5;
const int PIN_MODESWITCH = 7;

const float   CV_SEMINOTE = 1000/12;  //1000mv per octave, 12 seminones, equidistant
const int     CV_OFFSET   = 0;        //digital offset
const int     CV_VELOCITY = 4096/128;
 
/*learning comes later*/
const int MIDI_CHANNEL      = 1;
const int MIDI_BASENOTE = 60; //middle C 

/*global variables*/
int NOTE_LAST = 0;


void setOutput(byte channel, byte gain, byte shutdown, unsigned int val)
{
  byte lowByte = val & 0xff;
  byte highByte = ((val >> 8) & 0xff) | channel << 7 | gain << 5 | shutdown << 4;
 
  PORTB &= 0xfb;
  SPI.transfer(highByte);
  SPI.transfer(lowByte);
  PORTB |= 0x04;
}
 
int note2Cv(byte note, byte offset){
  return note*CV_SEMINOTE+CV_OFFSET ;   
}

int velo2Cv(byte velocity){
  return velocity*CV_VELOCITY ;
}

void cvNoteOn(byte channel, byte pitch, byte velocity){
  if(channel == MIDI_CHANNEL){
    if (pitch >= MIDI_BASENOTE){
      int NOTE_RELATIVE  =  pitch - MIDI_BASENOTE ;
      setOutput(0,GAIN_2,1,note2Cv(NOTE_RELATIVE,CV_OFFSET));
      setOutput(1,GAIN_2,1,velo2Cv(velocity));
      digitalWrite(PIN_GATE1,HIGH);
      digitalWrite(PIN_LED,HIGH);
      NOTE_LAST = pitch ;
    }
  }
  else{
  ;;
  }
}

void cvNoteOff(byte channel, byte pitch, byte velocity){
 if(channel == MIDI_CHANNEL && pitch == NOTE_LAST){
  digitalWrite(PIN_GATE1,LOW);
  digitalWrite(PIN_LED,LOW);
 }
}

void setup() {
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_LDAC,OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_GATE1, OUTPUT);
  pinMode(PIN_GATE2, OUTPUT);
  /*Enabling Switch with pullup*/
  pinMode(PIN_MODESWITCH,INPUT);  
  digitalWrite(PIN_MODESWITCH,HIGH);
  
  SPI.begin();  
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  MIDI.begin(MIDI_CHANNEL);
  MIDI.setHandleNoteOn(cvNoteOn);
  MIDI.setHandleNoteOff(cvNoteOff);
}

void loop() {
  
  MIDI.read();
  
}
