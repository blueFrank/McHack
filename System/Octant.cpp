#include "Octant.h"

Octant::Octant(){
	xMin = MIN_POSITION;
	yMin = MIN_POSITION;
	zMin = MIN_POSITION;

	xMax = MAX_POSITION;
	yMax = MAX_POSITION;
	zMax = MAX_POSITION;
}
bool Octant::estDansOctant(Planet* planete){
	if ((planete->position[0] > xMin) && (planete->position[0]<xMax)
		&& (planete->position[1]>yMin) && (planete->position[1]<yMax)
		&& (planete->position[2]>zMin) && (planete->position[2] < zMax))
		return true;
	else
		return false;

}
void Octant::insertion(Planet* planete){
	if (estDansOctant(planete)){
		if (planeteDansOctant.size()>5)
			planeteDansOctant.push_back(planete);
		else
			planeteDansOctant.push_back(planete);
			subdiviser();
	}

}
void Octant::subdiviser()
{

	hautGaucheAvant= new Octant(xMin/2, yMin, zMin, xMax , yMax / 2, zMax / 2);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		hautGaucheAvant->insertion(planeteDansOctant[i]);
	}
	hautGaucheArriere = new Octant(xMin / 2, yMin, zMin/2, xMax, yMax / 2, zMax);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		hautGaucheArriere->insertion(planeteDansOctant[i]);
	}
	hautDroiteAvant = new Octant(xMin / 2, yMin/2, zMin, xMax, yMax, zMax / 2);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		hautDroiteAvant->insertion(planeteDansOctant[i]);
	}
	hautDroiteArriere = new Octant(xMin / 2, yMin / 2, zMin/2, xMax, yMax, zMax);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		hautDroiteArriere->insertion(planeteDansOctant[i]);
	}
	basGaucheAvant = new Octant(xMin, yMin, zMin, xMax/2, yMax / 2, zMax / 2);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		basGaucheAvant->insertion(planeteDansOctant[i]);
	}
	basGaucheArriere = new Octant(xMin , yMin, zMin / 2, xMax/2, yMax / 2, zMax);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		basGaucheArriere->insertion(planeteDansOctant[i]);
	}
	basDroiteAvant = new Octant(xMin , yMin / 2, zMin, xMax/2, yMax, zMax / 2);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		basDroiteAvant->insertion(planeteDansOctant[i]);
	}
	basDroiteArriere = new Octant(xMin, yMin / 2, zMin / 2, xMax/2, yMax, zMax);
	for (unsigned int i = 0; i < planeteDansOctant.size(); i++){
		basDroiteArriere->insertion(planeteDansOctant[i]);
	}
	planeteDansOctant.clear();
}
Octant::Octant(float xMi, float yMi, float zMi,
	float xMa, float yMa, float zMa){
	xMin = xMi;
	yMin = yMi;
	zMin = zMi;

	xMax = xMa;
	yMax = yMa;
	zMax = zMa;
}
Octant::~Octant()
{

	delete hautDroiteArriere;
	delete basDroiteArriere;
	delete basGaucheArriere;
	delete basDroiteAvant;
	delete basGaucheAvant;
	delete hautDroiteAvant;
	delete hautGaucheArriere;
	delete hautGaucheAvant;


}