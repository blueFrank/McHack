#include <iostream>
#include <GL/glut.h>
#include <math.h>

#include "../Header/Planet.h"
#include "../Header/varglob.h"
#include "../Header/float3.h"

//pointeur vers le modele
GLUquadric *sphere = nullptr;
Planet* planetes = nullptr;
float rayon_;
float theta_; 
float phi_;

void placerCamera(int rayon, int theta, int phi)
{
	float phiRad = DEG2RAD(phi);
	float thetaRad = DEG2RAD(theta);

	gluLookAt(rayon*cos(phiRad)*sin(thetaRad), rayon*cos(phiRad)*cos(thetaRad), rayon*sin(phiRad), 0, 0, 0, 0, 0, 1);
}

//nb de planete max et affichee en ce moment;
const int MAX_PLANETE = 100;
int nPlanete = 50;


void initialisation()
{
   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // définir le pipeline graphique
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective(70., (GLdouble)g_largeur / (GLdouble)g_hauteur, 0.1, 10000);

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   rayon_ = -20;

   //placerCamera(x_, y_, z_);
 

   //pointe vers le modele de la sphere
   sphere = gluNewQuadric();

   //Cree toutes les planetes
   planetes = new Planet[MAX_PLANETE];

   // activer le mélange de couleur pour bien voir les possibles plis à l'affichageh
   //glEnable(GL_SMOOTH);
   glEnable(GL_DEPTH);
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
   glEnable(GL_POINT_SMOOTH);
}

void updatePlanet(Planet& planete, int temps){
	planete.position[0] += planete.speed[0] * temps / 1000.;
	planete.position[1] += planete.speed[1] * temps / 1000.;
	planete.position[2] += planete.speed[2] * temps / 1000.;
}

void collision(Planet& planet1, Planet& planet2){

	//calcul distance
	double deltaX = fabs(planet1.position[0] - planet2.position[0]);
	double deltaY = fabs(planet1.position[1] - planet2.position[1]);
	double deltaZ = fabs(planet1.position[2] - planet2.position[2]);
	double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));

	//Si collision, inverse les vitesses
	if (distance < planet1.rayon + planet2.rayon){

		//calcul du vecteur normal de reflexion
		double vecNormal[3] = { planet1.position[0] - planet2.position[0],
			planet1.position[1] - planet2.position[1],
			planet1.position[2] - planet2.position[2] };


		planet1.speed[0] -= planet1.speed[0];
		planet1.speed[1] -= planet1.speed[1];
		planet1.speed[2] -= planet1.speed[2];
		planet2.speed[0] -= planet2.speed[0];
		planet2.speed[1] -= planet2.speed[1];
		planet2.speed[2] -= planet2.speed[2];
	}

	//ressort de la planete
}

void afficherPlanete(Planet& planete){
	glPushMatrix(); {
		glTranslatef(planete.position[0], planete.position[1], planete.position[2]);
		glColor3f(planete.color[0], planete.color[1], planete.color[2]);
		gluSphere(sphere, planete.rayon, 16, 16);
	} glPopMatrix();
}

void afficherScene()
{

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // définir le pipeline graphique
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45., (GLdouble)g_largeur / (GLdouble)g_hauteur, 0, 300.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   placerCamera(rayon_, theta_, phi_);

   for (int i = 0; i < nPlanete; i++)
		afficherPlanete(planetes[i]);

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
   case '\e':   //escape
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
	   rayon_ += 5.;
	   break;
   case '-':
	   rayon_ -= 5.;
	   break;
   case 'a':
	   theta_ += 5.;
	   break;
   case 'd':
	   theta_ -= 5.;
	   break;
   case 'w':
	   phi_ += 5.;
	   break;
   case 's':
	   phi_ -= 5.;
	 
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
