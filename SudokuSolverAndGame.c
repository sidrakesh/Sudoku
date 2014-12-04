//A 9*9 Sudoku Solver and Game in C

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

//function prototypes
void fillsudo(int arr[][10][10]);
void rowfill(int arr[][10][10]);
void colfill(int arr[][10][10]);
void squarefill(int arr[][10][10]);
void singlesquarefill(int arr[][10][10],int i,int j);
void guesssolve(int arr[][10][10]);
int numfilled(int arr[][10][10]);
int ifimpasse(int arr[][10][10]);
int ifimpassesingsq(int arr[][10][10],int i,int j);
void manualinput(int arr[][10][10]);
void output(int arr[][10][10]);
void randomfill(int arr[][10][10]);
void sudokumode(char mode);
void challenge();
void challengeprob(char level,int arr[][10][10]);
void custom();
void displayGrid(int grid[][9],int a,int b,int newfilled[][9]);
void clearscreen();
void startchallenge(int x[][9],char level);
int score(int cnt,char level);
int ifdone(int a[][9],int b[][9]);
int ifimpassenew(int arr[][9]);
int ifimpassesingsqnew(int arr[][9],int i,int j);
void ClearConsoleToColors(int ForgC, int BackC);

int main()
{
    srand((unsigned int)time(NULL));

    WORD wColor = ((15 & 0x0F) << 4) + (0 & 0x0F);
                   //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                         //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
                      //A return value... indicating how many chars were written
                        //   not used but we need to capture this since it will be
                          //   written anyway (passing NULL causes an access violation).
     DWORD count;

                                   //This is a structure containing all of the console info
                          // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
                     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                              //This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                              //This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }

    printf("\t\t\tWELCOME TO THE GAME OF SUDOKU\n\n");

    char ans,mode,level;
    do{
         printf("\nSelect any of these modes:\n1>Press 'c' for Challenge mode\n2>Press 's' for Solver mode\n");

         do{
         mode=_getch();
         if(!(mode=='c'||mode=='s'))
         printf("Enter valid mode:\n");
         }while(!(mode=='c'||mode=='s'));

         sudokumode(mode);

      printf("\n\nDo you want to try again?(y/n):");
      do{
      ans=_getch();
      }while(!(ans=='y'||ans=='n'||ans=='Y'||ans=='N'));

     }while(ans=='y'||ans=='Y');

    printf("\nThanks for trying.\n");

    Sleep(1500);

    printf("\nCredits :Siddharth Rakesh\n\t 11CS30036");
    Sleep(3000);
    return 0;
}

void fillsudo(int arr[][10][10])
     {int sudodiff,sudonum,sudonumn,i,j,eveniter,count;

     sudonum=0;                             //to be used to detect whether changes are taking place
                                            //in the array or not. if, after cont. processing, it is observed
                                            //that no changes are taking place eventually, the solving procedures
                                            //will stop
     eveniter=1;
     sudonumn=numfilled(arr);
     do{
     if(eveniter%2==0)
     sudonum=sudonumn;

          rowfill(arr);
          colfill(arr);
          squarefill(arr);

     if(eveniter%2==0)
     sudonumn=numfilled(arr);

     eveniter++;
     }while(sudonumn-sudonum!=0);

     if((ifimpasse(arr)==0)&&(numfilled(arr)!=81))
     guesssolve(arr);

     }

int numfilled(int arr[][10][10])  //returns the number of filled cells of the sudoku
{
    int count=0;
    int i,j;

    for(i=1;i<=9;i++)
                     for(j=1;j<=9;j++)
                     if(arr[i][j][0]!=0)
                     count++;

    return count;
}

void rowfill(int arr[][10][10])   //function to fill array row-wise
     {int i,j,k;

     for(i=1;i<=9;i++)                   //part 1:fills the 3rd dimension of elements
                                         //corresponding to the elements which are already in the row
     {                for(j=1;j<=9;j++)
                      {
                                       if(arr[i][j][0]!=0)
                                       {
                                        for(k=1;k<=9;k++)
                                        {
                                        if(arr[i][k][0]==0)
                                        arr[i][k][arr[i][j][0]]=1;
                                        }
                                       }
                      }
     }
     int count,flag;

     for(i=1;i<=9;i++)                      //fills the row with values which are uniquely confined to a
                                            //particular cell
     {
                      for(k=1;k<=9;k++)
                      {count=0;
                      flag=0;

                                       for(j=1;j<=9;j++)
                                       if(arr[i][j][0]==k)
                                       {
                                       flag=1;
                                       break;
                                       }
                      if(flag==1)
                      continue;

                      else{
                                            for(j=1;j<=9;j++)
                                       {
                                       if((arr[i][j][k]==1)||(arr[i][j][0]!=0))
                                       count++;
                                       }
                      if(count==8)
                                       for(j=1;j<=9;j++)
                                       {
                                       if((arr[i][j][k]==0)&&(arr[i][j][0]==0))
                                       arr[i][j][0]=k;
                                       }
                      }
                      }
     }
     }


