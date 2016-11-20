#include <iostream>
#include "Chord.h"
#include "Measure.h"
#include "Note.h"

class Phrase {
public:
    Phrase(Chord *key, string finStr) {

        measureCount = 0;
        
        this->key = key;

        Measure *m;

        ifstream fin;
        fin.open(finStr);

        for (int i = 0; i < 4; i++) {
            m = new Measure(3, *key);

            while(m->getMelodyLength() < 12) {

                int pitch;
                int length;

                char pitchChar;
                char trash;
                string all;

                getline(fin, all);

                //Equivalent to Java's String charAt method
                pitchChar = all.at(0);
                length = all.at(2);

                Note newNote(-1,0);

                if (pitchChar == 'R') {
                    newNote = Note(0, length);
                } else {
                    pitch = (pitchChar - 'C' + 7) % 7;
                    newNote = Note(pitch, length);
                }

                newNote.print();
                m->addMelodyNote(newNote);

            }

            measures[i] = m;
        }
    }

    Melody *getNextMeasure()
    {
      Melody *next = measures[measureCount];
      measureCount++;
      return next;
    }

    void resetCount()
    {
      measureCount = 0;
    }

    void setCount(int i)
    {
      measureCount = i;
    }

    void print() {
        for (int i = 0; i < 4; i++) {
            measures[i]->printMelody();
            cout << " | ";
        }
    }

private:
    Measure *measures[4];
    Chord *key;
    int measureCount;
};
