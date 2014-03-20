#include "date.h"

int is_leap_year(int y) {
  if (!(y % 4) ||  !(y % 100))
    return 1;
  else
    return 0;
}

int get_day_number(struct Date * date) {
  int months[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /* months[0] is bogus */
  int num_days = 0;
  int i;

  for (i = 1; i < date->m; i++)
    num_days += months[i];

  if (is_leap_year(date->y) && (date->m > 2))
    num_days++;

  num_days += date->d;

  return num_days;
}
