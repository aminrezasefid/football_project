#pragma once
#pragma once
#include "defines.h"
void play_game(TEAM *host,TEAM *guest);
void print_sched(TEAM *team, WEEK *gamesweek);
void nextgames(TEAM *team,WEEK *gamesweek);
void print(char str[50]);
void delay(float secs);
TEAM *newleague(TEAM *team);
void print_teams(TEAM *team);
void scoreboard(TEAM *team, TEAM *userteam);
void swap(TEAM *a, TEAM *b);
void formation(int a, int c, int b,TEAM *team);
void position(int n, TEAM *team,char pos);
PLAYER *find_bestplayer(TEAM *team,char pos , int zakhire);
PLAYER *find_wrostplayer(TEAM *team, char pos,int zakhire);
void change(PLAYER *player1, PLAYER *player2,int def);
void set_skill(TEAM *team);
void set_fitness(TEAM *team);
void team_info(TEAM *team);
TEAM *search_team_by_id(TEAM *team,int id);
void teams_formation(TEAM *team);
void taviz(int id1, int id2, TEAM *team);
void check_skill(PLAYER *player);
void set_other_skill(PLAYER *player);
void simulation(WEEK *gamesweek,TEAM *team, TEAM *userteam, int n);
void set_team_power(TEAM *team, TEAM *userteam);
void lineup(TEAM *userteam);
void weekly_games(WEEK *gamesweek,TEAM *team, TEAM *userteam);
void match_process(WEEK *gamesweek,TEAM *team, TEAM *userteam, int n);