void colfill(int arr[][10][10])        //function to fill array column-wise
     {int i,j,k;

     for(j=1;j<=9;j++)                 //part 1:fills the 3rd dimension of elements
                                         //corresponding to the elements which are already in the row
     {                for(i=1;i<=9;i++)
                      {
                                       if(arr[i][j][0]!=0)
                                       {
                                       for(k=1;k<=9;k++)
                                       {if(arr[k][j][0]==0)
                                       arr[k][j][arr[i][j][0]]=1;
                                       }
                                       }
                      }
     }
          int count,flag;
     for(j=1;j<=9;j++)                     //fills the row with values which are uniquely confined to a
                                           //particular cell
     {                for(k=1;k<=9;k++)
                      {count=0;
                      flag=0;

                      for(i=1;i<=9;i++)
                      if(arr[i][j][0]==k)
                      {
                      flag=1;
                      break;
                      }

                      if(flag==1)
                      continue;

                      else{                 for(i=1;i<=9;i++)
                                       {
                                       if((arr[i][j][k]==1)||(arr[i][j][0]!=0))
                                       count++;
                                       }
                      if(count==8)
                                       for(i=1;i<=9;i++)
                                       {
                                       if((arr[i][j][k]==0)&&(arr[i][j][0]==0))
                                       arr[i][j][0]=k;
                                       }
                      }
                      }
     }
     }

void squarefill(int arr[][10][10])            //function to solve array square-wise
     {
     singlesquarefill(arr,1,1);//2nd and 3rd arguments define row and column of first cell of particular square

     singlesquarefill(arr,1,4);

     singlesquarefill(arr,1,7);

     singlesquarefill(arr,4,1);

     singlesquarefill(arr,4,4);

     singlesquarefill(arr,4,7);

     singlesquarefill(arr,7,1);

     singlesquarefill(arr,7,4);

     singlesquarefill(arr,7,7);
     }

void singlesquarefill(int arr[][10][10],int i,int j)  //unique square solving function
{
     int l,m,k,n;

     for(l=i;l<=i+2;l++)   //fill square elements' 3rd dimension with values that are already present
     {
                        for(m=j;m<=j+2;m++)
                        {
                                           if(arr[l][m][0]!=0)
                                           {
                                                                for(k=i;k<=i+2;k++)
                                                                for(n=j;n<=j+2;n++)
                                                                if(arr[k][n][0]==0)
                                                                arr[k][n][arr[l][m][0]]=1;
                                           }
                        }
     }
     int count,flag;

     for(k=1;k<=9;k++)     //fills values which are uniquely confined to a particular cell in the square
     {
      count=0;
      flag=0;
      for(l=i;l<=i+2;l++)
      {                for(m=j;m<=j+2;m++)
                      {
                                         if(arr[l][m][0]==k)
                                         {flag=1;
                                         break;}
                      }
                      if(flag==1)
                      break;
      }

      if(flag==1)
      continue;

      else{

           for(l=i;l<=i+2;l++)
      {                for(m=j;m<=j+2;m++)
                      {
                                         if(arr[l][m][k]==1||arr[l][m][0]!=0)
                                         count++;
                      }
      }

      if(count==8)
      for(l=i;l<=i+2;l++)
      {
                       for(m=j;m<=j+2;m++)
                      {
                                         if(arr[l][m][k]==0&&arr[l][m][0]==0)
                                         arr[l][m][0]=k;
                      }
      }
      }
     }

}

