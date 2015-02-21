#include <iostream>
#include <GL/glut.h>

#include "../Header/Planet.h"
#include "../Header/varglob.h"
#include "../Header/float3.h"

<<<<<<< HEAD
//pointeur vers le modele
GLUquadric *sphere = NULL;
Planet planeteTest;
int x_;
int y_;
int z_;

void placerCamera(int x, int y, int z);
=======
//pointeurs utilisees
GLUquadric* sphere = nullptr;
Planet* planetes = nullptr;

//nb de planete max et affichee en ce moment;
const int MAX_PLANETE = 100;
int nPlanete = 5;
>>>>>>> 59dbbeaf23152e8f3b4798b3e33a73e3bb9b3f22

void initialisation()
{
   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // définir le pipeline graphique
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluPerspective(45, (GLdouble)g_largeur / (GLdouble)g_hauteur,15, 300);
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   x_ = 0;
   y_ = -20;
   z_ = 0;
   //placerCamera(x_, y_, z_);
 

   //pointe vers le modele de la sphere
   sphere = gluNewQuadric();

   //Cree toutes les planetes
   planetes = new Planet[MAX_PLANETE];

   // activer le mélange de couleur pour bien voir les possibles plis à l'affichage
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
   glEnable(GL_POINT_SMOOTH);
}

void updatePlanet(Planet& planete, int temps){
	planete.position[0] += planete.speed[0] * temps / 1000.;
	planete.position[1] += planete.speed[1] * temps / 1000.;
	planete.position[2] += planete.speed[2] * temps / 1000.;
}

<<<<<<< HEAD
void placerCamera(int x, int y, int z)
{
	
	gluLookAt(x, y, z,  0, 0, 0,  0, 0, 1);

	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << z << std::endl;
}

void afficherScene()
{

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // définir le pipeline graphique
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(70.0, (GLdouble)g_largeur / (GLdouble)g_hauteur, 0.1, 300.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   placerCamera(x_, y_, z_);

   afficherPlanete(planeteTest);
=======
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

	// indiquer qu'il faut afficher à nouveau
	glutPostRedisplay();
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

	//affiche chacune des planetes
	for (int i = 0; i < nPlanete; i++)
		afficherPlanete(planetes[i]);	
>>>>>>> 59dbbeaf23152e8f3b4798b3e33a73e3bb9b3f22

   glutSwapBuffers();
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

   case 'w':
	   x_ += 10;
	   break;
   case 's':
	   x_ -= 10;
	   break;
   case 'a':
	   y_ += 10;
	   break;
   case 'd':
	   y_ -= 10;
	   break;
   case 'z':
	   z_ += 10;
	   break;
   case 'x':
	   z_ -= 10;
	 
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
