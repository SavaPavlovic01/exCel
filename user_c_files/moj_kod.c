#include <stdlib.h>
  #include <string.h>
  #include <stdio.h>
  int test(int a,int b){  return a+b;  }  int main(int argc,char** argv){  int val=test(strtol(argv[1],NULL,10),strtol(argv[2],NULL,10));  FILE* file=fopen("/home/ss/Desktop/exCel/moj_kod.txt","w");  fwrite(&val,4,1,file);  fclose(file);  exit(val);  }