void guesssolve(int arr[][10][10])  //called when direct computation methods fail
                                    //assumes value for a cell with minimum possibilities
                                    //further computes recursively until an impasse is reached
                                    //when an impasse is detected, next value is considered
{
     int trial[10][10][10];
     int i,j,k;
     int minunsol=10,mini,minj;


     int flag=0,count;

     for(i=1;i<=9;i++)
                      {
                       for(j=1;j<=9;j++)
                                        if(arr[i][j][0]==0)
                                        {
                                        count=0;

                                        for(k=1;k<=9;k++)
                                        if(arr[i][j][k]==0)
                                        count++;

                                                if(count==2)  //lowest possible options
                                                {
                                                mini=i;
                                                minj=j;
                                                minunsol=2;
                                                flag=1;
                                                break;
                                                }

                                        if(count<minunsol)
                                        {
                                         minunsol=count;
                                         mini=i;
                                         minj=j;
                                        }
                                        }
                      if(flag==1)
                      break;
                      }

     int posvalues[10];  //stores possible values

     count=1;

     for(k=1;k<=9;k++)
     if(arr[mini][minj][k]==0)
     {
      posvalues[count]=k;
      count++;
     }

     for(count=1;count<=minunsol;count++)
     if(numfilled(arr)!=81)  //if numfilled(arr) is 81, means we have solved the sudoku already
     {

       for(i=1;i<=9;i++)
                      for(j=1;j<=9;j++)
                                       for(k=0;k<=10;k++)
                                       trial[i][j][k]=arr[i][j][k]; //trial array, possible values
                                                                    //will be tried on this

      trial[mini][minj][0]=posvalues[count]; //poss. value selected

      fillsudo(trial);     //recursive call

      if(numfilled(trial)==81&&ifimpasse(trial)==0)  //means we have solved the array
      {
           for(i=1;i<=9;i++)
                      for(j=1;j<=9;j++)
                                       if(arr[i][j][0]==0)
                                       arr[i][j][0]=trial[i][j][0];
      }

     }


}

int ifimpasse(int arr[][10][10])  //checks if given array conditioon is an impasse
{
 int i,j,k,count;

 for(i=1;i<=9;i++)
                  for(j=1;j<=9;j++)
                                   if(arr[i][j][0]==0)
                                   {
                                   count=0;

                                    for(k=1;k<=9;k++)
                                    if(arr[i][j][k]==0)
                                    count++;

                                    if(count==0)
                                    return 1;
                                   }

 for(i=1;i<=9;i++)
                  for(k=1;k<=9;k++)
                                   {count=0;

                                   for(j=1;j<=9;j++)
                                   if(arr[i][j][0]==k)
                                   count++;

                                   if(count>1)
                                   return 1;
                                   }

 for(j=1;j<=9;j++)
                  for(k=1;k<=9;k++)
                                   {count=0;

                                   for(i=1;i<=9;i++)
                                   if(arr[i][j][0]==k)
                                   count++;

                                   if(count>1)
                                   return 1;
                                   }

 if(ifimpassesingsq(arr,1,1)==1)  //checks impasse for single square
 return 1;

 if(ifimpassesingsq(arr,1,4)==1)
 return 1;

 if(ifimpassesingsq(arr,1,7)==1)
 return 1;

  if(ifimpassesingsq(arr,4,1)==1)
 return 1;

  if(ifimpassesingsq(arr,4,4)==1)
 return 1;

  if(ifimpassesingsq(arr,4,7)==1)
 return 1;

  if(ifimpassesingsq(arr,7,1)==1)
 return 1;

  if(ifimpassesingsq(arr,7,4)==1)
 return 1;

  if(ifimpassesingsq(arr,7,7)==1)
 return 1;

return 0;
}

int ifimpassesingsq(int arr[][10][10],int i,int j)  //checks impasse for single square
{
 int l,m,k,count;

 for(k=1;k<=9;k++)
 {
 count=0;
     for(l=i;l<=i+2;l++)
                        for(m=j;m<=j+2;m++)
                        if(arr[l][m][0]==k)
                        count++;

 if(count>1)
 return 1;
 }

 return 0;
}

