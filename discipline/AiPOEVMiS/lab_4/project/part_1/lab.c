#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CALC_PRECISION  3
#define PRINT_PRECISION 1

extern "C" void CF(char *buff, int *val_len, int *dot_pos, int *sign_val);

static void double_to_buff(double value, char *buff, int *val_len, int *dot_pos, int *sign);
static double buff_to_double(char *buff, int dot_pos, int sign);

static void convert_chars_to_digits(char *buff, int buff_len);
static void convert_digits_to_chars(char *buff, int buff_len);

static void c_f_conversion(double *cels_arr, double *far_arr, int arr_len);

static void print_diagram(double *cels_arr, double *far_arr, int arr_len);
static void print_diagram_line(double cur_faren, double max_faren, double cels);

static double get_max_in_arr(double *arr, int arr_len);
static void set_formatter_str(char *formatter, int precision);

const int BUFF_SIZE = 20;
const int DIAGRAM_LEN = 20;

int
main(void)
{
    const int ARR_LEN = 10;
    double cels_arr[ARR_LEN] = {-400.45, -300.24, -200.68, -100.45, -50.23, -10.98, 50.76, 100.45, 150.34, 250.93};
    double far_arr[ARR_LEN];

    c_f_conversion(cels_arr, far_arr, ARR_LEN);

    print_diagram(cels_arr, far_arr, ARR_LEN);

    return 0;
}


static void
c_f_conversion(double *cels_arr, double *far_arr, int arr_len)
{
    int val_len;
    int sign;
    int dot_pos;
    char buff[BUFF_SIZE+1];

    for (int i = 0; i < arr_len; i++) {
        val_len = 0;
        sign = 0;
        dot_pos = 0;
        for (int j = 0; j < BUFF_SIZE; j++) { buff[j] = '0'; }

        double_to_buff(cels_arr[i], buff, &val_len, &dot_pos, &sign);
        CF(buff, &val_len, &dot_pos, &sign);
        far_arr[i] = buff_to_double(buff, dot_pos, sign);
    }
}

static void
double_to_buff(double value, char *buff, int *val_len, int *dot_pos, int *sign)
{
    if (value >= 0) {
        (*sign) = 0;
        (*dot_pos) = CALC_PRECISION;
    } else if (value < 0) {
        value = fabs(value);
        (*dot_pos) = CALC_PRECISION;
        (*sign) = 1;
    } else {
        (*dot_pos) = 0;
    }

    char temp_buff[BUFF_SIZE+1] = "";

    char formatter[10] = "";
    set_formatter_str(formatter, CALC_PRECISION);
    sprintf(temp_buff, formatter, value);

    sscanf(temp_buff, "%lf", &value);
    value *= pow(10, CALC_PRECISION);
    sprintf(temp_buff, "%.lf", value);

    *val_len = strlen(temp_buff);

    int counter = 0;
    for (int i = BUFF_SIZE - (*val_len); i <= BUFF_SIZE; i++) {
        buff[i] = temp_buff[counter++];
    }

    convert_chars_to_digits(buff, BUFF_SIZE);
}

static double
buff_to_double(char *buff, int dot_pos, int sign)
{
    convert_digits_to_chars(buff, BUFF_SIZE);
    double value = atof(buff);

    if (sign)    { value = -value; }

    if (dot_pos) { value /= pow(10, dot_pos); }

    return value;
}

static void
print_diagram(double *cels_arr, double *far_arr, int arr_len)
{
    printf(
        "-------------- This program convert Celsius to Farengheit ----------------\n"
        "--------------- and draws diagram using Farengheit values ----------------\n"
        "----------------------- by the following template: -----------------------\n"
        "[#########  Farengheit diagram  #########] [Faren: value]  [Cels: value]\n"
        "--------------------------------------------------------------------------\n"
        );

    double max_faren = get_max_in_arr(far_arr, arr_len);

    for (int i = 0; i < arr_len; i++) {
        print_diagram_line(far_arr[i], max_faren, cels_arr[i]);
    }

    printf("--------------------------------------------------------------------------\n");

}

static void
print_diagram_line(double cur_faren, double max_faren, double cels)
{
    int cur_len = abs((cur_faren / max_faren) * DIAGRAM_LEN);

    char diagram_str[(DIAGRAM_LEN * 2) + 2] = "[";

    if (cur_faren >= 0) {
        strcat(diagram_str, "....................");

        for (int i = 0; i < cur_len; i++) {
            strcat(diagram_str, "#");
        }

        for (int j = cur_len; j < DIAGRAM_LEN; j++) {
            strcat(diagram_str, ".");
        }

        strcat(diagram_str, "]");
    } else {

        for (int i = 0; i < DIAGRAM_LEN - cur_len; i++) {
            strcat(diagram_str, ".");
        }

        for (int j = DIAGRAM_LEN - cur_len; j < DIAGRAM_LEN; j++) {
            strcat(diagram_str, "#");
        }

        strcat(diagram_str, "....................]");
    }

    char print_str[100] = "";
    strcat(print_str, diagram_str);

    char formatter[10] = "";
    set_formatter_str(formatter, PRINT_PRECISION);

    strcat(print_str, " [Faren: ");
    strcat(print_str, formatter);
    strcat(print_str, "] [Cels: ");
    strcat(print_str, formatter);
    strcat(print_str, "]\n");

    printf(print_str, cur_faren, cels);
}

static double
get_max_in_arr(double *arr, int arr_len)
{
    double max_value = 0;

    for (int i = 0; i < arr_len; i++) {
        if (fabs(arr[i]) > max_value) {
            max_value = fabs(arr[i]);
        }
    }
    return max_value;
}

static void
set_formatter_str(char *formatter, int precision)
{
    strcat(formatter, "%.");
    char precision_str[5];
    itoa(precision, precision_str, 10);
    strcat(formatter, precision_str);
    strcat(formatter, "lf");
}

static void
convert_chars_to_digits(char *buff, int buff_len)
{
    for (int i = 0; i < buff_len; i++) { buff[i] -= '0'; }
}

static void
convert_digits_to_chars(char *buff, int buff_len)
{
    for (int i = 0; i < buff_len; i++) { buff[i] += '0'; }
}
