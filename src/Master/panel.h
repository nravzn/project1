#ifndef Panel
#define Panel

class Panel {
  public:
    Panel(byte bD, byte bU, byte bS, byte bDL, byte bUL, byte bSL);
    void readButtons();
    void setLeds();
};