void randomfill(int arr[][10][10])
{
int i,j,k,c,flag;
int filled[10];
for(i=1;i<=9;i++)
filled[i]=0;

for(i=1;i<=9;i++)
    for(j=1;j<=9;j++)
         for(k=0;k<=9;k++)
               arr[i][j][k]=0;

arr[1][1][0]=rand()%9+1;
filled[arr[1][1][0]]=1;

   for(i=2;i<=9;i++)
   {
   flag=0;
               while(flag==0)
               {
               c=rand()%9+1;
                            if(filled[c]==0)
                            {
                            filled[c]=1;
                            arr[1][i][0]=c;
                            flag=1;
                            }
               }
   }

flag=0;

while(flag==0)
       {
       c=rand()%9+1;

                    if(c!=arr[1][1][0]&&c!=arr[1][2][0]&&c!=arr[1][3][0])
                    {
                    arr[2][1][0]=c;
                    flag=1;
                    }
       }

flag=0;
while(flag==0)
       {
       c=rand()%9+1;

                    if(c!=arr[1][1][0]&&c!=arr[1][2][0]&&c!=arr[1][3][0]&&c!=arr[2][1][0])
                    {
                    arr[3][1][0]=c;
                    flag=1;
                    }
       }

for(i=1;i<=9;i++)
filled[i]=0;

filled[arr[1][1][0]]=1;
filled[arr[2][1][0]]=1;
filled[arr[3][1][0]]=1;

for(i=4;i<=9;i++)
   {
   flag=0;
               while(flag==0)
               {
               c=rand()%9+1;
                            if(filled[c]==0)
                            {
                            filled[c]=1;
                            arr[i][1][0]=c;
                            flag=1;
                            }
               }
   }

fillsudo(arr);
}

void sudokumode(char mode)
{
if(mode=='c')
{
printf("\nTo fill any entry, use arrow keys to move to the particular location and fill the desired number.");
Sleep(3500);
challenge();
}
/*else if(mode=='t')
tutorial();
*/
else if(mode=='s')
{
printf("\nEnter the known values of the sudoku and press s when done.");
Sleep(3500);
custom();
}
}

void custom()
{

     system("CLS");
     printf("\t\t\t       SOLVER MODE");
     clearscreen();
     time_t ct;
     int x[9][9];
     int i,j,c,d,e,k,a,count=0;
     int filled[9][9]={{0},{0}};
     int newfilled[9][9]={{0},{0}};

     for(i=0;i<9;i++)
    for(j=0;j<9;j++)
    x[i][j]=32;

    i=0;
    j=0;

    x[0][0]=95;

    displayGrid(x,0,0,newfilled);

    while ((a =getch())!='s')

   {


       clearscreen();

       if(a == 75) {

           if(j!=0) {

               j--;

              if(x[i][j+1]==95)
              x[i][j+1]=32;

              if(filled[i][j]==0)
              x[i][j]=95;

               displayGrid(x,i,j,newfilled);
            }

       } else if ( a == 77) {

       if(j!=8) {

               j++;

              if(x[i][j-1]==95)
              x[i][j-1]=32;

              if(filled[i][j]==0)
              x[i][j]=95;

               displayGrid(x,i,j,newfilled);
            }

       } else if ( a == 72) {

       if(i!=0) {

               i--;

              if(x[i+1][j]==95)
              x[i+1][j]=32;

              if(filled[i][j]==0)
              x[i][j]=95;

               displayGrid(x,i,j,newfilled);
            }

       } else if ( a == 80) {

       if(i!=8) {

               i++;

              if(x[i-1][j]==95)
              x[i-1][j]=32;

              if(filled[i][j]==0)
              x[i][j]=95;

               displayGrid(x,i,j,newfilled);
            }

       }
       else if(a!=224){

       if(a==49||a==50||a==51||a==52||a==53||a==54||a==55||a==56||a==57)
       {
       x[i][j]=a-48;
       filled[i][j]=1;
       }

       if(a==8)
       {
       filled[i][j]=0;
       x[i][j]=32;
       }
       displayGrid(x,i,j,newfilled);
       }


   }

   int arr[10][10][10];

   for(i=1;i<=9;i++)
   for(j=1;j<=9;j++)
   for(k=0;k<=9;k++)
   arr[i][j][k]=0;


   for(i=0;i<9;i++)
   for(j=0;j<9;j++)
   if(!(x[i][j]==1||x[i][j]==2||x[i][j]==3||x[i][j]==4||x[i][j]==5||x[i][j]==6||x[i][j]==7||x[i][j]==8||x[i][j]==9))
   x[i][j]=0;

   for(i=0;i<9;i++)
   for(j=0;j<9;j++)
   if(filled[i][j]==0)
   newfilled[i][j]=1;

   for(i=0;i<9;i++)
   for(j=0;j<9;j++)
   arr[i+1][j+1][0]=x[i][j];

   fillsudo(arr);

   clearscreen();

   for(i=0;i<9;i++)
   for(j=0;j<9;j++)
   x[i][j]=arr[i+1][j+1][0];

   displayGrid(x,10,10,newfilled);
}

