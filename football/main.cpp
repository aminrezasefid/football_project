#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Header.h"
#include "defines.h"
#pragma comment(lib, "winmm.lib")
#include <conio.h>
int main() {
	SetColor(15);
	TEAM *team;
	TEAM userteam;
	WEEK games_week;
	int id = 0;
	char input[50];
	team = (TEAM *)malloc(16 * sizeof(TEAM));
	int i = 0;
	int j = 0;
	int n = 1; //tedad hafte
	int n2 = 0; // tedad bazi haye hafte
	int choice = 0;
	printf("Enter 1 for New league Or 2 for Load existing league: ");
	PlaySound(TEXT("sounds/begin.wav"), NULL, SND_FILENAME);
	scanf("%d", &choice);
	if (choice == 1) {
		team = newleague(team);
		print_teams(team);
		teams_formation(team);
		games_week.current_game = 0;
		printf("%s", "Please choose a team number : ");
		PlaySound(TEXT("sounds/choose_team.wav"), NULL, SND_FILENAME);
		scanf("%d", &id);
		games_week.games_in_week = 8;
		fgets(input, 50, stdin); //khali kardane buffer
		TEAM *tmp = search_team_by_id(team, id);
		userteam = *tmp;
	}
	/*else if (choice == 2) {
	loading('l');
	loadleague();
	PlaySound(TEXT("sounds/load.wav"), NULL, SND_FILENAME);
	}*/
	nextgames(team, &games_week);
	scoreboard(team, &userteam);
	ranking_player(&userteam);
	printf("\n\n\n|your place in Table: %-2d|\n", userteam.place);
	SetColor(1);
	printf("You are entering managing mode");
	SetColor(15);
	delay(1);
	PlaySound(TEXT("sounds/manage.wav"), NULL, SND_FILENAME);
	while (1) {
		SetColor(10);
		printf("\n\nEnter your command : ");
		SetColor(15);
		fgets(input, 50, stdin);
		if (strcmp(input, "exit\n") == 0) break;
		else if (strcmp(input, "lineup\n") == 0) {
			lineup(&userteam);
			fgets(input, 50, stdin);
		}
		else if (strcmp(input, "table\n") == 0) scoreboard(team, &userteam);
		else if (strcmp(input, "save\n") == 0);/* {
											   PlaySound(TEXT("sounds/save.wav"), NULL, SND_FILENAME);
											   loading('S');
											   save();
											   }*/
		else if (strstr(input, "proceed") != NULL) {
			strtok(input, " ");
			char *tmp = strtok(NULL, " ");
			if (tmp != NULL) {
				n = atoi(tmp);
			}
			PlaySound(TEXT("sounds/simulation.wav"), NULL, SND_FILENAME);
			simulation(&games_week, team, &userteam, n);
		}
		else if (strcmp(input, "lineup all")) {
			int tmp = 0;
			for (tmp = 0; tmp < 5; tmp++) {
				lineup(team + tmp);
			}
		}
		else continue;
	}
}