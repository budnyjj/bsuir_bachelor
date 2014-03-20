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

int input_date_prompt() {
  char c;

  printf("Press \'c\' to calculate day number, \'q\' to exit\n");
  
  while (c=getchar(), 
	 (c != 'c' && c != 'C' && c != 'q' && c != 'Q'))
    {
      printf("Press \'c\' to calculate day number, \'q\' to exit\n");
      clear_input();
    }
   	  
  clear_input();

  if ((c == 'c') || (c == 'C'))
    return 1;  
  else 
    return 0; /* quit */  
}

int input_day() {
  int d;

  printf("Input day number: ");
  while (!scanf("%i", &d))
    {
      printf("Input numeric value!\n");
      clear_input();
    }
  clear_input();
  return d;
}

int input_month() {
  int m;

  printf("Input month number: ");
  while (!scanf("%i", &m))
    {
      printf("Input numeric value!\n");
      clear_input();
    }
  clear_input();
  return m;
}

int input_year() {
  int y;
  
  printf("Input year number: ");
  
  
  while (!scanf("%i", &y))
    {
      printf("Input numeric value!\n");
      clear_input();
    }

  clear_input();
  return y;
}

int is_correct_year(struct Date * date) {
  if (date->y > 0) 
    return 1;
  else
    {
      error("Incorrect input! Number of year must be non-negative");
      return 0;
    } 
}

int is_correct_month(struct Date * date) {
  if ((date->m > 0) && (date->m <= 12))
    return 1;
  else
    {
      error("Incorrect input! Number of month must be in range [1; 12]");
      return 0;
    }
}

int is_correct_day(struct Date * date) {
  /* months[0] is bogus */
  int months[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
  if ((is_leap_year(date->y)) &&
      (date->m == 2) &&
      (date->d == 29))
    return 1;

  if ((date->d > 0) && (date->d <= months[date->m]))
    return 1;
  else
    error("Incorrect input! There is no such day in calendar.");

  return 0;
}

int input_date(struct Date * date) {
  do
    {
      date->y = input_year();
    }
  while (!is_correct_year(date));

  do
    {
      date->m = input_month();
    }
  while (!is_correct_month(date));

  do
    {
      date->d = input_day();
    }
  while (!is_correct_day(date));

  return 1;
}

void output_day(int v) {
  printf("Result: %i\n", v);
}

void clear_input() {
  while (getchar() != '\n');
}

void error(char* msg) {
  printf("%s\n", msg);
}

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
