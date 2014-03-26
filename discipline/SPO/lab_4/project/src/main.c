/*  
    authors:        Anashkevich P.S., Budny R.I.
    group number:   120602
    date:           12.03.2014 - dd.mm.2014

    Для всех вариантов необходимо выполнить следующее: 
    определить типы и функции в соответствии с вариантом задания; 
    в функции main() реализовать демонстрацию работы созданных функций;

    Определите структуру Complex для хранения комплексных чисел: 

    struct Complex

    {
        double re;  //вещественная часть
        double im;  //мнимая часть
    };

    Определите следующие функции: 


    Complex Add(Complex c1, Complex c2);
    Complex Sub(Complex c1, Complex c2);
    Complex Mul(Complex c1, Complex c2);
    Complex Div(Complex c1, Complex c2); // сложение, вычитание, 
    умножение и деление комплексных чисел. 
    Все функции должны возвращать новое комплексное число, 
    содержащее результат операции;
    void PrintComplex(Complex c); // вывод значения комплексного числа 
    на экран в алгебраической или показательной формах.

*/
#include "ui.h"

int main () {
    
    complex_process();
    
    return 0;
}