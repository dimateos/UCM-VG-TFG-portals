/// TFG_dimateos
/// https://github.com/dimateos/TFG_Portals
/*
Diego Mateos Arlanzón : dimateos@ucm.es

DEGREE IN VIDEOGAME DEVELOPMENT
	FACULTAD DE INFORMÁTICA / UNIVERSIDAD COMPLUTENSE DE MADRID

Degree Final Dissertation in Videogames Development
	Academic year 2019 - 2020 (september)
	Director: Ana Gil Luezas
*/
#include <stdio.h> //print this info
const char *info =
	"/// TFG_dimateos\n"
	"/// https://github.com/dimateos/TFG_Portals\n"
	"\n"
	"Diego Mateos Arlanzon : dimateos@ucm.es\n"
	"\n"
	"DEGREE IN VIDEOGAME DEVELOPMENT\n"
	"	FACULTAD DE INFORMATICA / UNIVERSIDAD COMPLUTENSE DE MADRID\n"
	"\n"
	"Degree Final Dissertation in Videogames Development\n"
	"	Academic year 2019 - 2020 (september)\n"
	"	Director: Ana Gil Luezas\n"
	;

#include "App.h"
App app;

int main(int argc, char* argv[]) {
	bool success = false;

	printf("%s\n", info);
	printf("////////////////////////////////////////////////////////////////////\n");
	printf("////////////////////////////////////////////////////////////////////\n");
	printf("////////////////////////////////////////////////////////////////////\n\n");

	//const float RES = 1.0f;
	const float RES = 4.0f / 3.0f;
	const int RES_H = 900;
	const int RES_W = RES_H * RES;

	success = app.init(RES_W, RES_H);
	if (!success) return -1;
	success = app.start();
	if (!success) return -1;

	return 0;
}