void challenge()
{
     char level;
     int i,j,k;
     int arr[10][10][10];

     randomfill(arr);

     printf("\nSelect level:\n1>Press 'e' for easy level:\n2>Press 'm' for medium level\n3>Press 'h' for hard level:\n");
     level=_getch();

     challengeprob(level,arr);


}

void challengeprob(char level,int arr[][10][10])
{
 int cnt,i,j,lim,a,b,flag;
 int tobeprinted[9][9];

 for(i=0;i<9;i++)
 for(j=0;j<9;j++)
 {
 tobeprinted[i][j]=0;
 }

 if(level=='e')
 lim=rand()%10+55;
 else if(level=='m')
 lim=rand()%5+35;
 else if(level=='h')
 lim=rand()%3+18;

 for(i=1;i<=lim;i++)
 {
 flag=0;
        while(flag==0)
        {
        a=rand()%9;
        b=rand()%9;

                     if(tobeprinted[a][b]==0)
                     {
                     flag=1;
                     tobeprinted[a][b]=arr[a+1][b+1][0];
                     }
        }
 }

startchallenge(tobeprinted,level);
}


void startchallenge(int x[][9],char level)
{
    int i,j,a,cnt;


    time_t ct=clock();
    int filled[9][9]={{0},{0}};
    int perm[9][9]={{0},{0}};
    int newfilled[9][9]={{0},{0}};

    for(i=0;i<9;i++)
    for(j=0;j<9;j++)
    if(x[i][j]!=0)
    {filled[i][j]=1;
    perm[i][j]=1;}

    for(i=0;i<9;i++)
    for(j=0;j<9;j++)
    if(x[i][j]==0)
    x[i][j]=32;

    i=0;
    j=0;

    if(x[0][0]==32)
    x[0][0]=95;

    system("CLS");
    printf("\t\t\t\tCHALLENGE");
    clearscreen();
    displayGrid(x,0,0,newfilled);

             while(!kbhit())
         {
         cnt=(clock()-ct)/1000;

         printf("\t\t\t       %.02d : %.02d : %.02d\r",cnt/3600,(cnt%3600)/60,cnt%60);
         }


    while (ifimpassenew(x)==1&&(a=getch())!='q'&&(a!='s'))

   {


       clearscreen();

       if(a == 75) {

           if(j!=0) {

               j--;

              if(x[i][j+1]==95)
              x[i][j+1]=32;

              if(filled[i][j]==0)
              x[i][j]=95;
              }
               displayGrid(x,i,j,newfilled);


       } else if ( a == 77) {

       if(j!=8) {

               j++;

              if(x[i][j-1]==95)
              x[i][j-1]=32;

              if(filled[i][j]==0)
              x[i][j]=95;
              }
               displayGrid(x,i,j,newfilled);


       } else if ( a == 72) {

       if(i!=0) {

               i--;

              if(x[i+1][j]==95)
              x[i+1][j]=32;

              if(filled[i][j]==0)
              x[i][j]=95;
              }
               displayGrid(x,i,j,newfilled);


       } else if ( a == 80) {

       if(i!=8) {

               i++;

              if(x[i-1][j]==95)
              x[i-1][j]=32;

              if(filled[i][j]==0)
              x[i][j]=95;
              }
               displayGrid(x,i,j,newfilled);


       }
       else if(a!=224){

       if(perm[i][j]==0)
       {
       if(a==49||a==50||a==51||a==52||a==53||a==54||a==55||a==56||a==57)
       {x[i][j]=a-48;
       newfilled[i][j]=1;
       filled[i][j]=1;
       }
       if(a==8)
       {
       filled[i][j]=0;
       newfilled[i][j]=0;
       x[i][j]=32;
       }
       }
       if(ifimpassenew(x)==0)
       break;
       displayGrid(x,i,j,newfilled);
       }

while(!kbhit())
         {
         cnt=(clock()-ct)/1000;

         printf("\t\t\t       %.02d : %.02d : %.02d\r",cnt/3600,(cnt%3600)/60,cnt%60);

         }
   }
if(a!='q'&&a!='s')
{
system("CLS");
printf("\n\n\t\tCongratulations, you have solved the puzzle!\n\n");
printf("\t\t\tYour time : ");
printf("%.02d : %.02d : %.02d",cnt/3600,(cnt%3600)/60,cnt%60);
printf("\n\n\t\t\t    Your Score : %d\n\n",score(cnt,level));
Sleep(2500);
}

system("CLS");

}

