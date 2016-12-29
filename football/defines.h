#pragma once
typedef struct playerlist {
	int id; //
	int number; //shomare bazikon
	char name[50]; //esme bazikon
	int skill;
	int fitness;
	int form; 
	int age; //sen
	int goal; //tedad gole zade
	char position; //mogheiyati k bazikon bazi mikonad G=darvaze ban , D=modafe , M=halfback ,A=mohajem
	char best_position; //behtarin mogheiyati k bazikon bazi mikonad G=darvaze ban , D=modafe , M=halfback ,A=mohajem


} PLAYER;
typedef struct teamlist
{
	int id;
	char teamname[100]; //esme team
	PLAYER player[11]; //bazi konan asli
	PLAYER reserved_player[40]; //zakhire
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
	int noplayers;
} TEAM;
