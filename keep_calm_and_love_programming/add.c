#include <stdio.h>
int bilal(unsigned char a[],unsigned char b[]);

int bb;
int main(){
  unsigned char b[]={9,9,9};
  unsigned char a[]={1,2,3};
  bb=0;
  bilal(a,b);
  return 0;
}

int bilal(unsigned char a[],unsigned char b[])
{
  unsigned char sum[4];
  int carry;
  int i;
  carry=0;
  bb=1;
  for(i = 2; i > -1; i--)
    {
      if ( (carry + (int)a[i] + (int)b[i] ) <10 )
	{
	  sum[i+1] = (char) (carry + (int)a[i] + (int)b[i]);
	  carry=0;
	}

      else
	{
	  sum[i+1] = (char) ((carry + (int)a[i] + (int)b[i])%10);
	  carry=((int)a[i] + (int)b[i])/10;
	}
    }
  if(carry>0){
    sum[i+1]=carry;

  }


  for(i = 0; i < 4; i++)
    printf("%u",sum[i]);
  return 0;
}
