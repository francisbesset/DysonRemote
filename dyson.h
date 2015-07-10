#ifndef _DYSON_REMOTE_H_
#define _DYSON_REMOTE_H_

class DysonRemote
{
  public:
    DysonRemote (int IRPin);

    void power ();

  private:
    int IR_pin, lastCodeUsed = 2;

    void header();
    void phase(int lowTime, int hightTime);
    void pause(int repeat);
    int getCode();
};

#endif // _DYSON_REMOTE_H_
