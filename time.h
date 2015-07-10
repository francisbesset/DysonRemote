#ifndef _TIME_H_
#define _TIME_H_

class Time
{
  public:
    Time (int hour, int minute);

    bool isTime (DateTime datetime);

  private:
    int hour, minute;
};

#endif // _TIME_H_
