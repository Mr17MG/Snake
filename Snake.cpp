#include <iostream.h>
#include <conio.h>
#include <windows.h>
#include <fstream.h>
void gotoxy(int x,int y)
{
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );
    if (INVALID_HANDLE_VALUE != hConsole)
    {
        COORD pos = {x, y};
        SetConsoleCursorPosition( hConsole, pos );
    }
}

int game[10][20]={0},p,T,b,snake[2][100]={-1},xnew,ynew,k,m,s,flaq=1,score[10]={0},h=0;

char Aski (int a)
{
 return (char (a));
}

void Init (int a,int b,int game[][20])
{
	srand(time(0));
	int x,y;
	for(int i=0;i<b;i++)
	{
		if(a==-1)
		{
		x=rand()%9+1-1;
		y=rand()%19+1-1;
		}
		else {
		      x=rand()%10;
		      y=rand()%20;
             } 
		if(game[x][y]!=0)
		 i--;
		 else game[x][y]=a;
	}
}

void Print()
{
	for(int i=0;i<10;i++)
	{
		gotoxy(10,5+i);
		for(int j=0;j<20;j++)
		{
			if (game[i][j]==1)
			 cout<<"*";
		    else if(game[i][j]==-1)
			 cout<<"#";
			 else if(game[i][j]==2)
			  cout<<Aski(248);
			 else if(game[i][j]==0)
			   cout <<" "; 
		} 
		cout<<endl;
	}
}

void Box(int a,int x,int y,int r,int b,int n)
{
	if(a==1)
	{
		gotoxy(x,y);
		cout<<Aski(r);
	}
	else if(a==0)
	{
		for(int i=0;i<n;i++)
		{
			if(b==0)
			 gotoxy(x,y+i);
			else if(b==1)
			 gotoxy(x+i,y); 
			cout<<Aski(r);
		}
	}
}

void BOX()
{
    Box(1,9,4,201,0,0);
    Box(1,30,4,187,0,0);
    Box(1,9,15,200,0,0);
    Box(1,30,15,188,0,0);
    Box(0,10,4,205,1,20);
    Box(0,9,5,186,0,10);
    Box(0,30,5,186,0,10);
    Box(0,10,15,205,1,20);
}
int MODE()
{
	char q;
	cout<<"press C for Classic mode , M for Modern mode:";
	q=getch();
	if(q=='c' || q=='C')
	 {cout<<"Classic"<<endl;
	  return 0;}
    else if(q=='m' || q=='M')
	 {
	  cout<<"Modern"<<endl;
	  Sleep(500);
	  system("cls");
	  cout<<"Press H for Hard,N for Normal,E for Easy:";
	  q=getch();
	  if(q=='H;'||q=='h')
	     return 1;
      else if(q=='N'||q=='n')
	     return 2;
	  else if(q=='E'|| q=='e')
		 return 3;
	}
	 else 
	   {for(int y=0;y<55;y++)
        cout<<"\b";return -1;
       }
}

void MODE2()
{
	while(m!=-1)
	{
	 m=MODE();
	 system("cls");
 	 gotoxy(25,1);
	     if(m==0)
	      {
      	   cout<<"\"Classic Mode\"";
      	   h=0;
		   Init(1,1,game);
		   break;
	      }
	     else if(m==1)
	      {
	      	cout<<"\"Modern Mode\""<<"(HARD)";
	      	h=1;
		   Init(1,1,game);
	       Init(-1,30,game);
	       break;
	      }
	     else if(m==2)
	 	{
	 		cout<<"\"Modern Mode\""<<"(Normal)";
	 		h=1;
	 		Init(1,1,game);
	 		Init(-1,20,game);
	 		break;
	 	}  
	  	else if(m==3)
	  	{
	  		cout<<"\"Modern Mode\""<<"(Easy)";
	  		h=1;
			Init(1,1,game);
	  		Init(-1,10,game);
	  		break;
	  	}
	  	else
	  	{
	  		gotoxy(0,0);
	  		MODE();
	  	}
	  	 
	}
  }

void Moving()
{
	game[snake[0][0]][snake[1][0]]=0;
 	for(int i=0;i<k;i++)
 	 {
 	  snake[0][i]=snake[0][i+1];
 	  snake[1][i]=snake[1][i+1];
	 }
	 snake[0][k]=xnew;
	 snake[1][k]=ynew;
	 game[xnew][ynew]=2;
}

