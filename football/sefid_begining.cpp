#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"
#include "defines.h"
#include <time.h>

TEAM *newleague(TEAM *team) { //tabe baraye khandane etela'at e team ha va bazi konan
	srand(time(NULL));
	FILE *fptr = fopen("teams.csv", "r");
	int j = 0, i = 0;
	for (i = 0; i < 16; i++) {
		fgets(team[i].teamname, sizeof(team[i].teamname), fptr);
		strtok(team[i].teamname, "\n");
		team[i].id = i + 1;
		team[i].score = 0;
		team[i].gameplayed = 0;
		team[i].won = 0;
		team[i].lost = 0;
		team[i].drawn = 0;
		team[i].gf = 0;
		team[i].gd = 0;
		team[i].ga = 0;
		team[i].place = 1;
		team[i].formation = 1;
		char file[50];
		char file2[50] = "";
		strcpy(file, team[i].teamname);
		strtok(file, " ");
		strcat(file2, file);
		char *f = strtok(NULL, " ");
		if (f != NULL) strcat(file2, f);
		strcat(file2, ".csv");
		char tmp[100] = "teams/";
		strcat(tmp, file2);
		FILE *tpr = fopen(tmp, "r");
		char buffer[100];
		j = 0;
		while (fgets(buffer, 100, tpr) != NULL) {
			if (j < 11) {
				team[i].player[j].id = j + 1;
				char *ch = buffer;
				int ret = strtod(buffer, &ch);
				team[i].player[j].number = ret;
				ch = strtok(ch + 1, ",");
				strcpy(team[i].player[j].name, ch);
				ch = strtok(NULL, ",");
				ret = strtod(ch, &ch);
				team[i].player[j].age = ret;
				team[i].player[j].best_position = ch[1];
				team[i].player[j].position = ch[1];
				team[i].player[j].form = 100;
				team[i].player[j].goal = 0;
			}
			else {
				team[i].reserved_player[j - 11].id = j;
				char *ch = buffer;
				int ret = strtod(buffer, &ch);
				team[i].reserved_player[j - 11].number = ret;
				ch = strtok(ch + 1, ",");
				strcpy(team[i].reserved_player[j - 11].name, ch);
				ch = strtok(NULL, ",");
				ret = strtod(ch, &ch);
				team[i].reserved_player[j - 11].age = ret;
				team[i].reserved_player[j - 11].best_position = ch[1];
				team[i].reserved_player[j - 11].position = ch[1];
				team[i].reserved_player[j - 11].form = 100;
				team[i].reserved_player[j - 11].goal = 0;

			}
			j++;
		}
		team[i].noplayers = j;
		fclose(tpr);
		team[i].reserved_player[j - 10].id = -1;
		set_skill(&team[i]);
		set_fitness(&team[i]);
	}
	fclose(fptr);
	return team;
}
void set_fitness(TEAM *team) {
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < 11; i++) {
		int rnd = rand() % 40 + 60;
		if (rnd > 80 && rnd < 90 && j < 2) {
			team->player[i].fitness = rnd;
			j++;
		}
		else if (rnd > 80 && rnd < 90 && j == 2) {
			i--;
		}
		else if (rnd >= 90 && k == 0) {
			team->player[i].fitness = rnd;
			k++;
		}
		else if (rnd >= 90 && k == 1) {
			i--;
		}
		else team->player[i].fitness = rnd;
	}
	i = 0;
	while (1) {
		if (team->reserved_player[i].id == -1) break;
		int rnd = rand() % 40 + 60;
		if (rnd > 80 && rnd < 90 && j < 2) {
			team->reserved_player[i].fitness = rnd;
			j++;
		}
		else if (rnd > 80 && rnd < 90 && j == 2) {
			i--;
		}
		else if (rnd >= 90 && k == 0) {
			team->reserved_player[i].fitness = rnd;
			k++;
		}
		else if (rnd >= 90 && k == 1) {
			i--;
		}
		else team->reserved_player[i].fitness = rnd;
		i++;
	}
}

