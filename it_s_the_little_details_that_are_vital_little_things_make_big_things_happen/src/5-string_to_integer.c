void switch_flag(int *c);
int check_overflow(int number, char *x);

int string_to_integer(char *s){ /*returns first integer in a string*/
  int number, flag;
  number=0;
  flag=0; /*for checking concurrency of negative signs*/
  while (*s){
    if (*s=='-')
      switch_flag(&flag);
    if (*s>='0' && *s<='9'){
      while (*s>='0' && *s<='9'){
	if (check_overflow(number, s)){
	  number=0;
	  break;
	}
	if (flag) /*if negative*/
	  number=(number*10)-(*s-'0');
	else
	  number=(number*10)+(*s-'0');
	s++;
      }
      break;
    }
    s++;
  }
  return number;
}

void switch_flag(int *c){ /*switches the value of flag [0,1]*/
  if (*c==0)
    *c=1;
  else
    *c=0;
}

int check_overflow(int number, char *x){ /*checks overflow*/
  if (number>=214748360){
    if (*(x+1)>='0' && *(x+1)<='9'){
      return 1;
    }
    if (*x>'7'){
      return 1;
    }
  }
  if (number<=-214748360){
    if (*(x+1)>='0' && *(x+1)<='9'){
      return 1;
    }
    if (*x>'8'){
      return 1;
    }
  }
  return 0;
}
