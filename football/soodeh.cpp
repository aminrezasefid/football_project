#include "Header.h"
#include "header.h"
#include "defines.h"
#include <Windows.h>
#include <stdio.h>
void graph_loading(void) {
	int i = 0;
	int nspace = 0;
	int cnst = 0;
	int rnd = 0;
	rnd = rand() % 2 + 1;
	while (rnd) {
		system("cls");
		nspace = cnst;
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
		printf("%c", 186);
		while (nspace) {
			printf("  ");
			nspace--;
		}
		nspace = cnst;
		SetColor(14);
		printf("%c %c", 254, 254);
		SetColor(15);
		while (8 - nspace) {
			printf("  ");
			nspace++;
		}
		printf(" ");
		printf("%c\n", 186);
		cnst++;
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
		delay(0.1);
		if (cnst == 9) {
			cnst = 0;
			rnd--;
		}
	}
	system("cls");
}
PLAYER  *search_player_by_id(TEAM *team, int j) {
	int i = 0;
	for (i = 0; i < 11; i++) {
		if (team->player[i].id == j) return &(team->player[i]);
	}
	for (i = 0; i < team->noplayers - 11; i++) {
		if (team->reserved_player[i].id == j) return &(team->reserved_player[i]);
	}
	return NULL;
}
void sort_player(PLAYER *plr, int n) {
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++) {
		for (j = i; j < n; j++) {
			if ((plr[i].skill*plr[i].fitness*plr[i].form) < (plr[j].skill*plr[j].fitness*plr[j].form)) {
				PLAYER tmp;
				tmp=plr[i];
				plr[i] = plr[j];
				plr[j] = tmp;
			}
		}
	}
}
void ranking(TEAM *team, char post) {
	int i = 0;
	int j = 0;
	PLAYER plr[30] = {};
	for (i = 0; i < 11; i++) {
		if (team->player[i].best_position == post) {
			plr[j] = team->player[i];
			j++;
		}
	}
	for (i = 0; i < team->noplayers - 11; i++) {
		if (team->reserved_player[i].best_position == post) {
			plr[j] = team->reserved_player[i];
			j++;
		}
	}
	sort_player(plr, j);
	for (i = 0; i < j; i++) {
		int sh=plr[i].id;
		PLAYER *srtdplr=search_player_by_id(team,sh);
		plr[i].rank = i + 1;
		srtdplr->rank = plr[i].rank;
	}
}
void ranking_player(TEAM *team) {
	ranking(team, 'G');
	ranking(team, 'D');
	ranking(team, 'M');
	ranking(team, 'A');
}