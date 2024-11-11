#include <cstring>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <mutex>
#include "arch/boot.h"
#include "kernel/sys-controller.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(){
  const string IP = "104.26.14.72";
  warn_connect(IP);
  system_load();
  terminal();
  return 0;
}