void Exit()
{char c;
	gotoxy(40,12);
                cout<<"Do you want To exit:Y/N/R";
                c=getch();
                if(c=='y'||c=='Y')
                 exit(0);
                 else if(c=='N'||c=='n')
                 { 
				   gotoxy(40,12);
                   cout<<"                               ";
				  }
				  else if(c=='R' || c=='r')
				   flaq=-1;
                 else Exit();
}
void Trepan()
{
	char c=getch();
	if(c==27)
	 Exit();
			if(c==-32 || c==00)
			{
			 c=getch();
			 switch (c)
		      {
			 	case 72: if(p!=4)
				          p=3;
						  break;
				case 80: if(p!=3)
				         p=4;
						 break;
				case 77: if(p!=2)
				         p=1;
						 break;
				case 75: if(p!=1)
				         p=2;
				         break;
			  }
			}
}


void Score()
{
 ifstream i;
 ofstream o;
 int n,v=1,x;
 o.open("snake.txt",ios::app);
 o<<endl<<T;
 i.open("snake.txt",ios::in);
 gotoxy(28,5);
 cout<<"\"Your Last Score\""<<endl;
 while(!i.eof())
  { 
   i>>x;
   if(i.good())
    {
   	 gotoxy(28,5+v);
     cout<<v<<":"<<x<<endl;
    }
    v++;
   }
         
 o.close();
}

int Lose()
{
	system("cls");
        flaq=-1;
	gotoxy(30,1);
	cout<<"\"Game over\"";
	Beep(500,500);
	gotoxy(29,2);
	cout<<"Your score:"<<T<<endl;
	Score();
	Beep(400,500);
	gotoxy(45,11);
	cout<<"Do You Want To Play Again:Y/N";
	Beep(300,500);
	char c=getch();
	if(c=='y' || c=='Y');
	else if (c=='n' || c=='N')
	 exit(0);
	 else Lose();
}

void Eating()
 {
 	k++;
 	T+=10;
 	if(k%6==0)
 	 s-=50;
 	snake[0][k]=xnew;
 	snake[1][k]=ynew;
 	game[xnew][ynew]=2;
 	Init(1,1,game);
 }


void Move()
{
	while(flaq!=-1)
	{
	 Sleep(s);
	 T++;
     if(kbhit())
      {
     	Trepan(); 
      }

	switch(p)
	{
		case 1:xnew=snake[0][k];
		       if(h!=1)
			     ynew=(snake[1][k]+1)%20;
			      else ynew=snake[1][k]+1;
			     if(h==1 && ynew==20)
				  {Lose();flaq=-1;} 
			    break;
		case 2:xnew=snake[0][k];
		      if(h==0)
			   if(ynew==0)
			   ynew=19;
			   else ynew=(snake[1][k]-1)%20;
			   if(h==1)
			    ynew=snake[1][k]-1;
			   if(h==1 && ynew==-1)
				  {Lose();flaq=-1;}
			   break;
		case 3:if(h==0)
		        if(xnew==0)
		         xnew=9;
		       else xnew=(snake[0][k]-1)%10;
		       if(h==1)
		        xnew=snake[0][k]-1;
	           if(h==1 && xnew==-1)
				  {Lose();flaq=-1;}
			   ynew=snake[1][k];
			   break;
		case 4:if(h==0)
		        xnew=(snake[0][k]+1)%10;
		        else if(h==1) 
                      xnew=snake[0][k]+1;
		        if(h==1 && xnew==10)
				  {Lose();flaq=-1;}	 
		       ynew=snake[1][k];
			   break;	         
	}
	switch(game[xnew][ynew])
	{
		case 2:Lose();
		       flaq=-1;
		       break;
		case -1:Lose();
		        flaq=-1;
		        break;
        case 0:Moving();
               break;
        case 1:Eating();
               break;
		
	}
	if(flaq==-1)
	 break;
	gotoxy(42,10);
	cout<<T;
	 Print();	
    }
}

main()
{
	while(1)
	{
	 p=1,T=0,k=2,m,s=500;
	 system("cls");
	 for(int i=0;i<10;i++)
	  for(int j=0;j<20;j++)
	   game[i][j]=0;
	  for(int i=0;i<2;i++)
	  for(int j=0;j<100;j++)
	  snake[i][j]=-1; 
	 for(int i=0;i<3;i++)
	  game[9][i]=2;
	  
     snake[0][0]=9;snake[1][0]=0;snake[0][1]=9;snake[1][1]=1;
	 snake[0][2]=9;snake[1][2]=2;flaq=0; 
      system("color 17");
      MODE2();
      BOX();
	  Print();
	  gotoxy(36,10);
	  cout<<"Point:"<<T;
	  gotoxy(36,15);
	  cout<<"Use Up,Down,Right and lef key";
	  if(h==1)
	   {
	   	gotoxy(36,16);
	   	cout<<"\"\"\"\"\"collision with the wall is end of the game\"\"\"\"\"";
       }
      game[9][3]=0;
	  Move();
	 }
}