#include <stdio.h>
#include "header.h"
#include "defines.h"
void print_sched(TEAM *team, WEEK *gamesweek) {
	int i = 0;
	printf("%-25s%-2s%25s\n\n\n", "|HOST TEAM|","  ", "|GUEST TEAM|");
	for (i = 0; i < 240; i++) {
		TEAM *host=search_team_by_id(team, (gamesweek->gid[i].host_id));
		TEAM *guest = search_team_by_id(team, (gamesweek->gid[i].guest_id));
		printf("%-25s%-2s%25s\n", host->teamname, "vs", guest->teamname);
	}
}
void nextgames(TEAM *team,WEEK *gamesweek) {
	int j = 0;
	int i = gamesweek->current_game;
	FILE *fp = fopen("schedule.txt", "r");
	for (i = 0; i < 120; i++) {
		fscanf(fp, "%d%d", &(gamesweek->gid[i].host_id), &(gamesweek->gid[i].guest_id));
	}
	for (j = 0; j < 120; j++,i++) {
		gamesweek->gid[i].host_id = gamesweek->gid[j].guest_id;
		gamesweek->gid[i].guest_id = gamesweek->gid[j].host_id;
	}
	print_sched(team,gamesweek);
}