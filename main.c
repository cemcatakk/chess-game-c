#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LEN 8
typedef struct Point{
	char piece[3];
}point;
point board[LEN][LEN];
void printBoard(){
	int i,j;
	char ch='A';
	printf("Chess Board\n");
	for(i=LEN-1;i>=0;i--){
			printf("%-5d",i+1);
		for(j=0;j<LEN;j++){
			printf("%-5s",board[i][j].piece);
		}
		printf("\n");
	}
	printf("\n%-5s"," ");
	for(i=0;i<LEN;i++){
		printf("%-5c",ch+i);
	}
	printf("\n");
}
int ctl(char ch){
	return ch-64;
}
void Move(int cx,int cy,int tx,int ty){
	cx--;cy--;tx--;ty--;
	board[tx][ty].piece[0]=board[cx][cy].piece[0];
	board[tx][ty].piece[1]=board[cx][cy].piece[1];
	board[cx][cy].piece[0]='0';
	board[cx][cy].piece[1]='\0';
}
int canMoveP(int x,int y,int tx,int ty,int dir){
	x--;y--;tx--;ty--;
	if(x==tx&&y==ty)return -1;
	if((board[tx][ty].piece[0]==board[x][y].piece[0]))return -1;
	if((y==ty)&&(x-tx==dir)&&(board[tx][ty].piece[0]!=board[x][y].piece[0])&&(board[tx][ty].piece[0]!='0'))return -1;
	if((x-tx==dir)&&(y==ty-1||y==ty+1)&&(board[tx][ty].piece[0]!=board[x][y].piece[0])&&(board[tx][ty].piece[0]!='0'))return 1;
	if((x-tx==dir)&&y==ty)return 1;
	return -1;
}

int canMoveB(int x,int y,int tx,int ty){
	x--;y--;tx--;ty--; int i,j;
	if(x==tx&&y==ty)return -1;
	if((board[tx][ty].piece[0]==board[x][y].piece[0]))return -1;
	if(x>tx&&y>ty){
		for(i=x-1,j=y-1;i>tx&&j>ty;i--,j--){
			if(board[i][j].piece[0]!='0')return -1;
		}
	}
	else if(x<tx&&y>ty){
		for(i=x+1,j=y-1;i<tx&&j>ty;i++,j--){
			if(board[i][j].piece[0]!='0')return -1;
		}
	}
	else if(x<tx&&y<ty){
		for(i=x+1,j=y+1;i<tx&&j<ty;i++,j++){
			if(board[i][j].piece[0]!='0')return -1;
		}
	}
	else if(x>tx&&y<ty){
		for(i=x-1,j=y+1;i>tx&&j<ty;i--,j++){
			if(board[i][j].piece[0]!='0')return -1;
		}
	}
	if((abs(y-ty)==abs(x-tx))&&(board[tx][ty].piece[0]!=board[x][y].piece[0]))return 1;
	if((abs(y-ty)==abs(x-tx))&&(board[tx][ty].piece[0]!=board[x][y].piece[0])&&(board[tx][ty].piece[0]!='0'))return 1;
	return -1;
}

int canMoveG(int x,int y,int tx,int ty){
	x--;y--;tx--;ty--;
	int checkX=x-tx;
	int checkY=y-ty;
	if(abs(checkX)>1||abs(checkY)>1)return -1;
	if(x==tx&&y==ty)return -1;
	if((board[tx][ty].piece[0]==board[x][y].piece[0]))return -1;
	if((board[tx][ty].piece[0]!=board[x][y].piece[0]))return 1;
	if((board[tx][ty].piece[0]!=board[x][y].piece[0])&&(board[tx][ty].piece[0]!='0'))return 1;
	return -1;
}

int canMoveR(int x,int y,int tx,int ty){
	x--;y--;tx--;ty--; int i;
	if(x==tx&&y==ty)return -1;
	if(x!=tx&&y!=ty)return -1;
	if(x>tx&&y==ty){
		for(i=x-1;i>tx;i--){
			if(board[i][y].piece[0]!='0')return -1;
		}
	}
	else if(x<tx&&y==ty){
		for(i=x+1;i<tx;i++){
			if(board[i][y].piece[0]!='0')return -1;
		}
	}
	else if(x==tx&&y>ty){
		for(i=y-1;i>ty;i--){
			if(board[x][i].piece[0]!='0')return -1;
		}
	}
	else{
		for(i=y+1;i<ty;i++){
			if(board[x][i].piece[0]!='0')return -1;
		}
	}
	if((board[tx][ty].piece[0]!=board[x][y].piece[0]))return 1;
	if((board[tx][ty].piece[0]==board[x][y].piece[0]))return -1;
	return -1;
}

int canMoveQ(int x,int y,int tx,int ty){
	if(canMoveR(x,y,tx,ty)==1||canMoveB(x,y,tx,ty)==1||canMoveG(x,y,tx,ty)==1)return 1;
	return -1;
}

