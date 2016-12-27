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
		team[i].id = i + 1;
		team[i].score = 0;
		team[i].gameplayed = 0;
		team[i].won = 0;
		team[i].lost = 0;
		team[i].drawn = 0;
		team[i].gf = 0;
		team[i].gd = 0;
		team[i].ga = 0;
		for (j = 0; j < 11; j++) {
			fscanf(fptr, "%s%s%d%d%d%d", team[i].player[j].name, team[i].player[j].lastname, &team[i].player[j].fitness, &team[i].player[j].form, &team[i].player[j].skill, &team[i].player[j].best_position);
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
		delay(0.025);
		i++;
	}
}

void print_teams(TEAM *team) {
	int i;
	for (i = 0; i < 16; i++) {
		printf("%d.", team[i].id);
		print(team[i].teamname);
		print("\n");
	}
}
void sort_team(TEAM *team) {
	int i = 0, j = 0;
	for (i = 0; i < 16; i++) { //sort teams
		for (j = i; j < 16; j++) {
			if (team[i].score < team[j].score) {
				swap(&team[i], &team[j]);
			}
			else if (team[i].score == team[j].score) {
				if (team[i].gd < team[j].gd) {
					swap(&team[i], &team[j]);
				}
				else if (team[i].gf == team[j].gf) {
					if (team[i].ga > team[j].ga) {
						swap(&team[i], &team[j]);
					}
				}
			}
		}
	}
}
void swap(TEAM *a, TEAM *b) {
	TEAM tmp = *a;
	*a = *b;
	*b = tmp;

}
void scoreboard(TEAM *team, TEAM *userteam) {
	int i = 0, j = 0;
	sort_team(team);
	print("TEAM                     SCORE\n"); //print teams
	for (i = 0; i < 16; i++) {
		team[i].place = i + 1;
		if (team[i].id == userteam->id) {
			printf("your team :%-14s%-5d\n", team[i].teamname, team[i].score);
			userteam->place = i + 1;
			continue;
		}
		printf("%-25s%-5d\n", team[i].teamname, team[i].score);
	}
}
