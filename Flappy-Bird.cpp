#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 110
#define SCREEN_HEIGHT 28
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
using namespace std;
//		cout<<"____";
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_','_','>' };
					
int birdPos = 6;
int score = 0;

void TextColor(int x)
{
    HANDLE mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau,x);
}

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder(){ 
	TextColor(11);
	for(int i=0; i<=SCREEN_WIDTH; i++){
		gotoxy(i,0); cout << static_cast<char>(205);
		gotoxy(i,SCREEN_HEIGHT); cout << static_cast<char>(205);
	}
	
	for(int i=1; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout << static_cast<char>(179) << static_cast<char>(179);
		gotoxy(SCREEN_WIDTH,i); cout << static_cast<char>(179) << static_cast<char>(179);
	}
	for(int i=1; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout << static_cast<char>(179) << static_cast<char>(179);
	}
}
void genPipe(int ind){
	gapPos[ind] = 3 + rand()%14; 
}
void drawPipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout << static_cast<char>(219) << static_cast<char>(219) << static_cast<char>(219) << static_cast<char>(219); 
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout << static_cast<char>(219) << static_cast<char>(219) << static_cast<char>(219) << static_cast<char>(219); 
		}
	} 
}
void erasePipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"    "; 
		}
		for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"    "; 
		}
	}
}

void drawBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<bird[i][j];
		}
	}
}
void eraseBird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<" ";
		}
	}
}

int collision(){
	if( pipePos[0] >= 61  ){
		if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){
//			cout<< " HIT ";
//			getch();
			return 1;
		}
	}
	return 0;
}
void debug(){
//	gotoxy(SCREEN_WIDTH + 3, 4); cout<<"Pipe Pos: "<<pipePos[0];
	
}
void gameover(){
	system("cls");
	TextColor(2);
	gotoxy(50,10); cout <<"--------------------------" << endl;
	gotoxy(50,12); cout <<"-------- GAME OVER -------" << endl;
	gotoxy(50,14); cout <<"--------------------------" << endl;
	gotoxy(47,18); cout <<"Nhan phim bat ki de quay lai menu";
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 15, 8);cout<<"Diem: "<<score<<endl;
}

void help(){
	
	system("cls");
		for(int i=0;i<SCREEN_WIDTH-40;i++){
		gotoxy(i+20,2);   cout << static_cast<char>(205);
		}
		for(int i=0;i<SCREEN_WIDTH-40;i++){
		gotoxy(i+20,15);  cout << static_cast<char>(205);
		}
		for(int i=3;i<SCREEN_HEIGHT-13;i++){
		gotoxy(20,i); cout << static_cast<char>(179) << static_cast<char>(179);
		}
		for(int i=3;i<SCREEN_HEIGHT-13;i++){
		gotoxy(88,i); cout << static_cast<char>(179) << static_cast<char>(179);	
		}
	gotoxy(50,4);  TextColor(160); cout <<"HEPL";	 			 TextColor(3);
	gotoxy(35,5);  cout <<"- Nhan phim cach de lam cho con chim bay";   TextColor(3);
	gotoxy(35,6);  cout <<"- Nhan phim bat ki de quay lai menu";	 TextColor(3); 
	getch();
}

