#include <unistd.h>
//#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int eval(){
  const char code[]="#include <stdlib.h>\n\
  #include <string.h>\n\
  #include <stdio.h>\n\
  int test(int a,int b){\
  return a+b;\
  }\
  int main(int argc,char** argv){\
  int val=test(strtol(argv[1],NULL,10),strtol(argv[2],NULL,10));\
  return val;\
  }";

  FILE* file=fopen("\\user_c_files\\moj_kod.c","w");
  fprintf(file,code);
  fclose(file);
  int child_pid,wpid;
  int status=0;
  
  
  STARTUPINFO info={sizeof(info)};
  PROCESS_INFORMATION processInfo;
  
  if(CreateProcessA(
    "gcc\\gcc-13.2.0-no-debug\\bin\\gcc.exe", "gcc ./user_c_files/moj_kod.c -o ./user_c_files/moj_kod.exe",NULL,NULL,TRUE,0,NULL,NULL,&info,&processInfo
  )){
    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
  }
  PDWORD ret;
  STARTUPINFO info1={sizeof(info)};
  if(CreateProcessA(
    "user_c_files\\moj_kod.exe", "moj_kod 5 3",NULL,NULL,TRUE,0,NULL,NULL,&info1,&processInfo
  )){
    WaitForSingleObject(processInfo.hProcess, INFINITE);
    GetExitCodeProcess(processInfo.hProcess,ret);
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
  }
  
  printf("%d",*ret);
  printf("%d",GetLastError());

  
  return 0;
  
}

int main(){
  return eval();
}