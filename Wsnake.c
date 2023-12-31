// Creator: 0xa0
// Date: 22/11/2023 Montpellier, France
// Description:
// This is a program that creates a DVD screensaver logo in the terminal that will bounce off the sides
// of the terminal. It is written in C and it seems like the first of its kind. It is a fun project.
// email: sarah [at] 0xa0 [dot] dev
// github: 0xA00






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

//get the length of the terminal
int getTermLength(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

//get the width of the terminal
int getTermWidth(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void ctrlC(int sig){
	printf("\033[?25h");
	system("clear");
	exit(0);
}

void printmatricewithcoords(char* matrix[7][15], int x, int y){
	int termLength = getTermLength();
	int termWidth = getTermWidth();
	
	y = y+1;
	x = x+1;


	for(int i = 0; i < 7; i++){
		printf("\033[%d;%dH", y+i, x);
		for(int j = 0; j < 15; j++){
			printf("%s", matrix[i][j]);
		}
		printf("\n");
	}
	
}

int randomiser(){
	//choose between -1 and 1 and not any other number
	
	int random = rand() % 2;
	if(random == 0){
		return -1;
	}
	else{
		return 1;
	}
}

char *randomColor(){
	int random = rand() % 7;
	switch(random){
		case 0:
			return "\e[0;31m ";
		case 1:
			return "\e[0;32m ";
		case 2:
			return "\e[0;33m ";
		case 3:
			return "\e[0;34m ";
		case 4:
			return "\e[0;35m ";
		case 5:
			return "\e[0;36m ";
		case 6:
			return "\e[0;37m ";
		default:
			return "\e[0;37m ";
	}
}



int main(int argc, char *argv[]){
	srand(time(NULL));
	char* matrix[7][15] = {
		{"\e[0;31m "," ","█","█"," "," ","█"," ","█"," ","█","█"," "," "," "},
		{" "," ","█"," ","█"," ","█"," ","█"," ","█"," ","█"," "," "},
		{" "," ","█"," ","█"," ","█"," ","█"," ","█"," ","█"," "," "},
		{" "," ","█","█"," "," "," ","█"," "," ","█","█"," "," "," "},
		{" ","█","█","█","█","█","█","█","█","█","█","█","█","█"," "},
		{"█","█","█"," "," "," "," "," "," "," "," "," ","█","█","█"},
		{" ","█","█","█","█","█","█","█","█","█","█","█","█","█","\e[0m "}		
		
	};
	
	int updown = randomiser();
	int leftright = randomiser();
	//choose coords inside of the terminal but quite near the middle
	int x = getTermWidth()/2;
	int y = getTermLength()/2;

	signal(SIGINT, ctrlC);

	 printf("\033[?25l");
	while(1){
		//clear the screen
		system("clear");
		//move the cursor
		x += leftright;
		y += updown;
		//check if the cursor is at the edge of the screen
		if(x == 0 || x+15 == getTermWidth()){
			leftright = -leftright;
			char *newColor = randomColor();
			while(newColor == matrix[0][0]){
				newColor = randomColor();
			}
			matrix[0][0] = newColor;


		}
		if(y == 0 || y+8 == getTermLength()){
			updown = -updown;
                        matrix[0][0] = randomColor();
			char *newColor = randomColor();                                                                                                                                       
                        while(newColor == matrix[0][0]){                                                                                                                                      
                                newColor = randomColor();
                        }                                                                                                                                                                     
                        matrix[0][0] = newColor;


		}
		//print the matrix
		printmatricewithcoords(matrix, x, y);
		//wait 0.1 seconds
		usleep(100000);
	}

	//exit
	return 0;
	

}




