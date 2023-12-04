#include <unistd.h>
//#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int eval(){
  const char code[]="#include <stdlib.h>\n\
  #include <string.h>\n\
  #include <stdio.h>\n\
  int test(int a,int b){\
  return a+b;\
  }\
  int main(int argc,char** argv){\
  int val=test(strtol(argv[1],NULL,10),strtol(argv[2],NULL,10));\
  FILE* file=fopen(\"/home/ss/Desktop/exCel/moj_kod.txt\",\"w\");\
  fwrite(&val,4,1,file);\
  fclose(file);\
  exit(val);\
  }";

  FILE* file=fopen("moj_kod.c","w");
  fprintf(file,code);
  fclose(file);
  int child_pid,wpid;
  int status=0;
  
  char* args[]={
    "gcc",
    "/home/ss/Desktop/exCel/moj_kod.c",
    "-o",
    "/home/ss/Desktop/exCel/moj_kod",
    NULL
  };
  
  if((child_pid=fork())==0){
      execv("/usr/bin/gcc",args);
      exit(0);
  }
  while ((wpid = wait(&status)) > 0);
  int ret;
  if((child_pid=fork())==0){
    char* args_test[]={
      "moj_kod",
      "12",
      "3",
      NULL
    };
    int i=execvp("./moj_kod",args_test);
    exit(0);
  }

  while ((wpid = wait(&status)) > 0);
  int try_val=WEXITSTATUS(status);
  FILE* pls_work=fopen("/home/ss/Desktop/exCel/moj_kod.txt","r");
  int val;
  fread(&val,4,1,file);
  printf("%d\n",val);
  printf("%d\n",try_val);
  
  return 0;
  
}