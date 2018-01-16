#pragma once
#include <cstdlib>  // need in odrer to use system  class
#include <iostream>
//#include <stdio.h> // need for printf
#include <math.h>
#include <X11/Xlib.h>
//#include <string.h>
#include <unistd.h> // sleep (seconds)
//from build essetial
//#include <array> Provide  ---------array.size(); Not in Unix lib
//#include "shared.h"
using namespace std;

// compile with: g++ -shared -fPIC name.cpp -o name.so -lX11

 extern "C" int helpingLib(){

  // Open a display.
    Display *d = XOpenDisplay(0);
    Window w;

 //events
   XEvent event;
   int s;

 //---------------
   XSetWindowAttributes attributes;
   Visual *visual;
   int depth;

    if ( d )
    {
        // Create the window
        /* create window */
        s = DefaultScreen(d);

        // w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1,
        //                    BlackPixel(d, s), WhitePixel(d, s));


       visual = DefaultVisual(d,s);
       depth  = DefaultDepth(d,s);
       attributes.background_pixel = XWhitePixel(d,s);
       //Window root  = XRootWindow(d,s);

       // Root
       //std::cout << root;

       w = XCreateWindow( d,XRootWindow(d,s),
                              200, 200, 350, 200, 5, depth,  InputOutput,
                              visual ,CWBackPixel, &attributes);

        // Sleep long enough to see the window.
        //sleep(20);
  }
  // Show the window
  XMapWindow(d, w);
  XFlush(d);

  /* select kind of events we are interested in */
  XSelectInput(d, w, ExposureMask | KeyPressMask | ButtonPressMask);

  bool tmp = false;
  for(;!tmp;){

        XNextEvent(d, &event);

          /* draw or redraw the window */
        if (event.type == Expose)
        {
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            //XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, strlen(msg));
        }

        /* exit on key press */
        if (event.type == KeyPress){
          tmp = true;
        }
        if (event.type == ButtonPress){
          tmp = true;
        }
  }

  XCloseDisplay(d);
  /* close connection to server */
  //XCloseDisplay(d);

  return 0;
}
