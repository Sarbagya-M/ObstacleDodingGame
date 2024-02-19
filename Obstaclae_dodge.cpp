#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<time.h>



void drawCar(int ,int);
void removeCar(int, int);
void drawObstacle(int, int);
void removeObstacle(int, int);





int xPos, yPos, xPosObs, yPosObs;
int height = 22, width = 15, noOfObstacles = 0;
int main()
{
    int gd = DETECT, gm;
    char input, replay,scoreCh[20];
	//label to restart game
	int highScore=0;
	start:
	yPosObs = 15;
	int rightBoundary =176, leftBoundary=100, bottom = 400, carLane=1, randomLane, created =0, speed= 3,score=0;
    //initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    initgraph(&gd, &gm, (char*)"");
	
	xPos=138;
	yPos= bottom - height;

	//draws lanes
	line(leftBoundary - (width+4),0,leftBoundary - (width + 4),bottom);
	line( leftBoundary +width + 4,0,leftBoundary +width + 4, bottom);
	line(leftBoundary + 57,0,leftBoundary + 57, bottom);
	line(rightBoundary + width + 4,0,rightBoundary + width + 4, bottom);

	//draws car at startup
	drawCar(xPos, yPos);
	
	input = 75;

	//to initialize with random seed
	srand (time(NULL)); 
	//--------------------while as update function------------------------------
	while(1)
	{	
		//kbhit detects key hit
		if(_kbhit())
		{
			//saves whichever key was detected by kbhit
			input = _getch();

			switch (input)
			{
				//left button
				case 75:
					//removes previous car before updating 
					removeCar(xPos,yPos);
					xPos -= 38;
					carLane--;
					break;
				//right button
				case 77:
					removeCar(xPos,yPos);
					xPos += 38;
					carLane++;
					break;
				
				default:
					break;
			}
		
		}
		

		// to limit x position and carLane value
		if(xPos>rightBoundary)
		{
			xPos = rightBoundary;	
			carLane = 2;
		}
			

		else if (xPos<leftBoundary)
		{
			xPos = leftBoundary;
			carLane = 0;
		}
			
		//updates car
		drawCar(xPos, yPos);


		//creates new obstacle after dodging
		if(!created)
		{
			//random no. 0,1,2
			randomLane = rand()%3;
			//object has been created
			created = 1;
		}
			
		
		
		switch (randomLane)
		{
		case 0:
			
			xPosObs = 100;
			removeObstacle(xPosObs,yPosObs-speed);
			randomLane = 0;
			break;
		case 1:
			xPosObs = 138;
			removeObstacle(xPosObs,yPosObs-speed);
			randomLane = 1;
			break;

		case 2:
			xPosObs = 176;
			removeObstacle(xPosObs,yPosObs-speed);
			randomLane = 2;
			break;
		
		default:
			break;
		}
		
		//Obstacle reaches car
		if(yPosObs>338)
		{
			//couldn't dodge
			if(randomLane==carLane)
			{
				drawObstacle(xPosObs,yPosObs);
				settextstyle(3, 0, 5);
                outtextxy(getmaxx() / 2 - 150, getmaxy() / 2, "Game Over");
				settextstyle(3, 0, 2);
				outtextxy(getmaxx() / 2 - 170, getmaxy() / 2 + 50, "Press 'space' to replay or 'Esc' to exit");
				re:
				replay = _getch();
				// player replayed
				if(replay == 32)
				{
					cleardevice();
					created = 0;
					if(score > highScore)
						highScore = score;
					goto start;
				}
				// player exited
				else if(replay == 27)
				{
					goto end;
				}
				//wrong input
				else
				{
					goto re;
				}
				
			}
			//player dodges
			else
			{
				created = 0;
				yPosObs = 15;
				++score;
				if(score%3==0)
				speed++;
				//printf("____________\n");
			}
		}
		//Obstacles hasn't reach car
		else
		{	
			drawObstacle(xPosObs,yPosObs);
			
			yPosObs+=speed;
		}

		
		
	
		//printf("%d,%d,%d,%d\n",carLane, randomLane, yPosObs,score);
		settextstyle(3, 0, 3);
		sprintf(scoreCh,"High Score : %d",highScore);
        outtextxy(80,430,scoreCh);
		sprintf(scoreCh,"Score : %d",score);
        outtextxy(220,430,scoreCh);
		delay(5);

	}
	

	
	
	
	end:
     
	
    closegraph();
	
    return 0;
 }


//draws car
void drawCar(int xpos ,int ypos)
{
	
	rectangle(xpos - width, ypos - height, xpos + width, ypos + height);
	
}


//removes car
void removeCar(int xpos ,int ypos)
{
	
	setcolor(BLACK);
	rectangle(xpos - width, ypos - height, xpos + width, ypos + height);
	setcolor(WHITE);
}



//draws obstacle
void drawObstacle(int xpos ,int ypos)
{
	
	rectangle(xpos - width, ypos - width, xpos + width, ypos + width);
}


//removes obstacle
void removeObstacle(int xpos ,int ypos)
{
	
	setcolor(BLACK);
	rectangle(xpos - width, ypos - width, xpos + width, ypos + width);
	setcolor(WHITE);
}