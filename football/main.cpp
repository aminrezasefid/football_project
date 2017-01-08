#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Header.h"
#include "defines.h"
int main(){
	TEAM *team;
	TEAM userteam;
	WEEK games_week;
	int id = 0;
	char input[50];
	team = (TEAM *)malloc(16 * sizeof(TEAM));
	int i = 0;
	int j = 0;
	int n = 0; //tedad hafte
	int n2 = 0; // tedad bazi haye hafte
	int choice = 0;
	puts("Enter 1 for New league Or 2 for Load existing league:");
	scanf("%d", &choice);
	if (choice == 1) {
		team = newleague(team);
		print_teams(team);
		teams_formation(team);
		printf("%s", "Enter the games in a week : ");
		scanf("%d", &n2);
		games_week.games_in_week = n2;
		games_week.current_game = 0;
		printf("%s", "Please choose a team number : ");
		scanf("%d", &id);
		fgets(input, 50, stdin); //khali kardane buffer
		userteam = team[id - 1];
	}
	//else if (choice == 2) loadleague();
	nextgames(team,&games_week);
	scoreboard(team, &userteam);
	printf("\n\n\n|your place in Table: %-2d|\n", userteam.place);
	printf("You are entering managing mode");
	delay(1);
	while (1) {
		printf("\n\nEnter your command : ");
		fgets(input,50,stdin);
		if (strcmp(input, "exit\n")==0) break;
		else if (strcmp(input, "lineup\n")==0) lineup(&userteam);
		else if (strcmp(input, "table\n")==0) scoreboard(team,&userteam);
		else if (strcmp(input, "save\n") == 0);//save();
		else if (strstr(input, "proceed")!=NULL) {
			//strtok(input, " ");
			//strtok(NULL," ");
			//printf("%s", input);
			simulation(&games_week,team,&userteam,n);
		}
		else continue;
	}
}
