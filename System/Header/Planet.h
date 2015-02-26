#ifndef _PLANET_H_
#define _PLANET_H_

#include <stdlib.h>
#include <iostream>

static float FACTEUR_MASSE_RAYON = 0.5;
static float MAX_RAYON = 5;
static float MIN_RAYON = 2;
static float MAX_VITESSE = 1;
static float MIN_VITESSE = -1;
static float MAX_COLOR = (float)0.9;
static float MIN_COLOR = (float)0.3;
static float MAX_ALPHA = (float)0.8;
static float MIN_ALPHA = (float)0.5;
static float MAX_POSITION = 100;
static float MIN_POSITION = -100;


class Planet{
public:
	Planet(){
		//position
		position[0] = ((float)rand() / RAND_MAX)*(MAX_POSITION - MIN_POSITION) + MIN_POSITION;
		position[1] = ((float)rand() / RAND_MAX)*(MAX_POSITION - MIN_POSITION) + MIN_POSITION;
		position[2] = ((float)rand() / RAND_MAX)*(MAX_POSITION - MIN_POSITION) + MIN_POSITION;

		//planete gazeuse?
		//std::cout << position[0] << std::endl;
		gazeuse = rand() % 2 == 0;

		//couleur
		color[0] = ((float)rand() / RAND_MAX)*(MAX_COLOR - MIN_COLOR) + MIN_COLOR;
		color[1] = ((float)rand() / RAND_MAX)*(MAX_COLOR - MIN_COLOR) + MIN_COLOR;
		color[2] = ((float)rand() / RAND_MAX)*(MAX_COLOR - MIN_COLOR) + MIN_COLOR;
		color[3] = gazeuse ? ((float)rand() / RAND_MAX)*(MAX_ALPHA - MIN_ALPHA) + MIN_ALPHA : 1;


		//speed
		speed[0] = ((float)rand() / RAND_MAX)*(MAX_VITESSE - MIN_VITESSE) + MIN_VITESSE;
		speed[1] = ((float)rand() / RAND_MAX)*(MAX_VITESSE - MIN_VITESSE) + MIN_VITESSE;
		speed[2] = ((float)rand() / RAND_MAX)*(MAX_VITESSE - MIN_VITESSE) + MIN_VITESSE;

		//rayon
		rayon = ((float)rand() / RAND_MAX)*(MAX_RAYON - MIN_RAYON) + MIN_RAYON;
	}
	//attributs des planetes
	float getMass(){ return rayon * FACTEUR_MASSE_RAYON; }
	float position[3];
	float color[3];
	float speed[3];
	float rayon;
	bool  gazeuse;
};



#endif //_PLANETE_H_