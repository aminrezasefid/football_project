#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "defines.h"
TEAM *newleague(TEAM *team) { //tabe baraye khandane etela'at e team ha va bazi konan
	FILE *fptr = fopen("input.txt", "r");
	int j = 0, i = 0;
	for (i = 0; i < 16; i++) {
		fscanf(fptr, "%s", team[i].teamname);
		for (j = 0; j < 11; j++) {
			fscanf(fptr,"%s%s%d%d%d%d", team[i].player[j].name, team[i].player[j].lastname, &team[i].player[j].fitness, &team[i].player[j].form, &team[i].player[j].skill , &team[i].player[j].best_position);
		}
	}
	return team;
}

void delay(float secs) {  //delay function
	clock_t start;
	clock_t stop;

	start = clock();
	stop = clock();
	while (((float)(stop - start) / CLOCKS_PER_SEC) < secs) {
		stop = clock();
	}
}

void print(char str[50]) { //print function
	int i = 0;
	while (str[i] != '\0') {
		printf("%c", str[i]);
		fflush(stdout);
		delay(0.045);
		i++;
	}
}
