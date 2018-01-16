#include <cstdlib>  // need in odrer to use system  class
//#include <iostream> //more C-like,  std
#include <stdio.h> // C++ specific need for printf
#include <math.h>

//from build essetial
//#include <array> Provide  ---------array.size(); Not in Unix lib

#include <dlfcn.h> // to use dlopen | dlclose compile with -ldl
//#include <unistd.h> //get current working directory  sleep(secs)
//#include "shared.h"
#include <string.h>
#pragma once


// compile with: g++ -shared -fPIC name.cpp -o all.so -ldl
//void* handle; ??
extern "C" int invokeHelpingLib(){

   //how to find the current working directory???
   void* handle = dlopen ("/home/student/Documents/netProbe/myLib.so", RTLD_LAZY);
   int (*testFunc)();// template for the function
   if(!handle){
     return 1;
   }else{
     testFunc = (int(*)())dlsym(handle, "helpingLib");
     testFunc(); // === helpingLib();
     int t =dlclose (handle);
	printf("Closed ? = %d",t);
   }
   return 0;   
}

//notHelp(); return 1;

