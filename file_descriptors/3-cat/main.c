#include <unistd.h>
int stdin_writer();

int main(){
  if ( stdin_writer() ) return 1;
  return 0;
}

int stdin_writer(){
  int i;
  char buf;
  while ( (i=read(0, &buf, 1)) ){
    if ( i==-1 || write(1, &buf, 1)==-1 )
      return 1;
  }
  return 0;
}
