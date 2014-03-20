#ifndef __MY_DATE__
#define __MY_DATE__

struct Date {
  int d;
  int m;
  int y;
};

extern int is_leap_year(int);
extern int get_day_number(struct Date * date);

#endif
