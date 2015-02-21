#ifndef _PLANET_H_
#define _PLANET_H_

#include <stdlib.h>

float FACTEUR_MASSE_RAYON = 0.5;
float MAX_RAYON = 5;
float MIN_RAYON = 2;
float MAX_VITESSE = 1;
float MIN_VITESSE = -1;
float MAX_COLOR = 0.9;
float MIN_COLOR = 0.1;
float MAX_POSITION = 100;
float MIN_POSITION = -100;

class Planet{
public:
	Planet(){
		//position
		position[0] = ((double)rand() / RAND_MAX)*(MAX_POSITION - MIN_POSITION) + MIN_POSITION;
		position[1] = ((double)rand() / RAND_MAX)*(MAX_POSITION - MIN_POSITION) + MIN_POSITION;
		position[2] = ((double)rand() / RAND_MAX)*(MAX_POSITION - MIN_POSITION) + MIN_POSITION;

		//couleur
		color[0] = ((double)rand() / RAND_MAX)*(MAX_COLOR - MIN_COLOR) + MIN_COLOR;
		color[1] = ((double)rand() / RAND_MAX)*(MAX_COLOR - MIN_COLOR) + MIN_COLOR;
		color[2] = ((double)rand() / RAND_MAX)*(MAX_COLOR - MIN_COLOR) + MIN_COLOR;

		//speed
		speed[0] = ((double)rand() / RAND_MAX)*(MAX_VITESSE - MIN_VITESSE) + MIN_VITESSE;
		speed[1] = ((double)rand() / RAND_MAX)*(MAX_VITESSE - MIN_VITESSE) + MIN_VITESSE;
		speed[2] = ((double)rand() / RAND_MAX)*(MAX_VITESSE - MIN_VITESSE) + MIN_VITESSE;

		//rayon
		rayon = ((double)rand() / RAND_MAX)*(MAX_RAYON - MIN_RAYON) + MIN_RAYON;
	}

	//attributs des planetes
	float getMass(){ return rayon * FACTEUR_MASSE_RAYON; }
	float position[3];
	float color[3];
	float speed[3];
	float rayon;
};



#endif //_PLANETE_H_