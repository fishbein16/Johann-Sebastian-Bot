#include <pitches.h>
#include "Phrase.h"
#include "Measure.h"
#include "Note.h"

//Set up pins
#define melody1 = 8;
#define melody2 = 6;
#define bass1 = 9;
#define bass2 = 7;

//Set up timing variables
unsigned long melodyTime;
unsigned long bassTime;

//Set up period variables;
unsigned long melodyPeriod;
unsigned long bassPeriod;

//Set up duration variables
unsigned long melodyDuration;
unsigned long bassDuration;

//Value of pins
int melody = 0;
int bass = 0;

//array which each element corresponding to tones in scales
  int scale[8] = {NOTE_C6,NOTE_D6,NOTE_E6,NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6,NOTE_C7};

Phrase *currentPhrase;

void setup() {
  // put your setup code here, to run once:
  //Get first phrase
  //currentPhrase = new Phrase();
}

void loop() {
  // put your main code here, to run repeatedly: 
  for(int i = 0; i < 4; i++)
  {
    Melody *measure = currentPhrase->getNextMeasure(i);
    Note mel = measure->getNextMelodyNote();
    Note bas = measure->getNextBassNote();

    melodyDuration = mel.getDuration();
    bassDuration = bas.getDuration();

    while(mel.getPitch() != -1 && bas.getPitch() != -1) //check for end of measure
    {
      //compare durations
      if(melodyDuration > bassDuration)
      {
        //play pitches
        play(mel.getPitch(), bas.getPitch(), bassDuration);
        //update melodyDuration
        melodyDuration = melodyDuration - bassDuration;
        bas = measure->getNextBassNote();
        bassDuration = bas.getDuration();
      } 
      else if(melodyDuration < bassDuration)
      {
        //play pitches
        play(mel.getPitch(), bas.getPitch(), melodyDuration);
        //update bassDuration
        bassDuration = bassDuration - melodyDuration;
        mel = measure->getNextMelodyNote();
        melodyDuration = mel.getDuration();        
      }
      else
      {
        //play pitches
        play(mel.getPitch(), bas.getPitch(), melodyDuration);
        bas = measure->getNextBassNote();
        mel = measure->getNextMelodyNote();
        bassDuration = bas.getDuration();
        melodyDuration = mel.getDuration();
      }
    }
  }

  //Get next phrase
  //currentPhrase = new Phrase();
}

//function for playing pitch for specific duration
void play(int melodyTone, int bassTone, unsigned long duration)
{
  unsigned long timeNote = millis();
  setPitches(melodyTone,bassTone);
  while(millis()-timeNote < duration)
  {
     if (micros()-melodyTime >= melodyPeriod/2)
      {
         time1 = micros();
         if (melody == 0) 
         {
          melody = 1;
         }
         else 
         {
          melody = 0;
         }
         digitalWrite(melody1, melody); 
         digitalWrite(melody2, melody);
      }

     if (micros()-time2 >= bassPeriod/2)
      {
        bassTime = micros();
        if (bass == 0)
        {
          bass = 1;
        }
        else
        {
          bass = 0;
        }
        digitalWrite(bass1, bass); 
        digitalWrite(bass2, bass);
      }
  }
}

//function for setting pitch parameters
void setPitches(int tone1, int tone2)
{
  //delay(20);
  melodyPeriod = 1000000/scale[tone1-1];
  bassPeriod = 1000000/scale[tone2-1];
}
