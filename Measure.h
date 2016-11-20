#include <iostream>
#include <vector>
#include "Chord.h"
#include "Note.h"

class Measure
{
  public:
    Measure(int timeSig, Chord c) {
        timeSignature = timeSig;
        chord = new Chord(c.getRoot(), c.isMajor());
        melodyNoteNum = 0;
        bassNoteNum = 0;
        melodyLength = 0;
        bassLength = 0;
    }

    void addMelodyNote(Note n) {
        melody.push_back(n);
        melodyLength += n.getLength();

        //cout << " P:" << n.getPitch();
        //cout << " L:" << n.getLength();
    }

    Note getNextMelodyNote() {
        if(++melodyNoteNum >= melody.size()) {
            return Note(-1, 0);
        } else {
            return melody[melodyNoteNum];
        }
    }

    Note getFirstMelodyNote() {
        melodyNoteNum = 0;
        return melody[melodyNoteNum];
    }

    Note getMelodyNoteNum(int n) {
        return melody[n];
    }

    void addBassNote(Note n) {
        bass.push_back(n);
        bassLength += n.getLength();
    }

    Note getNextBassNote() {
        if(++bassNoteNum >= bass.size()) {
            return Note(-1, 0);
        } else {
            return bass[bassNoteNum];
        }
    }

    Note getFirstBassNote() {
        bassNoteNum = 0;
        return bass[bassNoteNum];
    }

    Note getBassNoteNum(int n) {
        return bass[n];
    }

    Chord getChord() {
        return *chord;
    }

    int getMelodyLength() {
        return melodyLength;
    }

    int getBassLength() {
        return bassLength;
    }

    void printMelody() {
        int pitch;
        do {
            Note m = getNextMelodyNote();
            m.print();
            cout << m.getPitch() << " " << notes[m.getPitch()];
            pitch = m.getPitch();
        } while (pitch >= 0);
    }

    void printBass() {
        Note b(0,0);
        do {
            b = getNextBassNote();
            b.print();
        } while (&b != NULL);
    }

  private:
    vector<Note> melody;
    vector<Note> bass;
    int timeSignature;
    int melodyNoteNum;
    int bassNoteNum;
    Chord *chord;
    int bassLength;
    int melodyLength;

}
