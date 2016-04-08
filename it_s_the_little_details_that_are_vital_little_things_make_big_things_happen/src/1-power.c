/*calculates x^y*/

int power(int x, int y){
  int temp;
  if (x<0) return -1;
  else if (y>0){

    temp=x*power(x, y-1);
    if (temp<x) return -1;
    else return temp;
  }
  else if (y==0) return 1;
  else return -1;
}
