
#include <iostream>
#include <GL/glut.h>
#include <math.h>

#include "../Header/Planet.h"
#include "../Header/varglob.h"
#include "../Header/float3.h"

//variables globales
const int MAX_PLANETE = 100;
int nPlanete = 50;

//pointeur vers le modele et les planetes
GLUquadric *sphere = nullptr;
Planet* planetes = nullptr;


void placerCamera()
{
	float phiRad = DEG2RAD(phi);
	float thetaRad = DEG2RAD(theta);

	gluLookAt(dist*cos(DEG2RAD(theta))*sin(DEG2RAD(phi)),
			  dist*sin(DEG2RAD(phi))*sin(DEG2RAD(theta)),
			  dist*cos(DEG2RAD(phi)),
			  0, 0, 0,
			  0, 0, 1);
}

void initialisation()
{
   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // définir le pipeline graphique
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective(45, (GLdouble)g_largeur / (GLdouble)g_hauteur, 0.1, 10000);

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   //position initiale de la camera
   dist = 100;
   phi = 90;
   theta = 0;

   //pointeur vers le modele de la sphere
   sphere = gluNewQuadric();

   //Cree toutes les planetes
   planetes = new Planet[MAX_PLANETE];

   //glEnable(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void updatePlanet(Planet& planete, int temps){
	float newPos[3];
	newPos[0] = planete.position[0] + planete.speed[0] * temps / 1000.;
	newPos[1] = planete.position[1] + planete.speed[1] * temps / 1000.;
	newPos[2] = planete.position[2] + planete.speed[2] * temps / 1000.;

	planete.position[0] = newPos[0];
	planete.position[1] = newPos[1];
	planete.position[2] = newPos[2];
}

//calcul distance
double calculerDistance(float p1[], float p2[]){
	double deltaX = fabs(p1[0] - p2[0]);
	double deltaY = fabs(p1[1] - p2[1]);
	double deltaZ = fabs(p1[2] - p2[2]);
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
}

double getFacteurInversion(float* vecNorm, float* position){
	//calcul du plan de reflexion
	double plan[4];
	plan[0] = vecNorm[0];
	plan[1] = vecNorm[1];
	plan[2] = vecNorm[2];
	plan[3] = -(plan[0] * position[0] +	plan[1] * position[1] +	plan[2] * position[2]);

	//calcul du facteur d'inversion
	return 2 * (plan[0] * position[0] +
				plan[1] * position[1] +
				plan[2] * position[2] +
				plan[3])
				/
			   (pow(plan[0], 2) +
			    pow(plan[1], 2) +
				pow(plan[2], 2));
}

void collision(Planet& planet1, Planet& planet2){

	//Si collision, inverse les vitesses
	if (calculerDistance(planet1.position,planet2.position) < planet1.rayon + planet2.rayon){

		std::cout << "COLLISION!\n";

		//calcul du vecteur normal du plan de reflexion
		float vecNormal[3] = { planet1.position[0] - planet2.position[0],
							   planet1.position[1] - planet2.position[1],
							   planet1.position[2] - planet2.position[2] };

		double fac1 = getFacteurInversion(vecNormal, planet1.position);
		double fac2 = getFacteurInversion(vecNormal, planet2.position);

		planet1.speed[0] -= fac1 * planet1.speed[0];
		planet1.speed[1] -= fac1 * planet1.speed[1];
		planet1.speed[2] -= fac1 * planet1.speed[2];
		planet2.speed[0] -= fac2 * planet2.speed[0];
		planet2.speed[1] -= fac2 * planet2.speed[1];
		planet2.speed[2] -= fac2 * planet2.speed[2];

		//ressort de la planete
		do{
			updatePlanet(planet1, 1);
			updatePlanet(planet2, 1);
		} while (calculerDistance(planet1.position, planet2.position) < planet1.rayon + planet2.rayon);
	}


}

void afficherPlanete(Planet& planete){
	glPushMatrix(); {
		glTranslatef(planete.position[0], planete.position[1], planete.position[2]);
		glColor4f(planete.color[0], planete.color[1], planete.color[2], planete.color[3]);
		gluSphere(sphere, planete.rayon, 16, 16);
	} glPopMatrix();
}

