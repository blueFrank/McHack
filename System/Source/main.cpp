// Prénoms, noms et matricule des membres de l'équipe:
// - Prénom1 NOM1 (matricule1)
// - Prénom2 NOM2 (matricule2)

#include <iostream>
#include <GL/glut.h>
#include "../Header/varglob.h"
#include "../Header/float3.h"

#if 1
// pour un W
float p1[3] = { -4.0,  2.0,  0.0 };
float p2[3] = { -3.0, -3.0,  0.0 };
float p3[3] = { -1.0, -3.0,  0.0 };
float p4[3] = {  0.0,  0.0,  0.0 };
float p5[3] = {  1.0, -3.0,  0.0 };
float p6[3] = {  3.0, -3.0,  0.0 };
float p7[3] = {  4.0,  2.0,  0.0 };
#else
// pour une flèche (Voir apprentissage supplémentaire)
float p1[3] = { -3.0,  1.0,  0.0 };
float p2[3] = { -3.0, -1.0,  0.0 };
float p3[3] = {  0.0, -1.0,  0.0 };
float p4[3] = { -0.5, -2.5,  0.0 };
float p5[3] = {  3.0,  0.0,  0.0 };
float p6[3] = { -0.5,  2.5,  0.0 };
float p7[3] = {  0.0,  1.0,  0.0 };
#endif

void initialisation()
{
   // donner la couleur de fond
   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   // définir le pipeline graphique
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( -12, 12, -8, 8, -10, 10 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   // activer le mélange de couleur pour bien voir les possibles plis à l'affichage
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void afficherScene()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   //premiere ligne
   glColor3f(1.0, 1.0, 1.0);		//couleur blanche
   glLoadIdentity();				//position
   glBegin(GL_LINES);
	   //ligne 1
	   glVertex3f(-12, 0.0, 0);
	   glVertex3f(12, 0.0, 0);
	   //ligne 2
	   glVertex3f(-4.0, 8.0, 0);
	   glVertex3f(-4.0, -8.0, 0); 
	   //ligne 3
	   glVertex3f(4.0, 8.0, 0);
	   glVertex3f(4.0, -8.0, 0);
   glEnd();
					
   glColor4f(1, 0, 0,0.8);			// utiliser du rouge
   glTranslatef(-8.0, 4.0, 0);		//position 
   glBegin(GL_QUADS);
		//quad 1
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
		//quad 2
		glVertex3fv(p4);
		glVertex3fv(p5);
		glVertex3fv(p6);
		glVertex3fv(p7);
		//quad 3
		glVertex3fv(p1);
		glVertex3fv(p4);
		glVertex3fv(p7);
		glVertex3fv(p1);  
   glEnd();

   glColor4f(0,1,0,0.8);			// utiliser du vert
   glTranslatef(8, 0, 0);		//position 
   glBegin(GL_TRIANGLES);
		//triangle 1
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		//triangle 2
		glVertex3fv(p1);
		glVertex3fv(p3);
		glVertex3fv(p4);
		//triangle 3
		glVertex3fv(p1);
		glVertex3fv(p4);
		glVertex3fv(p7);
		//triangle 4
		glVertex3fv(p4);
		glVertex3fv(p5);
		glVertex3fv(p7);
		//triangle 5
		glVertex3fv(p7);
		glVertex3fv(p5);
		glVertex3fv(p6);
   glEnd();

   glColor4f(0, 0, 1, 0.8);		// utiliser du bleu
   glTranslatef(8, 0, 0);		//position 
   glBegin(GL_POLYGON);
	   //polygone1 (doit etre convexe)
	   glVertex3fv(p4);			//point duquel partent tout les triangles formant le polygone
								//(NE PAS UTILISER CETTE OPTIMISATION, PAS GARANTIE)
	   glVertex3fv(p3);
	   glVertex3fv(p2);
	   glVertex3fv(p1);
	   glVertex3fv(p7);
	   glVertex3fv(p6);
	   glVertex3fv(p5);
   glEnd();
   
   glColor4f(1, 1, 0, 0.8);		// utiliser du jaune
   glTranslatef(0, -8.0, 0);	//position 
   glBegin(GL_QUAD_STRIP);
		//quad 1
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p1);
		glVertex3fv(p4);
		//quad 2
		glVertex3fv(p7);
		glVertex3fv(p4);
		//quad 3
		glVertex3fv(p6);
		glVertex3fv(p5);
   glEnd();

   glColor4f(1, 0, 1, 0.8);		// utiliser du rose
   glTranslatef(-8, 0, 0);	//position 
   glBegin(GL_TRIANGLE_STRIP);
		//triangle 1
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p1);
		//triangle 2
		glVertex3fv(p4);
		//triangle 3
		glVertex3fv(p7);
		//triangle 3
		glVertex3fv(p5);
		//triangle 3
		glVertex3fv(p6);
   glEnd();

   glColor4f(0, 1, 1, 0.8);		// utiliser du bleu ciel
   glTranslatef(-8, 0, 0);		//position 
   glBegin(GL_TRIANGLE_FAN);
	   glVertex3fv(p4);			//point duquel partent tout les triangles formant la fan
	   glVertex3fv(p3);
	   glVertex3fv(p2);
	   glVertex3fv(p1);
	   glVertex3fv(p7);
	   glVertex3fv(p6);
	   glVertex3fv(p5);
   glEnd();


   //3 point alignes
   glColor4f(1, 0.5, 0, 0.8);		// utiliser du vert
   glLoadIdentity();
   glTranslatef(0, 0.5, 0);			//position 
   glBegin(GL_TRIANGLES);
	   //triangle 1
	   glVertex3f(-3,0,0);
	   glVertex3f(0,0,0);
	   glVertex3f(3,0,0);
   glEnd();

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
   }
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
   g_feneID = glutCreateWindow( "INF2705" );

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

   initialisation();

   // boucle principale de gestion des événements
   glutMainLoop();

   // le programme n'arrivera jamais jusqu'ici
   return EXIT_SUCCESS;
}
