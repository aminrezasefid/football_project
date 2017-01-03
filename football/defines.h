#pragma once
struct playerlist {
	int id; //
	int number; //shomare bazikon
	char name[50]; //esme bazikon
	int skill;
	int fitness;
	int form; 
	int newgoal; //tedad gole zade dar bazi e akhar
	int age; //sen
	int goal; //tedad gole zade
	char position; //mogheiyati k bazikon bazi mikonad G=darvaze ban , D=modafe , M=halfback ,A=mohajem
	char best_position; //behtarin mogheiyati k bazikon bazi mikonad G=darvaze ban , D=modafe , M=halfback ,A=mohajem
	int main; // moteghayer baraye inke befhmim bazikon asli hast ya na  (1 bazikon asli hast va -1 bazikon zakhire hast)
	int G_skill; //maharate darvaze bani
	int D_skill; //maharate defa
	int M_skill; // maharate hafback
	int A_skill; // maharate hamle
};
typedef struct playerlist PLAYER;
struct teamlist
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
	double attack; //miyangine defa
	double deffense; //miyangin hamle
	int gf; //tedad gole zade (goals for)
	int ga; //tedad gole khorde (goals against)
	int gd; //tafazole gol (goal difference)
	int place; //jaygah dar jadval
	int noplayers;
};
typedef struct teamlist TEAM;
