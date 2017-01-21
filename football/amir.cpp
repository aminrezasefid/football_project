#include <stdio.h>
#include "header.h"
#include "defines.h"
#include "jalali.h"
#include <string.h>
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
	int i = 0;
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
void calendar(char x[], size_t size) {
	int y, m, d;
	static time_t current_time = time(NULL);
	struct tm *info;
	info = (struct tm *)malloc(20);
	char date[100];
	char date2[100];
	int i = rand() % 7;
	int j = 0;
	do {

		j = rand() % 7;

	} while (i == j);
	if (j<i) {

		int tmp = i;
		i = j;
		j = tmp;
	}
	time_t firstday = current_time + 3600 * 24 * i;
	info = localtime(&firstday);
	gregorian_to_jalali(&y, &m, &d, 1900 + info->tm_year, 1 + info->tm_mon, info->tm_mday);
	sprintf(date, "%d %s %d", d, j_month_name[m], y);
	time_t secondday = current_time + 3600 * 24 * j;
	info = localtime(&secondday);
	gregorian_to_jalali(&y, &m, &d, 1900 + info->tm_year, 1 + info->tm_mon, info->tm_mday);
	sprintf(date2, "%d %s %d", d, j_month_name[m], y);
	strcat(date, " , ");
	strcat(date, date2);
	strcat(x, date);
	current_time += 3600 * 24 * 7;
	info = localtime(&current_time);
}