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
				team[i].player[j].newgoal = 0;
				team[i].player[j].main = 1;
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
				team[i].reserved_player[j - 11].newgoal = 0;
				team[i].reserved_player[j - 11].main = -1;
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
			set_other_skill(&(team->player[i]));
			j++;
		}
		else if (rnd > 80 && rnd < 90 && j == 3) {
			i--;
		}
		else if (rnd >= 90) {
			i--;
		}
		else {
			team->player[i].skill = rnd;
			set_other_skill(&(team->player[i]));
		}

	}
	i = 0;
	while (1) {
		if (team->reserved_player[i].id == -1) break;
		int rnd = rand() % 40 + 60;
		if (rnd > 80 && rnd < 90 && j < 3) {
			team->reserved_player[i].skill = rnd;
			set_other_skill(&(team->reserved_player[i]));
			j++;
		}
		else if (rnd > 80 && rnd < 90 && j == 3) {
			i--;
		}
		else if (rnd >= 90) {
			i--;
		}
		else {
			team->reserved_player[i].skill = rnd;
			set_other_skill(&(team->reserved_player[i]));
		}
		i++;
	}
}
void set_other_skill(PLAYER *player) {
	char post = player->best_position;
	int skill = player->skill;
	if (post == 'G') {
		player->G_skill = skill;
		player->D_skill = skill - 30;
		player->M_skill = skill - 35;
		player->A_skill = skill - 40;
	}
	else if (post == 'D') {
		player->G_skill = skill - 40;
		player->D_skill = skill;
		player->M_skill = skill - 20;
		player->A_skill = skill - 30;
	}
	else if (post == 'M') {
		player->G_skill = skill - 40;
		player->D_skill = skill - 10;
		player->M_skill = skill;
		player->A_skill = skill - 10;
	}
	else {
		player->G_skill = skill - 40;
		player->D_skill = skill - 20;
		player->M_skill = skill - 10;
		player->A_skill = skill;
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
void print_teams(TEAM *team) { //chap e team ha
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
	PLAYER *bestplayer = NULL;
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
				printf("%s\n", team->player[i].name);
				if (team->player[i].fitness + team->player[i].skill > team->player[i + 1].fitness + team->player[i + 1].skill && team->player[i + 1].best_position == pos)	bestplayer = &(team->player[i + 1]);
				else bestplayer = &(team->player[i]);
			}
		}
	return bestplayer;
}
PLAYER *find_wrostplayer(TEAM *team, char pos, int zakhire) {
	int i;
	PLAYER *wrostplayer = NULL;
	if (zakhire == 1)
		for (i = 0; i < team->noplayers - 12; i++) {
			if (team->reserved_player[i].best_position == pos) {
				if (team->reserved_player[i].fitness + team->reserved_player[i].skill < team->reserved_player[i + 1].fitness + team->reserved_player[i + 1].skill && team->reserved_player[i + 1].best_position == pos)	wrostplayer = &(team->reserved_player[i + 1]);
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
void check_skill(PLAYER *player) {
	if (player->position == 'G') player->skill = player->G_skill;
	else if (player->position == 'D') player->skill = player->D_skill;
	else if (player->position == 'M') player->skill = player->M_skill;
	else player->skill = player->A_skill;
}
void change(PLAYER *player1, PLAYER *player2, int def) {

	if ((player1->main == -1 && player2->main == 1) || (player1->main == 1 && player2->main == -1) && def == 1) {

		PLAYER tmp;
		player1->main = player1->main*-1;
		player2->main = player2->main*-1;
		tmp = *player1;
		*player1 = *player2;
		*player2 = tmp;
	}
	else if ((player1->main == -1 && player2->main == 1) || (player1->main == 1 && player2->main == -1) && def == 0) {
		char tmp2;
		tmp2 = player1->position;
		player1->position = player2->position;
		player2->position = tmp2;
		PLAYER tmp;
		player1->main = player1->main*-1;
		player2->main = player2->main*-1;
		tmp = *player1;
		*player1 = *player2;
		*player2 = tmp;
	}
	else {
		char tmp;
		tmp = player1->position;
		player1->position = player2->position;
		player2->position = tmp;
	}
	check_skill(player1);
	check_skill(player2);
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
			change(bplayer, wplayer, 1);
			i--;
		}
		else {
			bplayer = find_bestplayer(team, pos, 1);
			if (pos == 'G') nxtpos = 'D';
			else if (pos == 'D') nxtpos = 'M';
			else if (pos == 'M') nxtpos = 'A';
			wplayer = find_wrostplayer(team, nxtpos, 0);
			change(bplayer, wplayer, 1);
			i++;
		}
	}
}
void formation(int a, int b, int c, TEAM *team) {
	position(a, team, 'G');
	position(b, team, 'D');
	position(c, team, 'M');
}
void team_info(TEAM *team) {
	int i;
	printf("|id| |your main players|                   |MAIN POST|         |SKILL|      |FITNESS|        |FORM|       |CURRENT POST|\n");
	for (i = 0; i < 11; i++)
		printf("%-5d%-40s%-20c%-13d%-17d%-15d%-10c\n", i + 1, team->player[i].name, team->player[i].best_position, team->player[i].skill, team->player[i].fitness, team->player[i].form, team->player[i].position);
	printf("|id| |your reserved players|               |MAIN POST|         |SKILL|      |FITNESS|        |FORM|       |CURRENT POST|\n");
	for (i = 0; i < team->noplayers - 11; i++)
		printf("%-5d%-40s%-20c%-13d%-17d%-15d%-10c\n", i + 12, team->reserved_player[i].name, team->reserved_player[i].best_position, team->reserved_player[i].skill, team->reserved_player[i].fitness, team->reserved_player[i].form, team->reserved_player[i].position);

}
TEAM *search_team_by_id(TEAM *team, int id) {
	int i;
	for (i = 0; i < 16; i++) {
		if (team[i].id == id) return &team[i];
	}
}
void teams_formation(TEAM *team) {
	int i = 0;
	for (i = 0; i < 16; i++) {
		formation(1, 4, 3, &team[i]);
	}
}
void taviz(int id1, int id2, TEAM *team) {
	PLAYER *pl1;
	PLAYER *pl2;
	if (id1 >= 11) pl1 = &(team->reserved_player[id1 - 11]);
	else pl1 = &(team->player[id1]);
	if (id2 >= 11) pl2 = &(team->reserved_player[id2 - 11]);
	else pl2 = &(team->player[id2]);
	change(pl1, pl2, 0);
}
void set_team_power(TEAM *team, TEAM *userteam) {
	int i = 0;
	int j = 0;
	int attack = 0;
	int defense = 0;
	for (i = 0; i < 16; i++) {
		attack = 0;
		if (team[i].id == (userteam->id)) {
			for (j = 0; j < 11; j++) {
				if ((userteam->player[j].position == 'A')) {
					attack = userteam->player[j].skill*1.5 + attack;
				}
				else if (userteam->player[j].position == 'M') {
					attack = userteam->player[j].skill + attack;
				}
			}
			userteam->attack = attack;
		}

		else {
			for (j = 0; j < 11; j++) {
				if (team[i].player[j].position == 'A') {
					attack = team[i].player[j].skill*1.5 + attack;
				}
				else if (team[i].player[j].position == 'M') {
					attack = team[i].player[j].skill + attack;
				}
			}
			team[i].attack = attack;
		}

	}
	for (i = 0; i < 16; i++) {
		defense = 0;
		if (team[i].id == (userteam->id)) {
			for (j = 0; j < 11; j++) {
				if ((userteam->player[j].position == 'D')) {
					defense = userteam->player[j].skill*1.5 + defense;
				}
				else if (userteam->player[j].position == 'M') {
					defense = userteam->player[j].skill + defense;
				}
			}
			userteam->deffense = defense;
		}
		else {
			for (j = 0; j < 11; j++) {
				if (team[i].player[j].position == 'D') {
					defense = team[i].player[j].skill*1.5 + defense;
				}
				else if (team[i].player[j].position == 'M') {
					defense = team[i].player[j].skill + defense;
				}
			}
			team[i].deffense = defense;
		}
	}
}
void play_game(TEAM *host, TEAM *guest) {
	//reminder : set kardane gole zade khorde emtiaz va ...   . . . . . . .. .

}
void weekly_games(WEEK *gamesweek, TEAM *team, TEAM *userteam) {
	int nogames = gamesweek->games_in_week;
	int cont = 0;
	int i = 0;
	for (i = 0; i < nogames; i++) {
		cont = gamesweek->current_game;
		TEAM *host = search_team_by_id(team, gamesweek->gid[cont].host_id);
		TEAM *guest = search_team_by_id(team, gamesweek->gid[cont].guest_id);
		if (userteam->id == host->id) host = userteam;
		else if (userteam->id == guest->id) guest = userteam;
		play_game(host, guest);
		(gamesweek->current_game)++;
	}
}
void match_process(WEEK *gamesweek,TEAM *team, TEAM *userteam, int n) {
	int i = 0;
	for (i = 0; i < n; i++) {
	//chap tarikh bargozari bazi ha
		weekly_games(gamesweek,team,userteam);
		//chap natayej bazi
	}
	
}

void simulation(WEEK *gamesweek,TEAM *team, TEAM *userteam, int n) {
	set_team_power(team, userteam);
	int i = 0;
	for (i = 0; i < 16; i++) {
		if (team[i].id == userteam->id)
			printf("team attack : %lf\tteam defense : %lf\n", userteam->attack, userteam->deffense);
		else printf("team attack : %lf\tteam defense : %lf\n", team[i].attack, team[i].deffense);
	}
	match_process(gamesweek,team,userteam,n);
}
void lineup(TEAM *userteam) {
	char input[50];
		system("cls");
		int a, b, c;
		team_info(userteam);
		printf("Now you can change your formation\n");
		printf("Enter the number of deffense :");
		scanf("%d", &a);
		printf("Enter the number of halfback :");
		scanf("%d", &b);
		printf("Enter the number of attack :");
		scanf("%d", &c);
		formation(1, a, b, userteam);
		team_info(userteam);
		printf("\n\nNow you can change your players place or change them when finished enter -1:\n\n");
		while (1) {
			int id1, id2;
			printf("Enter first player id :");
			scanf("%d", &id1);
			if (id1 == -1) break;
			printf("Enter second player id :");
			scanf("%d", &id2);
			taviz(id1 - 1, id2 - 1, userteam);
			team_info(userteam);
		}
}


