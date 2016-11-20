class Chord
{
  public:
    Chord(int Root, bool Major)
    {
      root = Root;
      major = Major;
    }

    int getRoot()
    {
      return root;
    }

    bool isMajor()
    {
      return major;
    }
  private:
    int root;
    bool major;
}
