#include <stdio.h>
#include "header.h"
#include "defines.h"
void print_sched(TEAM *team, WEEK *gamesweek) {
	int i = 0;
	int j = 0;
	j = gamesweek->current_game;
	j = j / 8 + 1;
	for (i = 0; i < 240 - gamesweek->current_game; i++) {
		if (i % 8 == 0) {
			SetColor(1);
			printf("\n\nweek %d:\n", j);
			SetColor(4);
			printf("%-25s%-2s%25s\t%-25s%-2s%25s\n", "|HOST TEAM|", "  ", "|GUEST TEAM|", "|HOST TEAM|", "  ", "|GUEST TEAM|"); 
			j++;
		}
		if (i % 2 == 0) SetColor(8);
		else SetColor(15);
		TEAM *host = search_team_by_id(team, (gamesweek->gid[i].host_id));
		TEAM *guest = search_team_by_id(team, (gamesweek->gid[i].guest_id));
		printf("%-25s%-2s%25s\t%-25s%-2s%25s\n", host->teamname, "vs", guest->teamname, host->teamname, "vs", guest->teamname);
	}
}
void nextgames(TEAM *team, WEEK *gamesweek) {
	int j = 0;
	int i = gamesweek->current_game;
	FILE *fp = fopen("schedule.txt", "r");
	for (i = 0; i < 120; i++) {
		fscanf(fp, "%d%d", &(gamesweek->gid[i].host_id), &(gamesweek->gid[i].guest_id));
	}
	for (j = 0; j < 120; j++, i++) {
		gamesweek->gid[i].host_id = gamesweek->gid[j].guest_id;
		gamesweek->gid[i].guest_id = gamesweek->gid[j].host_id;
	}
	print_sched(team, gamesweek);
}