#include <string.h>
int print_char(char c);
int countdigits(int n);
void print_digits(int n, int count);

/*takes an integer and prints it*/
void print_number(int n){
  int count;
  if (n==0){ /*if n is 0 print 0 and return*/
    print_char('0');
    return;
  }
  count=countdigits(n); /*count digits*/
  if (n<0) print_char('-'); /*if neg number*/
  print_digits(n, count);
}

/*digit count function*/
int countdigits(int n){
  int count;
  for ( count=0; n!=0; n/=10 ) count++;
  return count;
}

/*extract and print digits*/
void print_digits(int n, int count){
  int ncopy, temp, t;
  for ( temp=0; count>0; count-- ){
    ncopy=n;
    for (t=count;t>1;t--) ncopy/=10;
    t=ncopy-(temp*10);
    temp=ncopy;
    if (t<0) t*=(-1);
    print_char(t+48);
  }
}

void print_array(int *array, int size) {
  int i;
  for ( i = 0 ; i < size ; i++) {
    print_number(array[i]);
    if (i < size - 1) {
      print_char(',');
      print_char(' ');
    }
  }
  print_char('\n');
}

void print_array_str(char **array) {
  int i;
  for (i=0; array[i]!=NULL; i++) {
    int j;
    for (j=0; array[i][j]!='\0'; j++) {
      print_char(array[i][j]);
    }
    if (array[i+1]!=NULL) {
      print_char(',');
      print_char(' ');
    }
  }
  print_char('\n');
}
