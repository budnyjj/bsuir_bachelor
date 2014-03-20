#ifndef __MY_DATE_IO__
#define __MY_DATE_IO__

#include <stdio.h>
#include "date.h"
#include "io.h"

int input_date_prompt();

int input_date(struct Date * date);

void output_day();

#endif
