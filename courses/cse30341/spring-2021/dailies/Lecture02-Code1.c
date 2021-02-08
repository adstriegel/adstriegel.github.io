#include <stdio.h> 

char bKeepLooping = 1; 

void myFunction (void * pData)
{
  int * pNumber = (int *) pData;
  printf("%d\n", pNumber[0]);
}

int main( int argc, char *argv[] ) 
{ 
  int nVal = 3;
  int * pVal;

  pVal = &nVal;
  myFunction(pVal);  
}
