#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "defines.h"
int main() {
	TEAM *team;
	TEAM userteam;
	int id = 0;
	team = (TEAM *)malloc(16 * sizeof(TEAM));
	int i = 0;
	int j = 0;
	int choice = 0;
	FILE *fp = NULL;
	puts("Enter 1 for New league Or 2 for Load existing league:");
	scanf("%d", &choice);
	if (choice == 1) {
		team = newleague(team);
		print_teams(team);
		printf("%s", "Please choose a team number : ");
		scanf("%d", &id);
		userteam = team[id - 1];
	}
	//else if (choice == 2) loadleague();
	//nextgames();
	scoreboard(team, &userteam);
	printf("your place in Table: %d", userteam.place);
}
