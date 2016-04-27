int print_char(char c);

/*prints all possible combinations 
  of three different digits*/

void print_combination_3(void)
{
  int i,j,k;
  for ( i=0 ; i<8 ; i++ ){
      for ( j=i+1 ; j<9 ; j++ ){
          for ( k=j+1 ; k<10 ; k++ ){
              print_char(i+48);
              print_char(j+48);
              print_char(k+48);
              if ( !(i==7 && j==8 && k==9) ){
                  print_char(',');
                  print_char(' ');
              }
           }
       }
   }
}
