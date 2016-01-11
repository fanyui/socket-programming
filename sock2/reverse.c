#include<stdio.h>
void fxn();
int main(){
fxn();
}
void fxn(){
char x=getchar();
if(x!='\n'){
fxn();
putchar(x);
}
}