int canMoveK(int x,int y,int tx,int ty){
	x--;y--;tx--;ty--;
	if(x==tx&&y==ty)return -1;
	if((board[tx][ty].piece[0]==board[x][y].piece[0]))return -1;
	if((x+2==tx&&y+1==ty)||(x+2==tx&&y-1==ty)||(x-2==tx&&y+1==ty)||(x-2==tx&&y-1==ty))return 1;
	if((x+1==tx&&y+2==ty)||(x+1==tx&&y-2==ty)||(x-1==tx&&y+2==ty)||(x-1==tx&&y-2==ty))return 1;
	return -1;
}
int isValidChoice(int x,int y,char player){
	x--;y--;
	if(player!=board[x][y].piece[0])return -1;
	if(x<0||x>LEN-1)return -1;
	if(y<0||y>LEN-1)return -1;
	return 1;
}
int gameOver(){
	int i,j,check=0;
	for(i=0;i<LEN;i++){
		for(j=0;j<LEN;j++){
			if(board[i][j].piece[1]=='G')check++;
		}
	}
	if(check==2)return-1;
	else return 1;
}
int main(int argc, char *argv[]) {
	int i,j;
	int x,y,tx,ty;
	int dir=-1;
	char selectedPiece,turn='W';
	int canMove=0;
	board[0][0].piece[0]='W';board[0][0].piece[1]='R';
	board[0][1].piece[0]='W';board[0][1].piece[1]='K';
	board[0][2].piece[0]='W';board[0][2].piece[1]='B';
	board[0][3].piece[0]='W';board[0][3].piece[1]='Q';
	board[0][4].piece[0]='W';board[0][4].piece[1]='G';
	board[0][5].piece[0]='W';board[0][5].piece[1]='B';
	board[0][6].piece[0]='W';board[0][6].piece[1]='K';
	board[0][7].piece[0]='W';board[0][7].piece[1]='R';
	
	board[1][0].piece[0]='W';board[1][0].piece[1]='P';
	board[1][1].piece[0]='W';board[1][1].piece[1]='P';
	board[1][2].piece[0]='W';board[1][2].piece[1]='P';
	board[1][3].piece[0]='W';board[1][3].piece[1]='P';
	board[1][4].piece[0]='W';board[1][4].piece[1]='P';
	board[1][5].piece[0]='W';board[1][5].piece[1]='P';
	board[1][6].piece[0]='W';board[1][6].piece[1]='P';
	board[1][7].piece[0]='W';board[1][7].piece[1]='P';
	for(i=2;i<6;i++){
		for(j=0;j<LEN;j++){
			board[i][j].piece[0]='0';
			board[i][j].piece[1]='\0';
		}
	}
	
	board[7][0].piece[0]='B';board[7][0].piece[1]='R';
	board[7][1].piece[0]='B';board[7][1].piece[1]='K';
	board[7][2].piece[0]='B';board[7][2].piece[1]='B';
	board[7][3].piece[0]='B';board[7][3].piece[1]='Q';
	board[7][4].piece[0]='B';board[7][4].piece[1]='G';
	board[7][5].piece[0]='B';board[7][5].piece[1]='B';
	board[7][6].piece[0]='B';board[7][6].piece[1]='K';
	board[7][7].piece[0]='B';board[7][7].piece[1]='R';
	
	board[6][0].piece[0]='B';board[6][0].piece[1]='P';
	board[6][1].piece[0]='B';board[6][1].piece[1]='P';
	board[6][2].piece[0]='B';board[6][2].piece[1]='P';
	board[6][3].piece[0]='B';board[6][3].piece[1]='P';
	board[6][4].piece[0]='B';board[6][4].piece[1]='P';
	board[6][5].piece[0]='B';board[6][5].piece[1]='P';
	board[6][6].piece[0]='B';board[6][6].piece[1]='P';
	board[6][7].piece[0]='B';board[6][7].piece[1]='P';
	for(i=0;i<LEN;i++){
		for(j=0;j<LEN;j++){
			board[i][j].piece[2]='\0';
		}
	}
	while(1){
		printBoard(board);
		if(turn=='W'){
			printf("White's Turn!\n");
			dir=-1;
		}
		else{
			printf("Black's Turn!\n");
			dir=1;
		}
		while(1){
			do{
			printf("Select a piece to move:");
			scanf("%d%c",&x,&y);
			y=ctl(y);
		}while(isValidChoice(x,y,turn)==-1);
		selectedPiece = board[x-1][y-1].piece[1];
		printf("Playing %c from %d %c!\n",selectedPiece,x,y+64);
		do{
			printf("Enter target to move(0 to back):");
			scanf("%d%c",&tx,&ty);
			ty=ctl(ty);
			switch(selectedPiece){
				case 'P':
					canMove=canMoveP(x,y,tx,ty,dir);
					break;
				case 'B':
					canMove=canMoveB(x,y,tx,ty);
					break;
				case 'K':
					canMove=canMoveK(x,y,tx,ty);
					break;
				case 'R':
					canMove=canMoveR(x,y,tx,ty);
					break;
				case 'Q':
					canMove=canMoveQ(x,y,tx,ty);
					break;
				case 'G':
					canMove=canMoveG(x,y,tx,ty);
					break;
				default:
					canMove=-1;
					break;
			}
		    if(tx==0)break;
			if(canMove==-1){
				printf("You can't move piece from %d%c to %d%c\n",x,y+64,tx,ty+64);
			}
			else if(canMove==1){
				printf("Moved piece from %d%c to %d%c\n",x,y+64,tx,ty+64);
			}
		}while(canMove!=1);
		    if(tx!=0)break;
		}
		Move(x,y,tx,ty);
		if(gameOver()==1){
			printf("Player %c has won!\nGame Over.\n",turn);
			break;
		}
		if(turn=='W'){
			turn='B';
		}
		else{
			turn ='W';
		}
	}
	
	return 0;
}
