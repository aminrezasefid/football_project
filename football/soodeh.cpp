#include "Header.h"
#include "header.h"
#include "defines.h"
#include <Windows.h>
#include <stdio.h>
void save(WEEK games_week, TEAM *team,TEAM *userteam)
{
	int i=0, j=0;

	for (j = 0; j<16; j++) {
		char path[100] = "savedgame/";
		if (team[j].id == userteam->id) team[j]=*userteam;
		strcat(path, team[j].teamname);
		FILE *fptr = fopen(path, "w");
		if (team[j].id == userteam->id)	fprintf(fptr, "*%s-", team[j].teamname);
		else fprintf(fptr, "%s-", team[j].teamname);
		fprintf(fptr, "%d-", team[j].id);
		fprintf(fptr, "%d-", team[j].score);   
		fprintf(fptr, "%d-", team[j].gameplayed);
		fprintf(fptr, "%d-", team[j].won);	
		fprintf(fptr, "%d-", team[j].lost);
		fprintf(fptr, "%d-", team[j].drawn);
		fprintf(fptr, "%d-", team[j].formation);
		fprintf(fptr, "%d-", team[j].attack);
		fprintf(fptr, "%d-", team[j].deffense);
		fprintf(fptr, "%d-", team[j].form);		
		fprintf(fptr, "%d-", team[j].gf);
		fprintf(fptr, "%d-", team[j].ga);	
		fprintf(fptr, "%d-", team[j].gd);
		fprintf(fptr, "%d-", team[j].place);  
		fprintf(fptr, "%d\n", team[j].noplayers);
		for (i = 0; i<11; i++) {
			fprintf(fptr, "%d-", team[j].player[i].id);    
			fprintf(fptr, "%d-", team[j].player[i].number);
			fprintf(fptr, "%s-", team[j].player[i].name);	
			fprintf(fptr, "%d-", team[j].player[i].skill);
			fprintf(fptr, "%d-", team[j].player[i].fitness);
			fprintf(fptr, "%d-", team[j].player[i].form);
			fprintf(fptr, "%d-", team[j].player[i].newgoal);	
			fprintf(fptr, "%d-", team[j].player[i].age);
			fprintf(fptr, "%d-", team[j].player[i].goal);	
			fprintf(fptr, "%c-", team[j].player[i].position);
			fprintf(fptr, "%c-", team[j].player[i].best_position);	
			fprintf(fptr, "%d-", team[j].player[i].main);
			fprintf(fptr, "%d-", team[j].player[i].G_skill);	
			fprintf(fptr, "%d-", team[j].player[i].D_skill);
			fprintf(fptr, "%d-", team[j].player[i].M_skill);	
			fprintf(fptr, "%d\n", team[j].player[i].A_skill);
		}

		for (i = 0; i<team[j].noplayers - 11; i++) {
			fprintf(fptr, "%d-", team[j].reserved_player[i].id);  
			fprintf(fptr, "%d-", team[j].reserved_player[i].number);
			fprintf(fptr, "%s-", team[j].reserved_player[i].name);	
			fprintf(fptr, "%d-", team[j].reserved_player[i].skill);
			fprintf(fptr, "%d-", team[j].reserved_player[i].fitness);
			fprintf(fptr, "%d-", team[j].reserved_player[i].form);
			fprintf(fptr, "%d-", team[j].reserved_player[i].newgoal);
			fprintf(fptr, "%d-", team[j].reserved_player[i].age);
			fprintf(fptr, "%d-", team[j].reserved_player[i].goal);	
			fprintf(fptr, "%c-", team[j].reserved_player[i].position);
			fprintf(fptr, "%c-", team[j].reserved_player[i].best_position);	
			fprintf(fptr, "%d-", team[j].reserved_player[i].main);
			fprintf(fptr, "%d-", team[j].reserved_player[i].G_skill);	
			fprintf(fptr, "%d-", team[j].reserved_player[i].D_skill);
			fprintf(fptr, "%d-", team[j].reserved_player[i].M_skill);	
			fprintf(fptr, "%d\n", team[j].reserved_player[i].A_skill);
		}
		fclose(fptr);
	}
	FILE *gptr = fopen("savedgame/current_game.txt", "w");
	fprintf(gptr, "%d\n", games_week.current_game);
	fclose(gptr);
}
TEAM *loadleague(TEAM *team, WEEK *games_week){
	TEAM *user;
	int i, j;
	FILE *gptr = fopen("teams.csv", "r");
	for (i = 0; i<16; i++) {
		char str[200] = {};
		const char s[2] = "-";
		char *tok;
		fgets(team[i].teamname, sizeof(team[i].teamname), gptr);
		strtok(team[i].teamname, "\n");
		char path[100] = "savedgame/";
		strcat(path, team[i].teamname);
		FILE *fptr = fopen(path, "r");
		fgets(str, 200, fptr);
		tok = strtok(str, s);
		if (tok[0] == '*') {
			user = &(team[i]);
			strcpy(team[i].teamname, tok+1);
		}
		else strcpy(team[i].teamname, tok); 
		tok = strtok(NULL, s);
		team[i].id = atoi(tok);       
		tok = strtok(NULL, s);
		team[i].score = atoi(tok);   
		tok = strtok(NULL, s);
		team[i].gameplayed = atoi(tok);  
		tok = strtok(NULL, s);
		team[i].won = atoi(tok);      
		tok = strtok(NULL, s);
		team[i].lost = atoi(tok);     
		tok = strtok(NULL, s);
		team[i].drawn = atoi(tok);    
		tok = strtok(NULL, s);
		team[i].formation = atoi(tok);   
		tok = strtok(NULL, s);
		team[i].attack = atoi(tok);		
		tok = strtok(NULL, s);
		team[i].deffense = atoi(tok);	
		tok = strtok(NULL, s);
		team[i].form = atoi(tok);		
		tok = strtok(NULL, s);
		team[i].gf = atoi(tok);		
		tok = strtok(NULL, s);
		team[i].ga = atoi(tok);		
		tok = strtok(NULL, s);
		team[i].gd = atoi(tok);		
		tok = strtok(NULL, s);
		team[i].place = atoi(tok);	
		tok = strtok(NULL, s);
		team[i].noplayers = atoi(tok);  
		tok = strtok(NULL, s);
		for (j = 0; j<11; j++) {
			char string[100];
			fgets(string, 99, fptr);
			char *token;
			token = strtok(string, s);
			team[i].player[j].id = atoi(token); 
			token = strtok(NULL, s);
			team[i].player[j].number = atoi(token);	
			token = strtok(NULL, s);
			strcpy(team[i].player[j].name, token);	
			token = strtok(NULL, s);
			team[i].player[j].skill = atoi(token);	
			token = strtok(NULL, s);
			team[i].player[j].fitness = atoi(token);
			token = strtok(NULL, s);
			team[i].player[j].form = atoi(token);		
			token = strtok(NULL, s);
			team[i].player[j].newgoal = atoi(token);	
			token = strtok(NULL, s);
			team[i].player[j].age = atoi(token);		
			token = strtok(NULL, s);
			team[i].player[j].goal = atoi(token);		
			token = strtok(NULL, s);
			team[i].player[j].position= token[0];		
			token = strtok(NULL, s);
			team[i].player[j].best_position=token[0]; 
			token = strtok(NULL, s);
			team[i].player[j].main = atoi(token);		
			token = strtok(NULL, s);
			team[i].player[j].G_skill = atoi(token);	
			token = strtok(NULL, s);
			team[i].player[j].D_skill = atoi(token);	
			token = strtok(NULL, s);
			team[i].player[j].M_skill = atoi(token);
			token = strtok(NULL, s);
			team[i].player[j].A_skill = atoi(token);	
			token = strtok(NULL, s);
		}
		for (j = 0; j<team[i].noplayers - 11; j++) {
			char string[200];
			fgets(string, 200, fptr);
			char *token;
			token = strtok(string, s);
			team[i].reserved_player[j].id = atoi(token);     			token = strtok(NULL, s);
			team[i].reserved_player[j].number = atoi(token);			token = strtok(NULL, s);
			strcpy(team[i].reserved_player[j].name, token);				token = strtok(NULL, s);
			team[i].reserved_player[j].skill = atoi(token);				token = strtok(NULL, s);
			team[i].reserved_player[j].fitness = atoi(token);			token = strtok(NULL, s);
			team[i].reserved_player[j].form = atoi(token);				token = strtok(NULL, s);
			team[i].reserved_player[j].newgoal = atoi(token);			token = strtok(NULL, s);
			team[i].reserved_player[j].age = atoi(token);				token = strtok(NULL, s);
			team[i].reserved_player[j].goal = atoi(token);				token = strtok(NULL, s);
			team[i].reserved_player[j].position = token[0];				token = strtok(NULL, s);
			team[i].reserved_player[j].best_position = token[0];		token = strtok(NULL, s);
			team[i].reserved_player[j].main = atoi(token);				token = strtok(NULL, s);
			team[i].reserved_player[j].G_skill = atoi(token);			token = strtok(NULL, s);
			team[i].reserved_player[j].D_skill = atoi(token);			token = strtok(NULL, s);
			team[i].reserved_player[j].M_skill = atoi(token);			token = strtok(NULL, s);
			team[i].reserved_player[j].A_skill = atoi(token);			token = strtok(NULL, s);
		}

		fclose(fptr);
	}
	fclose(gptr);
	FILE *sptr=fopen("savedgame/current_game.txt", "r");
	if (sptr == NULL) printf("asdasda\n");
	else {
		fscanf(sptr, "%d", &(games_week->current_game));
		fclose(sptr);
	}
	return user;
}
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