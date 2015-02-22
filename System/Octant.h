#ifndef _OCTANT_H_
#define _OCTANT_H_
#include <stdlib.h>
#include "Header\Planet.h"
#include <vector>

class Octant

{
public : 
	//Nombre max de planéte par partition
	const int maxPlanete = 4;
	std::vector <Planet*> planeteDansOctant;
	Octant();
	Octant(float xMi, float yMi, float zMi,
		   float xMa, float yMa, float zMa);
	Octant* hautGaucheAvant;
	Octant* hautDroiteAvant;
	Octant* basGaucheAvant;
	Octant* basDroiteAvant;
	Octant* hautGaucheArriere;
	Octant* hautDroiteArriere;
	Octant* basGaucheArriere;
	Octant* basDroiteArriere;

	float xMin ;
	float yMin ;
	float zMin;

	float xMax ;
	float yMax ;
	float zMax ;

	bool estDansOctant(Planet* planete);
	void insertion(Planet* planete);
	void subdiviser();

	~Octant();

};
#endif //_OCTANT_H_