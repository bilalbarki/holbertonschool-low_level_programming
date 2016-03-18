#include <stdio.h>
int print_char(char c);
void print_hexa(int num, int digits);
void fill_it(int, int);
/*prints whole buffer with . for non printables*/
void print_buffer(char *b, int size){
  int x,i,j,filler;
  if (size <= 0)
    printf("\n");
  for( x=0x0 , i=0 ; i<size ; i=i+10, x=x+(0xa)){
    filler=0;
    print_hexa(x,8);
    print_char(':');
    print_char(' ');
    for (j=x;j<(x+10) && j<size;j++){
      print_hexa((int)b[j],2);
      if (j%2)
	print_char(' ');
      filler++;
    }
    fill_it(filler,size);
    for (j=x;j<(x+10) && j<size;j++){
      if (b[j]>=32 && b[j]!=127)
	print_char(b[j]);
      else
	print_char('.');
    }
    printf("\n");
  }
}
/*prints hexavalue using print_char*/
void print_hexa(int num, int digits){
  int a[10],c;
  for (c=0;num;num/=0x10){
    c++;
    a[c]=num%0x10;
  }
  fflush(stdout);
  for (;digits>c;digits--)
    print_char('0');
  for (;c>0;c--)
    if (a[c]>=0 && a[c]<10)
      print_char(a[c]+0x30);
    else if (a[c]==(0xa))
      print_char('a');
    else if (a[c]==0xb)
      print_char('b');
    else if (a[c]==0xc)
      print_char('c');
    else if (a[c]==0xd)
      print_char('d');
    else if (a[c]==0xe)
      print_char('e');
    else if (a[c]==0xf)
      print_char('f');

}
/*manages spaces*/
void fill_it(int filler, int size){
  int count;
  for (count=(10-filler)/2;count>0;count--)
    print_char(' ');

  for (;filler < 10;filler++){
    print_char(' ');
    print_char(' ');
    if (filler==9 && size%2!=0)
      print_char(' ');
  }
}
