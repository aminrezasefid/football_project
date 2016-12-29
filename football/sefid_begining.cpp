#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "defines.h"
TEAM *newleague(TEAM *team) { //tabe baraye khandane etela'at e team ha va bazi konan
	FILE *fptr = fopen("teams.csv", "r");
	if (fptr == NULL) puts("asd");
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
		team[i].formation = 1;
		/*for (j = 0; j < 11; j++) {
			fscanf(fptr, "%s%s%d%d%d%d", team[i].player[j].name, team[i].player[j].lastname, &team[i].player[j].fitness, &team[i].player[j].form, &team[i].player[j].skill, &team[i].player[j].best_position);
			team[i].player[j].position = team[i].player[j].best_position;
		}*/
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
	print("TEAM                     SCORE    WON    DRAWN     LOST    GF    GA    GD\n"); //print teams
	for (i = 0; i < 16; i++) {
		team[i].place = i + 1;
		if (team[i].id == userteam->id) {
			printf("my team : %-15s%-9d%-7d%-10d%-8d%-6d%-6d%-5d\n", team[i].teamname, team[i].score, team[i].score, team[i].won, team[i].drawn, team[i].lost, team[i].gf, team[i].ga, team[i].gd);
			userteam->place = i + 1;
			continue;
		}
		printf("%-25s%-9d%-7d%-10d%-8d%-6d%-6d%-5d\n", team[i].teamname, team[i].score, team[i].score, team[i].won, team[i].drawn, team[i].lost, team[i].gf, team[i].ga, team[i].gd);
	}
}
PLAYER *find_bestplayer(TEAM *team, int pos, int zakhire) {
	int i;
	if (pos == 5) pos = 2;
	else if (pos == 1) pos = 4;
	PLAYER *bestplayer;
	if (zakhire == 1)
		for (i = 0; i < 10; i++) {
			if (team->reserved_player[i + 1].id == -1) break;
			if (team->reserved_player[i].best_position == pos) {
				if (team->reserved_player[i].fitness + team->reserved_player[i].skill > team->reserved_player[i + 1].fitness + team->reserved_player[i + 1].skill)	bestplayer = &(team->reserved_player[i + 1]);
				else bestplayer = &(team->reserved_player[i]);
			}
		}
	else
		for (i = 0; i < 10; i++) {
			if (team->player[i].best_position == pos) {
				if (team->player[i].fitness + team->player[i].skill > team->player[i + 1].fitness + team->player[i + 1].skill)	bestplayer = &(team->player[i + 1]);
				else bestplayer = &(team->player[i]);
			}
		}
	return bestplayer;
}
PLAYER *find_wrostplayer(TEAM *team, int pos, int zakhire) {
	int i;
	if (pos == 5) pos = 2;
	else if (pos == 1) pos = 4;
	PLAYER *wrostplayer;
	if (zakhire == 1)
		for (i = 0; i < 10; i++) {
			if (team->reserved_player[i].best_position == pos) {
				if (team->reserved_player[i].fitness + team->reserved_player[i].skill < team->reserved_player[i + 1].fitness + team->reserved_player[i + 1].skill)	wrostplayer = &(team->reserved_player[i + 1]);
				else wrostplayer = &(team->reserved_player[i]);
			}
		}
	else
		for (i = 0; i < 10; i++) {
			if (team->player[i].best_position == pos) {
				if (team->player[i].fitness + team->player[i].skill < team->player[i + 1].fitness + team->player[i + 1].skill)	wrostplayer = &(team->player[i + 1]);
				else wrostplayer = &(team->player[i]);
			}
		}
	return wrostplayer;

}
void change(PLAYER *player1, PLAYER *player2) {
	PLAYER *tmp;
	tmp = player1;
	player1 = player2;
	player2 = tmp;

}
void position(int n, TEAM *team, int pos) {
	int i = 0;
	int j = 0;
	for (j = 0; j < 11; j++)
		if (team->player[j].position == pos) i++;
	j = 0;
	PLAYER *wplayer;
	PLAYER *w2player;
	PLAYER *b1player;
	PLAYER *b2player;
	if (i == n) return;
	while (i != n) {
		if (i > n) {
			wplayer = find_wrostplayer(team, pos, 0);
			b1player = find_bestplayer(team, pos + 1, 1);
			b2player = find_bestplayer(team, pos - 1, 1);
			if (b1player->fitness + b1player->skill < b2player->fitness + b2player->skill) b1player = b2player;
			change(b1player, wplayer);
			i--;
		}
		else {
			wplayer = find_wrostplayer(team, pos+1,0);
			b2player = find_bestplayer(team, pos-1,0);
			b1player = find_bestplayer(team, pos,1);
			if (b1player->fitness + b1player->skill < b2player->fitness + b2player->skill) b1player = b2player;
			change(b1player, wplayer);
			i++;
		}
	}
}


void default_formation(TEAM *team) {
	int i;
	for (i = 0; i < 16; i++) {
		position(4, &team[i], 2);
		position(3, &team[i], 3);
		position(3, &team[i], 4);
	}
}

