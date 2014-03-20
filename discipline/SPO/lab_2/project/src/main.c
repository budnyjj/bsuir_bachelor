#include "date.h"
#include "io.h"
#include "date_io.h"


int main() {
  struct Date date;

  while (input_date_prompt()) {
    int day_number = 0;
    input_date(&date);
    day_number = get_day_number(&date);
    output_day(day_number);
  }

  return 0;
}