int ifimpassenew(int arr[][9])
{
int i,j,k,count;
for(i=0;i<9;i++)
{
count=0;
for(k=1;k<=9;k++)
for(j=0;j<9;j++)
if(arr[i][j]==k)
count++;

if(count!=9)
return 1;
}

 for(j=0;j<9;j++)
{
count=0;
for(k=1;k<=9;k++)
for(i=0;i<9;i++)
if(arr[i][j]==k)
count++;

if(count!=9)
return 1;
}

 if(ifimpassesingsqnew(arr,0,0)==1)  //checks impasse for single square
 return 1;

 if(ifimpassesingsqnew(arr,0,3)==1)
 return 1;

 if(ifimpassesingsqnew(arr,0,6)==1)
 return 1;

  if(ifimpassesingsqnew(arr,3,0)==1)
 return 1;

  if(ifimpassesingsqnew(arr,3,3)==1)
 return 1;

  if(ifimpassesingsqnew(arr,3,6)==1)
 return 1;

  if(ifimpassesingsqnew(arr,6,0)==1)
 return 1;

  if(ifimpassesingsqnew(arr,6,3)==1)
 return 1;

  if(ifimpassesingsqnew(arr,6,6)==1)
 return 1;

return 0;
}

int ifimpassesingsqnew(int arr[][9],int i,int j)
{
    int l,m,k,count;

 for(k=1;k<=9;k++)
 {
 count=0;
     for(l=i;l<=i+2;l++)
                        for(m=j;m<=j+2;m++)
                        if(arr[l][m]==k)
                        count++;

 if(count!=1)
 return 1;
 }

 return 0;
}

void displayGrid(int grid[][9],int a,int b,int newfilled[][9])
{

int i,j;
         printf("\t\t\t+ - - - + - - - + - - - +");      //for giving proper orientation to sudoku

         for(i=0;i<3;i++)                          //output
         {
            printf("\n");
            printf("\t\t\t| ");

            for(j=0;j<3;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }
            printf("| ");

            for(j=3;j<6;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("| ");

            for(j=6;j<=8;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("|");
         }

         printf("\n\t\t\t+ - - - + - - - + - - - +");

         for(i=3;i<6;i++)
         {
            printf("\n");
            printf("\t\t\t| ");
            for(j=0;j<3;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("| ");

            for(j=3;j<6;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("| ");

            for(j=6;j<9;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("|");
         }

         printf("\n\t\t\t+ - - - + - - - + - - - +");

         for(i=6;i<9;i++)
         {
          printf("\n");
            printf("\t\t\t| ");
            for(j=0;j<3;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("| ");

            for(j=3;j<6;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("| ");

            for(j=6;j<9;j++){
            if((i!=a||j!=b)&&newfilled[i][j]==0)
            {
            if(grid[i][j]==95||grid[i][j]==32)
            printf("%c ",(char)grid[i][j]);
            else printf("%d ",grid[i][j]);
            }
            else if((i!=a||j!=b))
            {
                 ClearConsoleToColors(10,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
            }
            else {
                 ClearConsoleToColors(12,15);
                 if(grid[i][j]==95||grid[i][j]==32)
                 printf("%c ",(char)grid[i][j]);
                 else
                 printf("%d ",grid[i][j]);
                 ClearConsoleToColors(0,15);
                 }
            }

            printf("|");
         }
         printf("\n\t\t\t+ - - - + - - - + - - - +\n\n\n");

}

void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 2;
    SetConsoleCursorPosition(hOut, Position);
}

int score(int cnt,char level)
{
if(level=='e')
return (24000/cnt);

if(level=='m')
return (48000/cnt);

if(level=='h')
return (72000/cnt);
}
/*
void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
                   //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                         //This is used to reset the carat/cursor to the top left.
     DWORD count;

                                   //This is a structure containing all of the console info
                          // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
                     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);

     return;
}*/


void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hStdOut, wColor);

     return;
}
