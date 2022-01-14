//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
double startx=320,starty=400;
double speed=1000.0;
int durl=2,fdx,fdy,hdl_x,hdl_y,hdl1_x,hdl1_y,bar_size=0,win=0,size=4,score=0,cl=54,i,j,bx=80,by=660,p_x,p_y,gameover=0,l=1,cl1=88,menu=1,opt;
int snake[100][2]={{200,400},{190,400},{180,400},{170,400}};
int arr[100][100],food[5][2],hurdle[100][2],hurdle1[100][2],hurdle2[100][2],hurdle3[100][2],score_bar[100][2],a=10;
 
void drawsnake(int snake[100][2],int size)//function for drawing snake
{  
	DrawCircle( snake[0][0]+5,snake[0][1]+5 ,7,colors[cl1]);
	for(int i=1;i<size;i++)
	DrawSquare( snake[i][0],snake[i][1],10,colors[cl1]);
}
void movement(int snake[100][2],int durl)//directions
{  
	for(int i=size-1;i>0;i--)
	{
		snake[i][0]=snake[i-1][0];
	
		snake[i][1]=snake[i-1][1];
	}
	
       if(durl==1)	 //left
  	{
			snake[0][0]-=10;
  	}
  	else if(durl==2) //right
  	{
        	        snake[0][0]+=10;
  	}
 	else if(durl==3) //up
  	{
			snake[0][1]+=10;

  	}
  	else if(durl==4) //down
   	{
        	          snake[0][1]-=10;
   	}
}
void snake_hurdle(int hurdle[100][2],int hdl_x,int hdl_y) // hurdle 1
{
	for(i=0;i<20;i++)
	{
		hurdle[i][0]=hdl_x;
		hurdle[i][1]=hdl_y;
		DrawSquare(hurdle[i][0],hurdle[i][1],11,colors[130]);
		hdl_y+=10;
	}
}
void snake_hurdle1(int hurdle1[100][2],int hdl_x,int hdl_y) //hurdle 2
{  
	for(i=0;i<20;i++)
	{
		hurdle1[i][0]=hdl_x;
		hurdle1[i][1]=hdl_y;
		DrawSquare(hurdle1[i][0],hurdle1[i][1],11,colors[130]);
		hdl_x+=10;
	}
} 

void fill_bar(int score_bar[100][2],int bar_size, int bx, int by)//function for drawing snake
{  
	for(i=0;i<bar_size;i++)
	{		
		DrawSquare( bx,by,11,colors[28]);
		bx+=10;
			
	}
}
void boundry() // function for boundry
{
	for(int i=0;i<72;i++) 
 	{
    			DrawSquare( 0 , i*10,11,colors[30]);  
  	}
	for(int i=0;i<72;i++) 
   	{
    			DrawSquare( 640 , i*10,11,colors[30]);  
  	}
	for(int i=0;i<65;i++) 
  	{
    			DrawSquare( i*10,0,11,colors[30]);  
  	}
	for(int i=0;i<65;i++) 
   	{
    			DrawSquare( i*10,640,11,colors[30]);  
  	}
}
void Display()
{
	glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);   //Update the color
