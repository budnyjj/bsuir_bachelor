/* 	
	authors: 		Anashkevich P.S., Budny R.I.
	group number: 	120602
	date: 			12.02.2014 - dd.03.2014 
*/

#include <stdio.h>

#define isLeapYear (!(y % 400) || (!(y % 4) && (y % 100)))

void clear() { while(getchar() != '\n'); }

int d, m, y;
int result;
int days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void calcDayProcess();
void calcDay();
void printMainUserMenu();
void printChangeDateMenu();


int main() {
	while (1) {
		printMainUserMenu();
		switch (getchar()) {
		case 'e':
		case 'E': 	
		case 13: // Enter
			calcDayProcess();
			break;
		case 'q':
		case 'Q':
		case 27: // Esc
			return 0;
		default:
			printf("Incorrect input, please choose an exists element\n");
		}
	}
	return 0;
}

void calcDayProcess() {
	
	// year input
	printf("Enter year: ");
	clear();
	while (!scanf("%d", &y) || (y < 0)) {
		printf("Year input incorrect! Enter year: ");
		clear();
	}

	if (isLeapYear) {
		days[1] = 29;
	} else {
		days[1] = 28;
	}

	// month input
	printf("Enter month: ");
	clear();
	while (!scanf("%d", &m) || (m < 1) || (m > 12)) {
		printf("Month input incorrect! Enter month: ");
		clear();
	}

	// day input
	printf("Enter day: ");
	clear();
	while (!scanf("%d", &d) || (d < 1) || (d > 31)) {
		printf("Day input incorrect! Enter Day: ");
		clear();
	}

	if (d > days[m-1]) {
		printf("Input error! Month number %d contains only %d days in %d year\n", m, days[m-1], y);
		clear();
		while (1) {
			printChangeDateMenu();
			switch (getchar()) {
			case 'd':
			case 'D':
				printf("Enter day: ");
				clear();
				while (!scanf("%d", &d) || (d < 1) || (d > days[m-1])) {
					printf("Day input incorrect! Enter Day: ");
					clear();
				}
				goto overWhile;
			case 'm':
			case 'M':
				printf("Enter month: ");
				clear();
				while (!scanf("%d", &m) || (m < 1) || (m > 12) || (d > days[m-1])) {
					printf("Month input incorrect! Enter month: ");
					clear();
				}
				goto overWhile;
			case 'y':
			case 'Y':
				if (isLeapYear || (m != 2) || (d != 29)) {
					printf("Incorrect input, please choose an exists element\n");
					break;
				}
				printf("Enter year: ");
				clear();
				while (!scanf("%d", &y) || (y < 0) || !isLeapYear) {
					printf("Year input incorrect! Enter only LEAP year: ");
					clear();
				}
				goto overWhile;
			case 'b':
			case 'B':
				return;
			default:
				printf("Incorrect input, please choose an exists element\n");		
			}
		}
	}

	overWhile:
	result = 0;
	calcDay();
	printf("-----------------------------\n");
	printf("Number of days: %d \n", result);
	printf("-----------------------------\n");
	clear();
}

	
void calcDay() {
	int i = 0;
	while (i < m-1) {
		result += days[i];
		i++;
	}
	result += d;
}

void printMainUserMenu() {
	printf("+----Choose item:-----------+\n");
	printf("| e --- Enter date          |\n");
	printf("| q --- Quit                |\n");
	printf("+---------------------------+\n");
}

void printChangeDateMenu() {
	printf("+----Choose item:-----------+\n");
	printf("| d --- change Day          |\n");
	printf("| m --- change Month        |\n");
	if ((!isLeapYear) && (m == 2) && (d == 29)) {
		printf("| y --- change Year         |\n");
	}
	printf("| b --- Back to main menu   |\n");
	printf("+---------------------------+\n");	
}