void set_skill(TEAM *team) {
	int i = 0;
	int j = 0;
	for (i = 0; i < 11; i++) {
		int rnd = rand() % 40 + 60;
		if (rnd > 80 && rnd < 90 && j < 3) {
			team->player[i].skill = rnd;
			j++;
		}
		else if (rnd > 80 && rnd < 90 && j == 3) {
			i--;
		}
		else if (rnd >= 90) {
			i--;
		}
		else team->player[i].skill = rnd;
	}
	i = 0;
	while (1) {
		if (team->reserved_player[i].id == -1) break;
		int rnd = rand() % 40 + 60;
		if (rnd > 80 && rnd < 90 && j < 3) {
			team->reserved_player[i].skill = rnd;
			j++;
		}
		else if (rnd > 80 && rnd < 90 && j == 3) {
			i--;
		}
		else if (rnd >= 90) {
			i--;
		}
		else team->reserved_player[i].skill = rnd;
		i++;
	}
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
PLAYER *find_bestplayer(TEAM *team, char pos, int zakhire) {
	int i;
	PLAYER *bestplayer=NULL;
	if (zakhire == 1)
		for (i = 0; i < team->noplayers - 12; i++) {
			if (team->reserved_player[i].best_position == pos) {
				if (team->reserved_player[i].fitness + team->reserved_player[i].skill > team->reserved_player[i + 1].fitness + team->reserved_player[i + 1].skill && team->reserved_player[i + 1].best_position == pos)	bestplayer = &(team->reserved_player[i + 1]);
				else bestplayer = &(team->reserved_player[i]);
			}
		}
	else
		for (i = 0; i < 10; i++) {
			if (team->player[i].best_position == pos) {
				printf("%s\n",team->player[i].name);
				if (team->player[i].fitness + team->player[i].skill > team->player[i + 1].fitness + team->player[i + 1].skill && team->player[i + 1].best_position == pos)	bestplayer = &(team->player[i + 1] );
				else bestplayer = &(team->player[i]);
			}
		}
	return bestplayer;
}
PLAYER *find_wrostplayer(TEAM *team, char pos, int zakhire) {
	int i;
	PLAYER *wrostplayer=NULL;
	if (zakhire == 1)
		for (i = 0; i < team->noplayers - 12; i++) {
			if (team->reserved_player[i].best_position == pos) {
				if (team->reserved_player[i].fitness + team->reserved_player[i].skill < team->reserved_player[i + 1].fitness + team->reserved_player[i + 1].skill && team->reserved_player[i+1].best_position == pos)	wrostplayer = &(team->reserved_player[i + 1]);
				else wrostplayer = &(team->reserved_player[i]);
			}
		}
	else
		for (i = 0; i < 10; i++) {
			if (team->player[i].best_position == pos) {
				if (team->player[i].fitness + team->player[i].skill < team->player[i + 1].fitness + team->player[i + 1].skill && team->player[i + 1].best_position == pos)	wrostplayer = &(team->player[i + 1]);
				else wrostplayer = &(team->player[i]);
			}
		}
	return wrostplayer;

}
void change(PLAYER *player1, PLAYER *player2) {
	PLAYER tmp;
	tmp = *player1;
	*player1 = *player2;
	*player2 = tmp;

}
void position(int n, TEAM *team, char pos) {
	int i = 0;
	int j = 0;
	for (j = 0; j < 11; j++)
		if (team->player[j].position == pos) i++;
	j = 0;
	char nxtpos;
	PLAYER *wplayer;
	PLAYER *bplayer;
	if (i == n) return;
	while (i != n) {
		if (i > n) {
			wplayer = find_wrostplayer(team, pos, 0);
			if (pos == 'G') nxtpos = 'D';
			else if (pos == 'D') nxtpos = 'M';
			else if (pos == 'M') nxtpos = 'A';
			bplayer = find_bestplayer(team, nxtpos, 1);
			if (bplayer == NULL) {
				if (nxtpos == 'A') nxtpos = 'G';
				else if (nxtpos == 'D') nxtpos = 'M';
				else if (nxtpos == 'M') nxtpos = 'A';
				bplayer = find_bestplayer(team, nxtpos, 1);

			}
			change(bplayer, wplayer);
			i--;
		}
		else {
			bplayer = find_bestplayer(team, pos, 1);
			if (pos == 'G') nxtpos = 'D';
			else if (pos == 'D') nxtpos = 'M';
			else if (pos == 'M') nxtpos = 'A';
			wplayer = find_wrostplayer(team, nxtpos, 0);
			change(bplayer, wplayer);
			i++;
		}
	}
}


void default_formation(TEAM *team) {
	int i;
	for (i = 0; i < 16; i++) {
		position(1, &team[i], 'G');
		position(4, &team[i], 'D');
		position(3, &team[i], 'M');
	}
}

void team_info(TEAM *team) {
	int i;
	printf("|your main players|                     |MAIN POST|         |SKILL|      |FITNESS|        |FORM|       |CURRENT POST|\n");
	for (i = 0; i < 11; i++) 
			printf("%-40s%-20c%-13d%-17d%-15d%-10c\n", team->player[i].name, team->player[i].best_position, team->player[i].skill, team->player[i].fitness, team->player[i].form, team->player[i].position);
	printf("|your reserved players|                 |MAIN POST|         |SKILL|      |FITNESS|        |FORM|       |CURRENT POST|\n");
	for (i=0;i<team->noplayers-11;i++)
			printf("%-40s%-20c%-13d%-17d%-15d%-10c\n", team->reserved_player[i].name, team->reserved_player[i].best_position, team->reserved_player[i].skill, team->reserved_player[i].fitness, team->reserved_player[i].form, team->reserved_player[i].position);

}

TEAM *search_team_by_id(TEAM *team,int id) {
	int i;
	for (i = 0; i < 16; i++) {
		if (team[i].id == id) return &team[i];
	}
}
