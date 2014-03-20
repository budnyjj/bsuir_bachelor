/* 	
	authors: 			Anashkevich P.S., Budny R.I.
	group number: 120602
	date: 				12.02.2014 - dd.03.2014 
*/

#include <stdio.h>

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
			calcDayProcess();
			break;
		case 27: // Esc
		case 'q':
		case 'Q':
			return 0;
		default:
			printf("Incorrect input, please choose an exists element\n");
		}
	}
	return 0;
}

void calcDayProcess() {
	days[1] = 29;
	
	// day input
	printf("Enter day: ");
	clear();
	while (!scanf("%d", &d) || (d < 1) || (d > 31)) {
		printf("Day input incorrect! Enter Day: ");
		clear();
	}

	// month input
	printf("Enter month: ");
	clear();
	while (!scanf("%d", &m) || (m < 1) || (m > 12)) {
		printf("Month input incorrect! Enter month: ");
		clear();
	}
	if (d > days[m-1]) {
		if (m == 2) {
			printf("Input error! This month contains only 28/29 days \n");
		} else printf("Input error! This month contains only %d days \n", days[m-1]);
		while (1) {
			printChangeDateMenu();
			switch (getchar()) {
			case 'c':
			case 'C': 	
				printf("Enter day: ");
				clear();
				while (!scanf("%d", &d) || (d < 1) || (d > days[m-1])) {
					printf("Day input incorrect! Enter Day: ");
					clear();
				}
				goto overFor;
			case 'm':
			case 'M':
				return;
			default:
				printf("Incorrect input, please choose an exists element\n");
			}
		}
	}
	overFor:

	// year input
	printf("Enter year: ");
	clear();
	while (!scanf("%d", &y) || (y < 0)) {
		printf("Year input incorrect! Enter year: ");
		clear();
	}
	if (!((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)))) {
		days[1] = 28;
		if (d == 29) {
			printf("Input error! Only %d days in February in %d\n year\n", days[1], y);
			while (1) {
				printChangeDateMenu();
				switch (getchar()) {
				case 'c':
				case 'C': 	
					printf("Enter day: ");
					clear();
					while (!scanf("%d", &d) || (d < 1) || (d > days[m-1])) {
						printf("Day input incorrect! Enter Day: ");
						clear();
					}
					goto myOverFor;
				case 'm':
				case 'M':
					return;
				default:
					printf("Incorrect input, please choose an exists element\n");
				}
			}
		}
	} else days[1] = 29;

	myOverFor:
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
	printf("| c --- Change date         |\n");
	printf("| m --- Main menu           |\n");
	printf("+---------------------------+\n");	
}