if(menu==1)
{
	for(int i=0;i<65;i++) 
   	{
		for(int j=0;j<72;j++)
		{
    			DrawSquare( i*10 , j*10,11,colors[43]);  
		}
  	}
	DrawString(230,500,"start",colors[88]);
	DrawString(230,400, "resume",colors[88]);
	DrawString(230,300,"history",colors[88]);
	DrawString(230,200, "help",colors[88]);
	DrawTriangle(160,505,160,515,170,510,colors[23]);
	if(durl==3)
	{
		DrawTriangle(10,505-a,10,515-a,11,510-a,colors[23]);
		opt=1;
		menu=0;
	}
}
else
{

if(win==0)
{
if(gameover==0)
{	
	for(int i=0;i<65;i++) //loop for grid
   	{
		for(int j=0;j<65;j++)
		{
    			DrawSquare( i*10 , j*10,10,colors[cl]);  //This will draw a square shape of size 100x100  at x=300 and y=300
		}
  	}
   	for(int i=0;i<65;i++) // array for grid
   	{
        	for(int j=0;j<65;j++)
        	{
        	        arr[i][j]=0;  
        	}
	}
	

	
	drawsnake(snake,size);

	switch (durl) // directions
	{
		case 1: //left
			movement(snake,durl);
			break;
		case 2: //right
			movement(snake,durl);
			break;
		case 3: //up
 			movement(snake,durl);
			break;
		case 4: //down
			movement(snake,durl);
			break;
	}
	
	for(i=0;i<5;i++) // loop for food generation
	{
		DrawSquare( food[i][0],food[i][1],10,colors[14]);
	}
	DrawCircle( p_x+5,p_y+5 ,10,colors[23]);
	
	for(int i=0;i<5;i++) // snake eating food
	{
		if( (snake[0][0]==food[i][0]) && (snake[0][1]==food[i][1]) )
		{
			snake[size][0]=food[i][0];
			snake[size][1]=food[i][1];
			size++;
			score+=5;
			food[i][0]=(rand()%60)*10;
			food[i][1]=(rand()%60)*10;
			bar_size++;
		}
	}
		if((snake[0][0]==p_x) && (snake[0][1]==p_y)) // power food eating
		{		
			snake[size][0]=p_x;
			snake[size][1]=p_y;			
			score+=15;
			size++;
			p_x=(rand()%60)*10;
			p_y=(rand()%60)*10;
			bar_size+=3;
		}	
	if(score>=50 && score<100) // display hurdle for level 2
	{		
		if(score==50)
		{			
			bar_size=0;
		}
		l=2;
		cl=19;
		cl1=5;
		speed=1000.0-250.0;
		snake_hurdle(hurdle,hdl_x,hdl_y);
	}
	if(score>=100 && score<150) // display hurdle for level 3
	{	
		if(score==100)
		{
		bar_size=0;
		}
		l=3;
		cl=139;
		cl1=141;
		speed=1000.0-500.0;
	 	snake_hurdle(hurdle,hdl_x,hdl_y);
		snake_hurdle1(hurdle1,hdl_x,hdl_y);
	}
	
	if(score==150 )
		win=1;
	for(i=0;i<20;i++) // hurdle collision
	{
		if((snake[0][0]==hurdle[i][0] && snake[0][1]==hurdle[i][1]) ||( snake[0][0]==hurdle1[i][0] && snake[0][1]==hurdle1[i][1]))
		gameover=1;
	}
	for(int i=0;i<65;i++) // grid for score
   	{
		for(int j=65;j<72;j++)
		{
    			DrawSquare( i*10 , j*10,11,colors[13]);  
		}
  	}
	
boundry();
DrawLine(80, 665, 180, 665, 11, colors[129]);
DrawString(10,660,"score",colors[76]);																					DrawString(10,680,to_string(score),colors[MISTY_ROSE]);																		
DrawString(590,660,"level",colors[76]);																DrawString(610,680,to_string(l),colors[MISTY_ROSE]);													fill_bar(score_bar,bar_size,bx,by);
}
else
{
	for(int i=0;i<65;i++)
   	{
		for(int j=0;j<72;j++)
		{
    			DrawSquare( i*10 , j*10,11,colors[23]);  //This will draw a square shape of size 100x100  at x=300 and y=300
		}
  	}
	boundry();
	DrawString(200,400,"GAME OVER",colors[31]);
    	DrawString(200,300, "YOUR SCORE",colors[34]);
	DrawString(250,200, to_string(score),colors[88]);
}		
}
else
{
	
	for(int i=0;i<65;i++)
   	{
		for(int j=0;j<72;j++)
		{
    			DrawSquare( i*10 , j*10,11,colors[27]);  //This will draw a square shape of size 100x100  at x=300 and y=300
		}
  	}
	boundry();
	DrawString(220,400,"CONGRATULATIONS",colors[88]);
	DrawString(220,200, "YOU HAVE CLEARED ALL LEVELS",colors[88]);

}  
}   
	glutSwapBuffers(); // do not modify this line..
}

void NonPrintableKeys(int key, int x, int y)  
{
	if (key == GLUT_KEY_LEFT)
	{
		if(durl!=2)
			durl=1;
	}
	else if (key == GLUT_KEY_RIGHT) 
	{	
		if(durl!=1)
			durl=2;
	} 
	else if (key == GLUT_KEY_UP) 
	{	
		if(durl!=4)										
			durl=3;
        
	}
	else if (key == GLUT_KEY_DOWN)    
	{
		if(durl!=3)
			durl=4;	
	}

     glutPostRedisplay();
}
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	menu=0;
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(speed / FPS, Timer, 0);
}
void Timer2(int m) // timer func for food
{	
	for(i=0;i<5;i++)
	{
		fdx=(rand()%60)*10;
		fdy=(rand()%60)*10;
		food[i][0]=fdx;
		food[i][1]=fdy;
	}

	glutPostRedisplay();
	glutTimerFunc(75000.0/ FPS, Timer2,0);
}
void Timer3(int m) // timer func for hurdle
{
	for(i=0;i<5;i++)
	{
		hdl_x=(rand()%60)*10;
		hdl_y=(rand()%60)*10;
		hdl1_x=(rand()%60)*10;
		hdl1_y=(rand()%60)*10;
	}

	glutPostRedisplay();
 	glutTimerFunc(150000.0/ FPS, Timer3,0);
}
void Timer4(int m) // timer func for power food
{
	p_x=(rand()%60)*10;
	p_y=(rand()%60)*10;
	glutPostRedisplay();
    	glutTimerFunc(75000.0/ FPS, Timer4,0);
}

/*
 * our gateway main function
 * */

int main(int argc, char*argv[]) {
    	int width = 650, height = 720; // i have set my window size to be 800 x 600
    	InitRandomizer(); // seed the random number generator...
    	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    	glutInitWindowPosition(50, 50); // set the initial position of our window
    	glutInitWindowSize(width, height); // set the size of our window
    	glutCreateWindow("PF's Snake Game"); // set the title of our game window
    	SetCanvasSize(width, height); // set the number of pixels...
// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
  	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.    
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    	glutTimerFunc(5.0 / FPS, Timer, 0);
	glutTimerFunc(5.0 / FPS, Timer2 ,0);
	glutTimerFunc(5.0 / FPS, Timer3 ,0);
	glutTimerFunc(5.0 / FPS, Timer4 ,0);
// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