void play(){
	
	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1; 
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;
	
	system("cls"); 
	drawBorder();
	genPipe(0);
	updateScore();
	gotoxy(WIN_WIDTH + 6, 2);   TextColor(12);  cout<<"VO HOA THUAN - CNTT CT07 - KMP"; 
	gotoxy(WIN_WIDTH + 13, 4);  TextColor(12);  cout<<"FLAPPY BIRD " << static_cast<char>(2);
	gotoxy(WIN_WIDTH + 14, 6);  TextColor(11);  cout<<"----------";
	gotoxy(WIN_WIDTH + 14, 10); TextColor(11);  cout<<"----------";
	gotoxy(WIN_WIDTH + 15, 16); TextColor(11);  cout<<"Dieu khien";
	gotoxy(WIN_WIDTH + 14, 17); TextColor(11);  cout<<"------------";
	gotoxy(WIN_WIDTH + 12, 18); TextColor(11);  cout<<"Phim cach = nhay";
	
	gotoxy(10, 5);cout<<"Nhan dau cach de bat dau";
	getch();
	gotoxy(10, 5);cout<<"                        ";
	while(1){
		 
		if(kbhit()){
			char ch = getch();
			if(ch==32){
				if( birdPos > 3 )
					birdPos-=3;
			} 
			if(ch==27){
				break;
			}
		}
		
		drawBird();
		drawPipe(0);
		drawPipe(1);
		debug();
		if( collision() == 1 ){
			gameover();
			return;
		}
		Sleep(100);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;
		
		if( birdPos > SCREEN_HEIGHT - 2 ){
			gameover();
			return;
		}
		
		if( pipeFlag[0] == 1 )
			pipePos[0] += 2;
		
		if( pipeFlag[1] == 1 )
			pipePos[1] += 2;
		
		if( pipePos[0] >= 40 && pipePos[0] < 42 ){
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if( pipePos[0] > 68 ){
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}
		
	}
	 
}
void Vien_out(){ 
	TextColor(11);
	for(int i=0; i<=SCREEN_WIDTH; i++){
		gotoxy(i,0); cout << static_cast<char>(205);
		gotoxy(i,SCREEN_HEIGHT); cout << static_cast<char>(205);
		
	}
	for(int i=0;i<SCREEN_WIDTH;i++){
		gotoxy(i,20); cout << static_cast<char>(205);
	
	}
	for(int i=1; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout << static_cast<char>(179) << static_cast<char>(179);
		gotoxy(SCREEN_WIDTH,i); cout << static_cast<char>(179) << static_cast<char>(179);
		
	}

}
void about(){
	system("cls");
	gotoxy(50,8);   TextColor(202); cout << " PROFILE ";  
	gotoxy(38, 10); TextColor(11);  cout << "Name:";       gotoxy(50, 10); TextColor(2); cout << "VO HOA THUAN";
	gotoxy(38, 11); TextColor(11);  cout << "Birthday:";   gotoxy(50, 11); TextColor(2); cout << "03/08/2004";
	gotoxy(38, 12); TextColor(11);  cout << "Fcebook:";    gotoxy(50, 12); TextColor(2); cout << "https://www.facebook.com/vht.got";
	gotoxy(38, 13); TextColor(11);  cout << "Gmail:";      gotoxy(50, 13); TextColor(2); cout << "vohoathuan.82004@gmail.com";
	gotoxy(38, 14); TextColor(11);  cout << "Address:";    gotoxy(50, 14); TextColor(2); cout << "Chau Thanh - Tien Giang";
	gotoxy(38, 15); TextColor(11);  cout << "Schools:";    gotoxy(50, 15); TextColor(2); cout << "CNTT & KMP Ho Chi Minh";
	gotoxy(38, 16); TextColor(11);  cout << "Occupation:"; gotoxy(50, 16); TextColor(2); cout << "Sinh Vien";
	gotoxy(38, 17); TextColor(11);  cout << "GitHub:";     gotoxy(50, 17); TextColor(2); cout << "https://github.com/Vo-Hoa-Thuan";
	gotoxy(38, 18); TextColor(11);  cout << "Hobby:";      gotoxy(50, 18); TextColor(2); cout << "Play game";
	gotoxy(38, 19); TextColor(6);   cout << "Nhan phim bat ki de quay lai menu " << static_cast<char>(2);
	getch();
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	
//	play();
	
	do{
		system("cls");
		Vien_out();
		gotoxy(46,4);  TextColor(160); cout << " GAME FLAPPY BIRD " << static_cast<char>(2); TextColor(1);
		gotoxy(48,6);  TextColor(202); cout <<" 1. PLAY GAME"; 		 TextColor(3);
		gotoxy(48,7);  cout <<" 2. HELP"; 	    TextColor(3);
		gotoxy(48,8);  cout <<" 3. ABOUT";	    TextColor(3); 	 
		gotoxy(48,9);  cout <<" 4. EXIT";       TextColor(6);
		gotoxy(48,10); cout <<"Moi Ban Chon: ";
		 cout <<"\n";
    TextColor(2);
    gotoxy(25,22); cout <<"$$$$$$$$$$$  $$$   $$$  $$$   $$$   $$$$$$$$   $$$$   $$$\n"; Sleep(50);
    gotoxy(25,23); cout <<"$$$$$$$$$$$  $$$   $$$  $$$   $$$   $$$$$$$$   $$$$$  $$$\n"; Sleep(50); TextColor(3);
    gotoxy(25,24); cout <<"    $$$      $$$   $$$  $$$   $$$  $$$    $$$  $$$$$$ $$$\n"; Sleep(50);
    gotoxy(25,25); cout <<"    $$$      $$$$$$$$$  $$$   $$$  $$$$$$$$$$  $$$ $$$$$$\n"; Sleep(50); TextColor(4);
    gotoxy(25,26); cout <<"    $$$      $$$   $$$  $$$   $$$  $$$    $$$  $$$  $$$$$\n"; Sleep(50);
    gotoxy(25,27); cout <<"    $$$      $$$   $$$  $$$$$$$$$  $$$    $$$  $$$   $$$$\n";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') help();
		else if( op=='3') about();
		else if( op=='4') exit(0);
		
	}while(1);
	
	return 0;
}
