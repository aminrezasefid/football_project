#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "defines.h"
int main() {
	TEAM *team;
	team = (TEAM *) malloc(16 * sizeof(TEAM));
	int i = 0;
	int j = 0;
	int choice = 0;
	FILE *fp=NULL;
	puts("Enter 1 for New league Or 2 for Load existing league:");
	scanf("%d", &choice);
	if (choice == 1) team = newleague(team);
	//else if (choice == 2) loadleague();
	for (j = 0; j < 16; j++) {
		printf("\n\n\nteam name is :%s\n", team[j].teamname);
		for (i = 0; i < 11; i++) {
			printf("%d.%s %s skill:%d form:%d fitness:%d bestplayingposition:%d\n", i + 1, team[j].player[i].name, team[j].player[i].lastname, team[j].player[i].skill, team[j].player[i].form, team[j].player[i].fitness, team[j].player[i].best_position);
		}
	}
}
