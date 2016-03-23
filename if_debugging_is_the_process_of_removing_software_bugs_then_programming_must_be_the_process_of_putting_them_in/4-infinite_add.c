void count(char *n1,char *n2,int *count1,int *count2);
char *make_copy(char *ncopy1,char *ncopy2, char *n1, char *n2, 
		int size_r, int count1, int count2, char *r);
char *add(char *n1, char *n2, int size_r, char *r);

char *infinite_add(char *n1, char *n2, char *r, int size_r){
  int count1, count2;
  size_r--;
  char ncopy1[size_r];
  char ncopy2[size_r];
  count(n1,n2,&count1,&count2);
  return make_copy(ncopy1,ncopy2,n1, n2, size_r, count1, count2, r);
}


void count(char *n1,char *n2,int *count1,int *count2){
  int n1c, n2c;
  for (n1c=0;*(n1+n1c)!='\0';n1c++);
  for (n2c=0;*(n2+n2c)!='\0';n2c++);
  *count1=n1c-1;
  *count2=n2c-1;
}

char* make_copy(char *ncopy1,char *ncopy2, char *n1,
		char *n2, int size_r, int count1, int count2, char *r){
  int i1, i2,temp;
  for (i1=0;n1[i1]!='\0';i1++, count1--)
    ncopy1[size_r-i1]=n1[count1];
  for (i2=0;n2[i2]!='\0';i2++, count2--)
    ncopy2[size_r-i2]=n2[count2];
  if (i1>i2){
    temp=i1-i2;
    for (i1=0;i1<temp;i1++)
      ncopy2[size_r-i2-i1]='0';
  }
  else if (i2>i1){
    temp=i2-i1;
    for (i2=0;i2<temp;i2++)
      ncopy1[size_r-i1-i2]='0';
  }
  ncopy1[size_r-i1-i2]='\0';
  ncopy2[size_r-i1-i2]='\0';
  return add(ncopy1,ncopy2,size_r+1,r);
}

char *add(char *n1, char *n2, int size_r, char *r){
  int carry, overflow;
  size_r--;
  r[size_r]='\0';
  overflow=0;
  carry=0;
  for (;n1[size_r]!='\0';size_r--,overflow++){
    int temp;
    if (overflow==size_r)
      return 0;
    temp=carry+(int)(n1[size_r]-'0')+(int)(n2[size_r]-'0');
    carry=0;
    if (temp<9)
      r[size_r-1]=(char)(temp+'0');
    else{
      r[size_r-1]=(char)(temp%10) + '0';
      carry=temp/10;
    }
  }
  if (carry)
    r[size_r-1]=(char)carry+'0';
  else
    size_r++;
  return r+(size_r-1);
}
