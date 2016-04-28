void toggle_flag(int *c);
int overflow(int number, char *x);

/*returns first integer in a string*/

int string_to_integer(char *s){
  int number, flag;
  number=0;
  flag=0; /*check repeated occurance of neg signs*/
  for ( ; *s ; s++ ){
    if ( *s == '-' )
      toggle_flag( &flag );
    if ( *s >= '0' && *s <= '9' ){
      for ( ; *s >= '0' && *s <= '9' ; s++ ){
	if ( overflow(number, s) ){
	  number=0;
	  break;
	}
	if ( flag ) number=(number*10)-(*s-'0');
	else number=(number*10)+(*s-'0');
      }
      break;
    }
  }
  return number;
}

void toggle_flag(int *c){ /*switches the value of flag [0,1]*/
  if (*c==0) *c=1;
  else *c=0;
}

int overflow(int number, char *x){ /*checks overflow*/
  if ( number>=214748360 ){
    if (*(x+1)>='0' && *(x+1)<='9')  return 1;
    if (*x>'7') return 1;
  }
  if ( number<=-214748360 ){
    if (*(x+1)>='0' && *(x+1)<='9') return 1;
    if (*x>'8') return 1;
  }
  return 0;
}
