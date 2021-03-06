#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

char notes[8] = {' ', 'c', 'd', 'e', 'f', 'g', 'a', 'b'};

class Note {
public:
    Note(int pitch, int length) {
        this->pitch = pitch;
        this->length = length;
    }

    int getPitch() {
        return pitch;
    }

    int getLength() {
        return length;
    }

    void print() {
        cout << notes[pitch];
        for (int i = 1; i < length; i++) {
            cout << "-";
        }
    }

private:
    int pitch;
    int length;


};

class Chord {
public:
    Chord(int root, bool major) {
        this->root = root;
        this->major = major;
    }

    int getRoot() {
        return root;
    }

    bool isMajor() {
        return major;
    }

private:
    int root;
    bool major;
};

class Measure {
public:
    Measure(int timeSig, Chord c) {
        timeSig = timeSignature;
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
};

class Phrase {
public:
    Phrase(Chord *key, string finStr) {
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
//                char trash;
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

    void print() {
        for (int i = 0; i < 4; i++) {
            measures[i]->printMelody();
            cout << " | ";
        }
    }

private:
    Measure *measures[4];
    Chord *key;
};

int main() {
    Note a(6, 4);
    a.print();
    cout << endl;

    string finStr = "C:\\Users\\Kyle\\Downloads\\nice_converted.txt";


    Phrase *p1 = new Phrase(new Chord(1, 1), finStr);
    //p1->print();
}
