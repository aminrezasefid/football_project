#pragma once
#pragma once
#include "defines.h"
void print(char str[50]);
void delay(float secs);
TEAM *newleague(TEAM *team);
void print_teams(TEAM *team);
void scoreboard(TEAM *team, TEAM *userteam);
void swap(TEAM *a, TEAM *b);
void default_formation(TEAM *team);
void position(int n, TEAM *team,char pos);
PLAYER *find_bestplayer(TEAM *team,char pos , int zakhire);
PLAYER *find_wrostplayer(TEAM *team, char pos,int zakhire);
void change(PLAYER *player1, PLAYER *player2);
void set_skill(TEAM *team);
void set_fitness(TEAM *team);
void team_info(TEAM *team);
TEAM *search_team_by_id(TEAM *team,int id);