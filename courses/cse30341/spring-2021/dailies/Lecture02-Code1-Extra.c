#include <stdio.h>

char bKeepLooping = 1;

void myFunction (void * pData)
{
  int * pNumber = (int *) pData;
  printf("%d\n", pNumber[0]);

  printf("\n\n==Extra==\n");
  printf("  pData:    %p\n", pData);
  printf("  pNumber:  %p\n", pNumber);
}

int main (int argc, char *argv[])
{
  int nVal = 3;
  int * pVal;

  pVal = &nVal;
  myFunction(pVal);

  printf("  pVal:     %p\n", pVal);
  printf(" &nVal:     %p\n", &nVal);

  printf("==Extra Extra==\n");
  printf(" myFunction: %p\n", myFunction);
}
