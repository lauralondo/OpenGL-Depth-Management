/*
 * Laura Londo
 * 9 April 2014
 * HW #7
 */

#include <GL/glut.h>
//#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define screenWidth 1000	//initial screem width
#define screenHeight 700	//initial screen height
//#define waitTime 16 		//millisecond wait between redisplays


int numRecs = 0;
float *recTLx;
float *recTLy;
float *recBRx;
float *recBRy;
float *recZ;


//Function to write a string to the screen at a specified location
void bitmapText(float x, float y, float z, char* words) {
	int len = 0, i = 0;
	//Set the location where the string should appear
	glRasterPos3f(x,y,z);
	len = (int) strlen(words);
	//Set the character in the string to helvetica size 18
	for(int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,words[i]);
	}
}


void initRecs(int argc, char *argv[]) {

	if(argc <= 1) {	//if there were no command line arguments given
		printf("commandline arguments needed: \n");
		printf("number of rectangles\n");
		printf("x of the top left corner of rectangle 1\n");
		printf("y of the top left corner of rectangle 1\n");
		printf("x of the bottom right corner of rectangle 1\n");
		printf("y of the bottom right corner of rectangle 1\n");
		printf("z of rectangle 1\n");
		printf("x of the top left corner of rectangle 2\n");
		printf("...\n");
		exit(0);
	}

	numRecs = atoi(argv[1]);	//number of rectangles

	//declare array sizes
	recTLx = (float *) malloc(numRecs*sizeof(float));
	recTLy = (float *) malloc(numRecs*sizeof(float));
	recBRx = (float *) malloc(numRecs*sizeof(float));
	recBRy = (float *) malloc(numRecs*sizeof(float));
	recZ =   (float *) malloc(numRecs*sizeof(float));

	//initialize array values to the given input values
	for (int i=2; i<numRecs+2; i+=5) {
		recTLx[i] = atof(argv[i]);
		recTLy[i] = atof(argv[i+1]);
		recBRx[i] = atof(argv[i+2]);
		recBRy[i] = atof(argv[i+3]);
		recZ[i] = atof(argv[i+4]);
	}
}


//display callack.
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glColor3f(0.69, 0.29, 0.74);	//purple
		glVertex3f((-1.0/3.0), -1.0,0.5);
		glVertex3f((-1.0/3.0), 1.0,0.5);
		glVertex3f((1.0/3.0), 1.0,0.5);
		glVertex3f((1.0/3.0), -1.0,0.5);
	glEnd();

	glutSwapBuffers();
}

//reshape callback. adjusts both the clipping box and viewport. keeps proportions unchanged
void reshape(int w, int h) {
	float aspectRatio = 1.0;

	//Compute the aspect ratio of the resized window
	aspectRatio = (float)h / (float)w;

	// Adjust the clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h >= w)
		gluOrtho2D(-1.0, 1.0, -aspectRatio, aspectRatio);
	else
		gluOrtho2D(-1.0/aspectRatio, 1.0/aspectRatio, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	//adjust the viewport
	glViewport(0, 0, w, h);
}

//keyboard callback
void keyboard(unsigned char key, int x, int y) {
   	if((int)key == 27) exit(0);		//exit program
}

int main(int argc, char *argv[]) {
	initRecs(argc, argv);

	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 	glutInitWindowSize(screenWidth, screenHeight);
 	glutCreateWindow("depth");
 	glClearColor(0,0,0,0);

 	//The four following statements set up the viewing rectangle
	glMatrixMode(GL_PROJECTION);					// use proj. matrix
	glLoadIdentity();								// load identity matrix
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);				// set orthogr. proj.
	glMatrixMode(GL_MODELVIEW);						// back to modelview m.



	//callbacks
 	glutDisplayFunc(display);			//display
 	glutReshapeFunc(reshape);			//reshape window
 	glutKeyboardFunc(keyboard);			//keyboard

 	glutMainLoop();
	return 0;
}
