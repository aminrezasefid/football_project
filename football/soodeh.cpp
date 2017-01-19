#include "Header.h"
#include "header.h"
#include "defines.h"
#include <Windows.h>
#include <stdio.h>
void graph_loading(void) {
	int i = 0;
	int nspace = 0;
	int cnst = 0;
	int rnd = 0;
	rnd = rand() % 2 + 1;
	while (rnd) {
		system("cls");
		nspace = cnst;
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
		printf("%c", 186);
		while (nspace) {
			printf("  ");
			nspace--;
		}
		nspace = cnst;
		SetColor(14);
		printf("%c %c", 254, 254);
		SetColor(15);
		while (8 - nspace) {
			printf("  ");
			nspace++;
		}
		printf(" ");
		printf("%c\n", 186);
		cnst++;
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
		delay(0.1);
		if (cnst == 9) {
			cnst = 0;
			rnd--;
		}
	}
	system("cls");
}