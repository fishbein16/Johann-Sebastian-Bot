#include <iostream>

char notes[8] = {' ', 'c', 'd', 'e', 'f', 'g', 'a', 'b'};

class Note
{
  public:
    Note(int Pitch, int Length)
    {
      pitch = Pitch;
      length = Length;
    }

    int getPitch()
    {
      return pitch;
    }

    int getLength()
    {
      return length;
    }

    void print()
    {
      cout << notes[pitch];
      for(int i = 0; i < length; i++)
      {
        cout << "-";
      }
      cout << endl;
    }
  private:
    int pitch;
    int length;
}
