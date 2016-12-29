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
void position(int n, TEAM *team,int pos);
PLAYER *find_bestplayer(TEAM *team,int pos , int zakhire);
PLAYER *find_wrostplayer(TEAM *team, int pos,int zakhire);
void change(PLAYER *player1, PLAYER *player2);