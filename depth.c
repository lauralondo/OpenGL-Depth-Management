/*
 * Laura Londo
 * 9 April 2014
 * HW #7 Depth Management
 *
 * Program demonstrates depth management using ray casting on 2D rectangles.
 * User enters the number of rectangles then the x & y coordinates of the
 * top left corner and bottom right corners and the z coordinate for each
 * rectangle.
 * rectangles with smaller z values will be rendered in front of further
 * rectangles.
 *
 * Directions:
 * 	user may press a numbered key 0-9 to choose a rectangle to move.
 * 	arrow keys move the rectangle on the x and y axis
 * 	f moves the rectangle forwards, towards the viewer
 * 	b moves the rectangle back away from the viewer
 * 	press esc to exit the program
 *
 * a suggested input:   2  -1000 400 400 -800 5   100 100 1000 -400 4
 */

#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define screenWidth 700	//initial screem width
#define screenHeight 700	//initial screen height



int numRecs = 0;	//number of rectangles passed in
float *recTLx;
float *recTLy;
float *recBRx;
float *recBRy;
float *recZ;
float colors[][3] = {	{1,0,0},	//red
						{0,1,0},	//green
						{0,0,1},	//blue
						{0,1,1},	//cyan
						{1,0,1},	//magenta
						{1,1,0} };	//yellow

int selRec = 0;		//the currenlty selected rectangle to move




//initializes the rectangle coordinate arrays to the passed in values
void initRecs(int argc, char *argv[]) {
	if(argc < 2) {	//if there were no command line arguments given
		printf("\ncommandline arguments needed: \n");
		printf("number of rectangles\n");
		printf("x of the top left corner of rectangle 1\n");
		printf("y of the top left corner of rectangle 1\n");
		printf("x of the bottom right corner of rectangle 1\n");
		printf("y of the bottom right corner of rectangle 1\n");
		printf("z of rectangle 1\n");
		printf("x of the top left corner of rectangle 2\n");
		printf("...\n\n");
		printf("a suggested input:   2  -1000 400 400 -800 5  100 100 1000 -400 4\n\n");
		exit(0);
	}

	numRecs = atoi(argv[1]);	//get number of rectangles

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
	else {	//not the right number of arguments per rectangle
		printf("incorrect number of arguments.\n");
		printf("\ncommandline arguments needed: \n");
		printf("number of rectangles\n");
		printf("x of the top left corner of rectangle 1\n");
		printf("y of the top left corner of rectangle 1\n");
		printf("x of the bottom right corner of rectangle 1\n");
		printf("y of the bottom right corner of rectangle 1\n");
		printf("z of rectangle 1\n");
		printf("x of the top left corner of rectangle 2\n");
		printf("...\n\n");
		printf("a suggested input:   2  -1000 400 400 -800 5  100 100 1000 -400 4\n\n");
		exit(0);
	}
} //end initRecs


//display callack.
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

	float x, y, z, t;

	//loop through each pixel in the viewing plane
	for (int h=-350; h<screenHeight/2; h++) {		//loop through vertical pixels
		for (int w=-350; w<screenWidth/2; w++) {	//loop through horiz pixels
			z = FLT_MAX;		//the max depth so far (max possible)
			glColor3f(0,0,0);	//default color (the background color)

			//loop through each rectangle
			for(int r=0; r<numRecs;r++) {

				if(recZ[r] < z) {	//if the current rectangle is closer,

					t = recZ[r];	//get the depth of the current rectangle
					x = w*t;		//get the real-world x coordinate for this pixel
					y = h*t;		//get the real-world y coordinate for this pixel

					//if the x y coordinates are within this rectangle,
					if(x<recBRx[r] && x>recTLx[r] && y<recTLy[r] && y>recBRy[r]) {
						glColor3fv(colors[r%5]); //set the current color to this rectangle's color
						z = t;
					}
				}
			} //end for each rectangle

			//draw this pixel
			glBegin(GL_POINTS);
			glVertex2f(w,h);
			glEnd();
		}
	}//end loop through pixels

	glutSwapBuffers();
} //end display


//keyboard callback
void keyboard(unsigned char key, int x, int y) {
   	if((int)key == 27) 	//exit program
   		exit(0);
   	if(key == 'f')		//move rectangle towards the viewer
   		recZ[selRec] -= 1;
   	if(key == 'b')		//move the rectangle back away from viewer
   		recZ[selRec] += 1;

   	//enable user to select a rectangle to move
   	if(key == '0')
   		selRec = 0;
   	if(key == '1')
   		selRec = 1;
   	if(key == '2')
   		selRec = 2;
   	if(key == '3')
   		selRec = 3;
   	if(key == '4')
   		selRec = 4;
   	if(key == '5')
   		selRec = 5;
   	if(key == '6')
   		selRec = 6;
   	if(key == '7')
   		selRec = 7;
   	if(key == '8')
   		selRec = 8;
   	if(key == '9')
   		selRec = 9;

   	//if an invalid rectangle number was selected, reset to 0
   	if (selRec >= numRecs) selRec = 0;

   	glutPostRedisplay();
} //end keyboard


//special keys used to move the currently selected rectangle
void specialKey(int key, int x, int y) {
   	if(key == GLUT_KEY_UP) {	//move rectangle up
   		recTLy[selRec] += 50;
   		recBRy[selRec] += 50;
   	}
   	if(key == GLUT_KEY_DOWN) {	//move rectangle down
		recTLy[selRec] -= 50;
   		recBRy[selRec] -= 50;
   	}
   	if(key == GLUT_KEY_RIGHT) {	//move rectangle right
   		recTLx[selRec] += 50;
   		recBRx[selRec] += 50;
   	}
   	if(key == GLUT_KEY_LEFT) {	//move rectangle left
   		recTLx[selRec] -= 50;
   		recBRx[selRec] -= 50;
   	}
   	glutPostRedisplay();
}


//main method
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
	gluOrtho2D(-350, 350, -350, 350);	// set orthogr. proj.
	glMatrixMode(GL_MODELVIEW);			// back to modelview m.

	//callbacks
 	glutDisplayFunc(display);			//display
 	glutKeyboardFunc(keyboard);			//keyboard
 	glutSpecialFunc(specialKey);		//special keys

 	glutMainLoop();
	return 0;
} //end main