void afficherScene()
{

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   placerCamera();
  
   //affiche toutes les planetes pas gazeuses
   glDisable(GL_BLEND);
   for (int i = 0; i < nPlanete; i++)
	   if (planetes[i].gazeuse == false)
			afficherPlanete(planetes[i]);
   glEnable(GL_BLEND);

   //affiche toutes les planetes gazeuses
   glDepthMask(GL_FALSE);	//desactive l'ecriture tampon profondeur
   for (int i = 0; i < nPlanete; i++)
	   if (planetes[i].gazeuse == true)
		   afficherPlanete(planetes[i]);
   glDepthMask(GL_TRUE);	//active l'ecriture tampon profondeur

   glutSwapBuffers();
}

static void animer(int tempsPrec)
{
	// obtenir le temps depuis le début du programme, en millisecondes
	int tempsCour = glutGet(GLUT_ELAPSED_TIME);
	if (tempsPrec == 0) tempsPrec = tempsCour;

	// temps d'attente en secondes avant le prochain affichage
	const int FPS = 60;  // en "images/seconde"
	const int delai = 1000 / FPS;  // en "millisecondes/image" (= 1000 millisecondes/seconde  /  images/seconde)
	glutTimerFunc(delai, animer, tempsCour);

	//Update chaque planete
	for (int i = 0; i < nPlanete; i++)
		updatePlanet(planetes[i], delai);

	//Verifie si collision TODO:UTILISER QUADTREE
	for (int i = 0; i < nPlanete; i++)
		for (int j = 0; j < nPlanete; j++)
			if (i != j)
				collision(planetes[i], planetes[j]);


	// indiquer qu'il faut afficher à nouveau
	glutPostRedisplay();
}


void redimensionnement( GLsizei w, GLsizei h )
{
   g_largeur = w;
   g_hauteur = h;
   glViewport( 0, 0, w, h );
   glutPostRedisplay();
}

void clavier( unsigned char touche, int x, int y )
{
   //printf( "%d",touche);
   switch ( touche )
   {
   case 27:		//escape(ascii)
      glutDestroyWindow( g_feneID );
	  delete[] planetes;
      exit( 0 );
      break;

   case 'g':
	  //va chercher les proprietes (front et back)
	  int result[2];
	  glGetIntegerv(GL_POLYGON_MODE, result);

	  //toggle entre les 2
	  if (result[0] == GL_FILL)
		  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  else
		  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	  
	  // la fenêtre a besoin d'être réafficher
	  glutPostRedisplay();
      break;

   case '+':
	   dist -= 5.;
	   break;
   case '-':
	   dist += 5.;
	   break;
   case 'a':
	   theta -= 5.;
	   break;
   case 'd':
	   theta += 5.;
	   break;
   case 'w':
	   phi -= 5.;
	   break;
   case 's':
	   phi += 5.;
   }
   afficherScene();
}

void clavierSpecial( int touche, int x, int y )
{
}

void sourisClic( int button, int state, int x, int y )
{
}

void sourisMouvement( int x, int y )
{
}

int main( int argc, char *argv[] )
{
   // initialisation de GLUT
   glutInit( &argc, argv );
   // paramétrage de l'affichage
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
   // taille de la fenetre
   glutInitWindowSize( g_largeur, g_hauteur );
   // création de la fenêtre
   g_feneID = glutCreateWindow( "McHacks" );

   // référencement de la fonction de rappel pour l'affichage
   glutDisplayFunc( afficherScene );
   // référencement de la fonction de rappel pour le redimensionnement
   glutReshapeFunc( redimensionnement );
   // référencement de la fonction de gestion des touches
   glutKeyboardFunc( clavier );
   // référencement de la fonction de gestion des touches spéciales
   glutSpecialFunc( clavierSpecial );
   // référencement de la fonction de rappel pour le mouvement de la souris
   glutMotionFunc( sourisMouvement );
   // référencement de la fonction de rappel pour le clic de la souris
   glutMouseFunc( sourisClic );

   //initialise la scene
   initialisation();
   //demarre l'animation
   animer(0);

   // boucle principale de gestion des événements
   glutMainLoop();

   // le programme n'arrivera jamais jusqu'ici
   return EXIT_SUCCESS;
}
