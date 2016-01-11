#include<stdio.h>

#include<stdlib.h>
//a programe that count blanks tabs and newlines
int main(){

char c;
int sp=0;
int tab=0;
int nl=0;
while((c=getchar())!=EOF)
    if (c==' ')
        ++sp;
    else if(c=='\t')
        ++tab;
    else if(c=='\n')
    ++nl;

printf("%d space %d tab %d newlines\n",sp,tab,nl);
getch();
return 0;
}
