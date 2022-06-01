#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <ctime>

class TIMEUSE
{
public:
  TIMEUSE() : t_start(std::clock()) {}

  void st()
  {
    t_start = std::clock();
  }

  void fi()
  {
    t_finish = std::clock();
  }

  double time_use() const
  {
    return 1000. * (t_finish - t_start) / CLOCKS_PER_SEC;
  }

private:
  std::clock_t t_start, t_finish;
};

#endif