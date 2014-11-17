#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRECISION 5

static void normalize_buff(double value, int *val_len, char *buff, int *dot_pos, int *sign);
const int BUFF_SIZE = 20;

extern "C" void CF(char *buff, int val_len, int dot_pos, int sign_val);

int
main(void)
{
    // double val = 12.1234567890;
    double val = 10;

    char buff[BUFF_SIZE+1] = "00000000000000000000";
    int val_len;
    int sign;
    int dot_pos;
    normalize_buff(val, &val_len, buff, &dot_pos, &sign);

    puts(buff);

    printf("======= CF procedure =======\n");
    CF(buff, val_len, dot_pos, sign);
    printf("======= CF procedure =======\n");

    puts(buff);

    return 0;
}

static void
normalize_buff(double value, int *val_len, char *buff, int *dot_pos, int *sign)
{
    if (value >= 0) {
        (*sign) = 0;
        (*dot_pos) = PRECISION;
    } else if (value < 0) {
        value = fabs(value);
        (*dot_pos) = PRECISION;
        (*sign) = 1;
    } else {
        (*dot_pos) = 0;
    }

    //char formatter[10] = "%.";
    ///char precision[5];
    //int prec = PRECISION;
    //sscanf(precision, "%d", &prec);
    //strcat(formatter, precision);
    //strcat(formatter, "lf");
    char temp_buff[BUFF_SIZE+1];
    sprintf(temp_buff, "%.5lf", value);
    //sprintf(temp_buff, formatter, value);

    sscanf(temp_buff, "%lf", &value);
    value *= pow(10, PRECISION);
    sprintf(temp_buff, "%.lf", value);

    *val_len = strlen(temp_buff);

    int counter = 0;
    for (int i = BUFF_SIZE - (*val_len); i <= BUFF_SIZE; i++) {
        buff[i] = temp_buff[counter++];
    }
}
