// =============================================
// wtime - Unix time command for Windows
//
// author: Marc-Daniel DALEBA
// date: 2025-07-07
// license: MIT
// description:  
//    Simple time command for Windows that measures
//    real, user and system CPU time of a command.
//
// usage:
//    wtime [-p] command [args...]
// =============================================

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_CMD_LEN 1024
#define l0(a) (((a) < 0) ? (0) : (a))

PROCESS_INFORMATION pi;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
  switch (fdwCtrlType) {
  case CTRL_C_EVENT:
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, pi.dwProcessId);
    return TRUE;

  default:
    return FALSE;
  }
}

int main(int argc, char **argv)
{
  int p;
  bool portable;
  char cmd[MAX_CMD_LEN];
  STARTUPINFO si;
  LARGE_INTEGER time00, time01, freq;
  FILETIME creation, exit, kernel, user;
  ULONGLONG kernelLong, userLong;
  double realTime, kernelTime, userTime; 
  
  portable = false;
  memset(cmd, '\0', MAX_CMD_LEN);
  if (argc > 1) {
    p = 1;
    if (!strcmp(argv[p], "-p")) {
      portable = true;
      p++;
    }
    for (; p < argc; ++p) {
      strncat(cmd, argv[p], l0(MAX_CMD_LEN - strlen(cmd)));
      if (p < argc - 1) strncat(cmd, " ", l0(MAX_CMD_LEN - strlen(cmd)));
    }
    
    SetConsoleCtrlHandler(CtrlHandler, TRUE);
    
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    
    QueryPerformanceFrequency(&freq); 
    QueryPerformanceCounter(&time00);
    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
      printf("error: CreateProcessA(...) failed.\n");
      return -1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    QueryPerformanceCounter(&time01);
    realTime = (double)(time01.QuadPart - time00.QuadPart) / freq.QuadPart;
    
    GetProcessTimes(pi.hProcess, &creation, &exit, &kernel, &user);
    kernelLong = (((ULONGLONG)kernel.dwHighDateTime) << 32) | kernel.dwLowDateTime;
    userLong = (((ULONGLONG)user.dwHighDateTime) << 32) | user.dwLowDateTime;
    kernelTime = (double)kernelLong / 10000000.0;
    userTime = (double)userLong / 10000000.0;
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  }
  printf("\n");
  if (portable) {
    printf("real %.2f\nuser %.2f\nsys %.2f\n", realTime, userTime, kernelTime);
  } else {
    printf("%-8s %dm%.3f\n", "real", (int)(realTime / 60.0), (float)fmod(realTime, 60.0));
    printf("%-8s %dm%.3f\n", "user", (int)(userTime / 60.0), (float)fmod(userTime, 60.0));
    printf("%-8s %dm%.3f\n", "sys", (int)(kernelTime / 60.0), (float)fmod(kernelTime, 60.0));
  }
  return 0;
}