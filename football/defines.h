#pragma once
typedef struct playerlist {
	char name[50]; //esme bazikon
	char lastname[50]; //famile bazikon
	int skill;
	int fitness;
	int form;
	int position; //mogheiyati k bazikon bazi mikonad 1=darvaze ban, 2=defa, 3=hafbak,4=hamle
	int best_position; //behtarin mogheiyati k bazikon bazi mikonad 1=darvaze ban, 2=defa, 3=hafbak , 4=hamle


} PLAYER;
typedef struct teamlist
{
	int id;
	char teamname[100]; //esme team
	PLAYER player[11]; //bazi konan
	int score;	//emtiaz team
	int gameplayed; //tedad e bazi anjam shode
	int won; //tedad bazi e borde
	int lost; //tedad bazi e bakhte
	int drawn; //tedad bazi e mosavi shode
	int formation; //tarkib e team
	int attack; //miyangine defa
	int deffense; //miyangin hamle
	int gf; //tedad gole zade (goals for)
	int ga; //tedad gole khorde (goals against)
	int gd; //tafazole gol (goal difference)
	int place; //jaygah dar jadval
} TEAM;
