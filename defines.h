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
	char teamname[100]; //esme team
	PLAYER player[11]; //bazi konan
	int score=0;	//emtiaz team
	int gameplayed=0; //tedad e bazi anjam shode
	int won=0; //tedad bazi e borde
	int lost=0; //tedad bazi e bakhte
	int drawn=0; //tedad bazi e mosavi shode
	int formation=0; //tarkib e team
	int attack; //miyangine defa
	int deffense; //miyangin hamle
	int gf=0; //tedad gole zade (goals for)
	int ga=0; //tedad gole khorde (goals against)
	int gd=0; //tafazole gol (goal difference)
} TEAM;
