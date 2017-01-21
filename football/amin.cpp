#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include "header.h"
#include "defines.h"
PLAYER sort_goaler(PLAYER *goalers) {
	int i = 0;
	PLAYER bst_goaler;
	bst_goaler = goalers[0];
	for (i = 1; i < 16; i++) {
		if (goalers[i].goal > bst_goaler.goal) bst_goaler = goalers[i];
	}
	return bst_goaler;
}
PLAYER mr_goal(TEAM *team, TEAM *userteam) {
	int i = 0;
	int j = 0;
	PLAYER goaler[16];
	for (i = 0; i < 16; i++) {
		TEAM *t;
		if (team[i].id == userteam->id) t = userteam;
		else t = team + i;
		goaler[i]=t->player[0];
		for (j = 1; j<11; j++) {
			if (t->player[j].goal > goaler[i].goal) goaler[i] = t->player[j];
		}
		for (j = 1; j < t->noplayers - 11; j++) {
			if (t->reserved_player[j].goal > goaler[i].goal) goaler[i] = t->reserved_player[j];
		}
	}
	PLAYER best = sort_goaler(goaler);
	return best;
}
TEAM *newleague(TEAM *team) { //tabe baraye khandane etela'at e team ha va bazi konan
	srand(time(NULL));
	FILE *fptr = fopen("teams.csv", "r");
	int j = 0, i = 0;
	for (i = 0; i < 16; i++) {
		fgets(team[i].teamname, sizeof(team[i].teamname), fptr);
		strtok(team[i].teamname, "\n");
		set_team_id(&team[i]);
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
		team[i].form = 0;
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
				char *ch;
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
				team[i].player[j].rank = 1;
			}
			else {
				team[i].reserved_player[j - 11].id = j+1;
				char *ch;
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
				team[i].reserved_player[j - 11].rank = 1;
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
void set_team_id(TEAM *team) {
	static int a[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	static int i = 15;
	int j = rand() % (i + 1);
	team->id = a[j];
	int tmp = a[j];
	a[j] = a[i];
	a[i] = tmp;
	i--;
}
void set_fitness(TEAM *team) {
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < 11; i++) {
		int rnd;
		if (team->player[i].age < 25) rnd = rand() % 20 + 81;
		else if (team->player[i].age < 30) rnd = rand() % 20 + 61;
		else if (team->player[i].age >= 30) rnd = rand() % 20 + 41;
		team->player[i].fitness = rnd;
		team->player[i].max_fitness = rnd;
	}
	i = 0;
	while (1) {
		if (team->reserved_player[i].id == -1) break;
		int rnd;
		if (team->reserved_player[i].age < 25) rnd = rand() % 20 + 81;
		else if (team->reserved_player[i].age < 30) rnd = rand() % 20 + 61;
		else if (team->reserved_player[i].age >= 30) rnd = rand() % 20 + 41;
		team->reserved_player[i].fitness = rnd;
		team->reserved_player[i].max_fitness = rnd;
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
		if (i % 2 == 0) SetColor(8);
		else SetColor(15);
	}
	SetColor(15);
}
void sort_team(TEAM *team, TEAM *userteam) {
	int i = 0, j = 0;
	TEAM *a = search_team_by_id(team, userteam->id);
	*a = *userteam;
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
	sort_team(team, userteam);
	SetColor(4);
	print("TEAM                     SCORE    WON    DRAWN     LOST    GF    GA    GD\n"); //print teams
	SetColor(15);
	for (i = 0; i < 16; i++) {
		team[i].place = i + 1;
		if (i % 2 == 0) SetColor(8);
		else SetColor(15);
		if (team[i].id == userteam->id) {
			SetColor(11);
			printf("%-25s%-9d%-7d%-10d%-8d%-6d%-6d%-5d\n", team[i].teamname, team[i].score, team[i].won, team[i].drawn, team[i].lost, team[i].gf, team[i].ga, team[i].gd);
			userteam->place = i + 1;
			SetColor(15);
			continue;
		}
		printf("%-25s%-9d%-7d%-10d%-8d%-6d%-6d%-5d\n", team[i].teamname, team[i].score, team[i].won, team[i].drawn, team[i].lost, team[i].gf, team[i].ga, team[i].gd);
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
	int total_player = 0;
	for (j = 0; j < 11; j++)
		if (team->player[j].position == pos) i++;
	for (j = 0; j < 11; j++) {
		if (team->player[j].best_position == pos) total_player++;
	}
	for (j = 0; j < team->noplayers - 11; j++) {
		if (team->reserved_player[j].best_position == pos) total_player++;
	}
	if (n > total_player) {
		printf("there is not enough player in post %c !!!!", pos);
		delay(2);
		lineup(team);
	}
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
void formation(int a, int b, int c,int d, TEAM *team) {
	if (a + b + c + d> 11) {
		printf("\n\n\nincorrect number of players !!!!\n\n\n");
		delay(1);
		lineup(team);
	}
	position(a, team, 'G');
	position(b, team, 'D');
	position(c, team, 'M');
}
void team_info(TEAM *team) {
	int i;
	SetColor(12);
	printf("|id| |your main players|                   |MAIN POST|         |SKILL|      |FITNESS|        |FORM|       |CURRENT POST|\n");
	SetColor(15);
	for (i = 0; i < 11; i++)
	{
		if (i % 2 == 0) SetColor(8);
		else SetColor(15);
		printf("%-5d%-40s%-20c%-13d%-17d%-15d%-10c\n", i + 1, team->player[i].name, team->player[i].best_position, team->player[i].skill, team->player[i].fitness, team->player[i].form, team->player[i].position);
	}
	SetColor(12);
	printf("|id| |your reserved players|               |MAIN POST|         |SKILL|      |FITNESS|        |FORM|       |CURRENT POST|\n");
	SetColor(15);
	for (i = 0; i < team->noplayers - 11; i++) {
		if (i % 2 == 0) SetColor(8);
		else SetColor(15);
		printf("%-5d%-40s%-20c%-13d%-17d%-15d%-10c\n", i + 12, team->reserved_player[i].name, team->reserved_player[i].best_position, team->reserved_player[i].skill, team->reserved_player[i].fitness, team->reserved_player[i].form, team->reserved_player[i].position);
	}
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
		formation(1, 4, 3, 3,&team[i]);
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
	int form = 0;
	for (i = 0; i < 16; i++) {
		attack = 0;
		if (team[i].id == (userteam->id)) {
			for (j = 0; j < 11; j++) {
				if ((userteam->player[j].position == 'A')) {
					attack = (userteam->player[j].skill*1.5 + userteam->player[j].fitness) / 2 + attack;
				}
				else if (userteam->player[j].position == 'M') {
					attack = (userteam->player[j].skill + userteam->player[j].fitness) / 2 + attack;
				}
			}
			userteam->attack = attack;
		}

		else {
			for (j = 0; j < 11; j++) {
				if (team[i].player[j].position == 'A') {
					attack = (team[i].player[j].skill*1.5 + team[i].player[j].fitness) / 2 + attack;
				}
				else if (team[i].player[j].position == 'M') {
					attack = (team[i].player[j].skill + team[i].player[j].fitness) / 2 + attack;
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
					defense = (userteam->player[j].skill*1.5 + userteam->player[j].fitness) / 2 + defense;
				}
				else if (userteam->player[j].position == 'M') {
					defense = (userteam->player[j].skill + userteam->player[j].fitness) / 2 + defense;
				}
			}
			userteam->deffense = defense;
		}
		else {
			for (j = 0; j < 11; j++) {
				if (team[i].player[j].position == 'D') {
					defense = (team[i].player[j].skill*1.5 + team[i].player[j].fitness) / 2 + defense;
				}
				else if (team[i].player[j].position == 'M') {
					defense = (team[i].player[j].skill + team[i].player[j].fitness) / 2 + defense;
				}
			}
			team[i].deffense = defense;
		}
	}
	for (i = 0; i < 16; i++) {
		form = 0;
		if (team[i].id == (userteam->id)) {
			for (j = 0; j < 11; j++) {
				userteam->form = userteam->form + userteam->player[j].form;
			}

		}

		else {
			for (j = 0; j < 11; j++) {
				team[i].form = team[i].form + team[i].player[j].form;
			}
		}

	}
}
void goal_process(TEAM *team1, TEAM *team2) {
	PLAYER *attacker[6];
	PLAYER *defenser[7];

	int j = 0;
	int i = 0;
	for (i = 0; i < 11; i++) {
		if (team1->player[i].position == 'A') {
			attacker[j] = &(team1->player[i]);
			j++;
		}
	}
	int nA = j;
	j = 0;
	for (i = 0; i < 11; i++) {
		if (team2->player[i].position == 'D' || team2->player[i].position == 'G') {
			defenser[j] = &(team2->player[i]);
			defenser[j]->form = defenser[j]->form - 1;
			j++;
		}
	}
	for (i = 0; i < nA; i++) {
		attacker[i]->form = attacker[i]->form + attacker[i]->form * 3 / 100;
		
	}
	i = 0;
	int probabality = 0;
	while (1) {
		if (attacker[i]->form > 170) probabality = 50;
		else if (attacker[i]->form > 140) probabality = 40;
		else if (attacker[i]->form > 110) probabality = 30;
		else if (attacker[i]->form > 80) probabality = 20;
		else if (attacker[i]->form > 50) probabality = 10;
		else probabality = 5;
		int cal = rand() % 100 + 1;
		if (cal < probabality) {
			attacker[i]->newgoal++;
			break;
		}
		i++;
		if (i == nA) i = 0;
	}
}
int host_process(TEAM *host, TEAM *guest) {
	int diff = host->attack + 100 - guest->deffense;

	int probable_goal = 0;
	int probablity = 0;
	int hostgoal = 0;
	if (diff >40) probable_goal = rand() % 3 + 3;
	else if (diff > 20) probable_goal = rand() % 2 + 2;
	else probable_goal = 1;
	int i = 0;
	if ((host->form - guest->form) > 200) probablity = 65;
	else if ((host->form - guest->form) > 100) probablity = 55;
	else if ((host->form - guest->form) > 50) probablity = 45;
	else if ((host->form - guest->form) > 0) probablity = 35;
	else probablity = 25;
	probablity = probablity + 15;
	for (i = 0; i < probable_goal; i++) {
		int cal = rand() % 100 + 1;
		if (cal < probablity) {
			goal_process(host, guest);
			hostgoal++;
		}
	}
	return hostgoal;
}
int guest_process(TEAM *host, TEAM *guest) {
	int diff = guest->attack + 100 - host->deffense;

	int probable_goal = 0;
	int probablity = 0;
	int guestgoal = 0;
	if (diff > 40) probable_goal = rand() % 3 + 3;
	else if (diff > 20) probable_goal = rand() % 2 + 2;
	else probable_goal = 1;
	int i = 0;
	if ((guest->form - host->form) > 200) probablity = 65;
	else if ((guest->form - host->form) > 100) probablity = 55;
	else if ((guest->form - host->form) > 50) probablity = 45;
	else if ((guest->form - host->form) > 0) probablity = 35;
	else probablity = 25;
	for (i = 0; i < probable_goal; i++) {
		int cal = rand() % 100 + 1;
		if (cal < probablity) {
			goal_process(guest, host);
			guestgoal++;
		}
	}
	return guestgoal;

}
void reservedplayers_form(TEAM *team1, TEAM *team2) {
	int i = 0;
	for (i = 0; i < team1->noplayers - 11; i++) {
		team1->reserved_player[i].form = team1->reserved_player[i].form - team1->reserved_player[i].form * 3 / 100;
	}
	for (i = 0; i < team2->noplayers - 11; i++) {
		team2->reserved_player[i].form = team2->reserved_player[i].form - team2->reserved_player[i].form * 3 / 100;
	}

}
void find_goaler(PLAYER *goaler, TEAM *team) {
	int i = 0;
	int j = 0;
	for (i = 0; i < 11; i++) {
		if (team->player[i].newgoal != 0) {
			team->player[i].goal = team->player[i].goal + team->player[i].newgoal;
			goaler[j] = team->player[i];
			team->player[i].newgoal = 0;
			j++;
		}
	}

}
void change_feature(TEAM *winner, TEAM *looser) {
	int i = 0;
	for (i = 0; i < 11; i++) {
		winner->player[i].form = winner->player[i].form + winner->player[i].form * 5 / 100;
		looser->player[i].form = looser->player[i].form - looser->player[i].form * 5 / 100;
	}
	for (i = 0; i < 11; i++) {
		winner->player[i].fitness = winner->player[i].fitness - winner->player[i].fitness / 10;
		looser->player[i].fitness = looser->player[i].fitness - looser->player[i].fitness / 10;
	}
	for (i = 0; i < winner->noplayers - 11; i++) {
		winner->reserved_player[i].fitness = winner->reserved_player[i].fitness + rand() % 6 + 10;
		if (winner->reserved_player[i].fitness > winner->reserved_player[i].max_fitness) winner->reserved_player[i].fitness = winner->reserved_player[i].max_fitness;
	}
	for (i = 0; i < looser->noplayers - 11; i++) {
		looser->reserved_player[i].fitness = looser->reserved_player[i].fitness + rand() % 6 + 10;
		if (looser->reserved_player[i].fitness > looser->reserved_player[i].max_fitness) looser->reserved_player[i].fitness = looser->reserved_player[i].max_fitness;
	}
}
void play_game(TEAM *host, TEAM *guest) {
	host->gameplayed++; //ezafe kardan e tedad bazi haye anjam shode baraye team ha
	guest->gameplayed++; //ezafe kardan e tedad bazi haye anjam shode baraye team ha
	reservedplayers_form(host, guest);
	int nh = host_process(host, guest); //pardazesh bazi mizban va rikhtane tedad gole zadeye in team dar moteghayere nh
	int ng = guest_process(host, guest);//pardazesh bazi mihman va rikhtane tedad gole zadeye in team dar moteghayere ng
	if ((nh - ng) == 0) { //bazi mosavi shode
		host->drawn += 1; //ezafe kardane tedad bazi haye mosavi shode 
		host->score += 1; //ezafe shodane 1 emtiaz be team
		host->gf += nh; //set kardane goal haye zade
		host->ga += ng; //set kardane goal haye khorde
		host->gd = host->gf - host->ga;  //set kardane tafazol e goal
										 //anjam amaliat haye bala rooye team e mihman
		guest->drawn++;
		guest->score++;
		guest->gf += ng;
		guest->ga += nh;
		guest->gd = guest->gf - guest->ga;
	}
	else if ((nh - ng) > 0) { //team mizban mibarad
		change_feature(host, guest); //taghirate koli roohiye va fitness
		host->won++;
		host->score += 3;
		host->gf += nh;
		host->ga += ng;
		host->gd = host->gf - host->ga;
		guest->lost++;
		guest->gf += ng;
		guest->ga += nh;
		guest->gd = guest->gf - guest->ga;
	}
	else { //teame mihman mibarad
		change_feature(guest, host);
		host->lost++;
		host->gf += nh;
		host->ga += ng;
		host->gd = host->gf - host->ga;
		guest->won++;
		guest->score += 3;
		guest->gf += ng;
		guest->ga += nh;
		guest->gd = guest->gf - guest->ga;
	}
	char tmp[400];
	PLAYER *host_goaler;
	PLAYER *guest_goaler;
	host_goaler = (PLAYER *)calloc(5, sizeof(PLAYER));
	guest_goaler = (PLAYER *)calloc(5, sizeof(PLAYER));
	find_goaler(host_goaler, host);
	find_goaler(guest_goaler, guest);
	static int ord = 0;
	if (ord == 0) {
		SetColor(8); 
		ord = 1;
	}
	else {
		SetColor(15);
		ord = 0;
	}
	printf("%-25s%d-%d%25s\n", host->teamname, nh, ng, guest->teamname);
	SetColor(15);
	int j = 0;
	int i = 0;
	while (j < (nh + ng)) {
		char tmp2[60];
		SetColor(11);
		if (host_goaler[i].newgoal == 0) printf("%-25s%s %d%25s\n", " ", " ", guest_goaler[i].newgoal, guest_goaler[i].name);
		if (guest_goaler[i].newgoal == 0) printf("%-25s%d %s%25s\n", host_goaler[i].name, host_goaler[i].newgoal, " ", " ");
		if (guest_goaler[i].newgoal != 0 && host_goaler[i].newgoal != 0) printf("%-25s%d %d%25s\n", host_goaler[i].name, host_goaler[i].newgoal, guest_goaler[i].newgoal, guest_goaler[i].name);
		SetColor(15);
		//strcat(tmp, tmp2);
		j = j + host_goaler[i].newgoal + guest_goaler[i].newgoal;
		i++;
	}
	printf("\n\n");
	//strcat(games_res, tmp);
}
void check_formation(TEAM *team) {
	int i = 0;
	for (i = 0; i < 11; i++) {
		if (team->player[i].fitness < 40) {
			PLAYER *bplayer=find_bestplayer(team,team->player[i].position,1);
			if (bplayer == NULL) return;
			if ((bplayer->fitness+bplayer->skill) > (team->player[i].skill + team->player[i].fitness))	change(bplayer, &(team->player[i]),1);
		}
	}
}
void weekly_games(WEEK *gamesweek, TEAM *team, TEAM *userteam) {
	int nogames = gamesweek->games_in_week; //tedad bazi hayi k bayad dar 1 hafte bazi beshe
	char date[100] = {};
	calendar(date, 50);
	char *firstday;
	char *secondday;
	firstday=strtok(date,",");
	secondday = strtok(NULL, ",");
	char games_res[2000] = "result of week "; //motaghayer baraye elam e natayej
	char tmp[1000];
	if (gamesweek->current_game >=240) {		
		printf("The league is over , do you want to start a new league?(yes/no) ");
		char choose[5];
		scanf("%s", choose);
		if (strcmp(choose, "yes") == 0) newleague(team);
		else return;
	}
	sprintf(tmp, "%d\nDate: %s\n", (gamesweek->current_game / gamesweek->games_in_week) + 1,firstday); //shomare gozari hafte haye dar hal bar gozari
	strcat(games_res, tmp);
	SetColor(1);
	printf("%s", games_res);
	sprintf(tmp, "%-25s%3s%25s\n", "host team", "V S", "guest team");
	//strcat(games_res, tmp);
	int cont = 0;
	int i = 0;
	SetColor(4);
	printf("%s", tmp); //elame natayej bazi haye 1 hafte
	SetColor(15);
	for (i = 0; i < nogames; i++) { //bargozari bazi haye 1 hafte
		SetColor(1);
		if (i == 4) printf("Date:%s\n", secondday);
		SetColor(15);
		cont = gamesweek->current_game; //shomare bazi k gharar ast anjam beshe
		TEAM *host = search_team_by_id(team, gamesweek->gid[cont].host_id); //entekhab teame mizban
		TEAM *guest = search_team_by_id(team, gamesweek->gid[cont].guest_id); //entekhab teame mihman
		if (userteam->id == host->id) { 
			host = userteam; 
			check_formation(guest);
		} //check kardabe inke teame user bazi dare ya na
		else if (userteam->id == guest->id) { 
			guest = userteam;
			check_formation(host);
		} //check kardabe inke teame user bazi dare ya na
		else {
			check_formation(guest);
			check_formation(host);
		}
		play_game(host, guest); //shoroo e bazi beyne 2 team
		(gamesweek->current_game)++; //afazayesh shomare bazi
	}
	if ((gamesweek->current_game / gamesweek->games_in_week) + 1 > 30) {
	PLAYER best=mr_goal(team, userteam);
		SetColor(4);
		printf("The Master Of Goal Is %s With %d Goal\n", best.name, best.goal);
		SetColor(15);
	}
}
void match_process(WEEK *gamesweek, TEAM *team, TEAM *userteam, int n) {
	int i = 0;
	for (i = 0; i < n; i++) { //tedad hafte hayi ke gharar ast shbih sazi konim
							  //chap tarikh bargozari bazi ha
		weekly_games(gamesweek, team, userteam); //bargozari 1 hafte az baziha
	}

}
void loading(char sit) {
	int i = 0;
	char statement[50];
	SetColor(14);
	if (sit == 's') strcpy(statement, "Simulating ");
	else if (sit == 'l')strcpy(statement, "Loading ");
	else if (sit == 'S')strcpy(statement, "Saving ");
	printf("%s", statement);
	int rnd = rand() % 3 + 3;
	while (rnd) {
		printf(". ");
		delay(0.5);
		rnd--;
		i++;
		if (i % 3 == 0) {
			printf("\b\b\b\b\b\b      \b\b\b\b\b\b");
		}
	}
	printf("\n");
	SetColor(15);
}
void simulation(WEEK *gamesweek, TEAM *team, TEAM *userteam, int n) { //shoroo e tabe shabih sazi
	loading('s');
	set_team_power(team, userteam); // set kardane ghodrate hamle va defa va form e team
	match_process(gamesweek, team, userteam, n); // tabe badi vase shabih sazi
}
void lineup(TEAM *userteam) {
	char input[50];
	int a, b, c;
	team_info(userteam);
	SetColor(1);
	int choice = 0;
	while (1){
	do {
		printf("Enter 1 for changing the formation or 2 for substitution or 0 to go back: ");
		SetColor(15);
		scanf("%d", &choice);
	} while (choice != 1 && choice != 0 && choice != 2);
	if (choice == 1) {
		printf("Now you can change your formation\n");
		SetColor(10);
		printf("Enter the number of deffense :");
		SetColor(15);
		scanf("%d", &a);
		SetColor(10);
		printf("Enter the number of halfback :");
		SetColor(15);
		scanf("%d", &b);
		SetColor(10);
		printf("Enter the number of attack :");
		SetColor(15);
		scanf("%d", &c);
		formation(1, a, b, c,userteam);
		team_info(userteam);
		SetColor(1);
		continue;
	}
	else if (choice == 2) {
		printf("\n\nNow you can change your players place or change them when finished enter -1:\n\n");
		SetColor(10);
		while (1) {
			int id1, id2;
			SetColor(10);
			printf("Enter first player id :");
			SetColor(15);
			scanf("%d", &id1);
			if (id1 == -1) break;
			SetColor(10);
			printf("Enter second player id :");
			SetColor(15);
			scanf("%d", &id2);
			taviz(id1 - 1, id2 - 1, userteam);
			team_info(userteam);
		}
		continue;
	}
	else if (choice == 0) return;
	else continue;
	}
}
void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

