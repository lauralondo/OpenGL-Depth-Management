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
float colors[6][3] = {	{1,0,0},	//red
						{0,1,0},	//green
						{0,0,1},	//blue
						{0,1,1},	//cyan
						{1,0,1},	//magenta
						{1,1,0} };	//yellow


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


//initializes the rectangle coordinate arrays to the passed in values
void initRecs(int argc, char *argv[]) {
	if(argc < 2) {	//if there were no command line arguments given
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

	printf("\nnumber of rectangles =  %d\n\n", numRecs);

	if(argc-2 == numRecs*5) {	//if correct number of arguments (5 per rect.)
		printf("initializing!\n\n");
		//initialize array values to the given input values
		for (int i=2, recNumber=0; i<argc; i+=5, recNumber++) {
			recTLx[recNumber] = atof(argv[i]);		//x coord of top left
			recTLy[recNumber] = atof(argv[i+1]);	//y coord of top left
			recBRx[recNumber] = atof(argv[i+2]);	//x coord of bottom right
			recBRy[recNumber] = atof(argv[i+3]);	//y coord of bottom right
			recZ[recNumber]   = atof(argv[i+4]);	//z coord of rectangle
		}
	}
	else {						//not the right number of arguments
		printf("incorrect number of arguments.\n");
		exit(0);
	}
} //end initRecs


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

//reshape callback. adjusts clipping box & viewport. keeps proportions unchanged
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
} //end reshape

//keyboard callback
void keyboard(unsigned char key, int x, int y) {
   	if((int)key == 27) exit(0);		//exit program
   	//
} //end keyboard

int main(int argc, char *argv[]) {
	initRecs(argc, argv);				//initialize rectangle coordinates

	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 	glutInitWindowSize(screenWidth, screenHeight);
 	glutCreateWindow("Depth Management");
 	glClearColor(0,0,0,0);

 	//The four following statements set up the viewing rectangle
	glMatrixMode(GL_PROJECTION);		// use proj. matrix
	glLoadIdentity();					// load identity matrix
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);	// set orthogr. proj.
	glMatrixMode(GL_MODELVIEW);			// back to modelview m.



	//callbacks
 	glutDisplayFunc(display);			//display
 	glutReshapeFunc(reshape);			//reshape window
 	glutKeyboardFunc(keyboard);			//keyboard

 	glutMainLoop();
	return 0;
}
