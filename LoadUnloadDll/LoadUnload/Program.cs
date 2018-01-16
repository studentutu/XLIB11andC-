using System;
using System.Runtime.InteropServices;

namespace LoadUnload
{
 class Program
    {
        static void Main(string[] args)
        {

            IsLinux();
            Console.WriteLine(IntPtr.Size == 8 ?"64":"32");
		if(IsLinux){
            		funcWithLoadUnload("/home/student/Documents/netProbe/LoadUnloadDll/LoadUnload/myLib.so");
		}
            
  
        }

        private static bool IsLinux() {
            var p = (int) Environment.OSVersion.Platform;
            return (p == 4) || (p == 6) || (p == 128);// if true - Linux
        }
        
        
        //DLLImport "dlfcn"/libdl    Load lib
	// use flag RTLD_LAZY=1,  RTLD_NOW = 2;
	// String path/nameOfLib.so, int 1(RTLD_LAZY)
        [DllImport("libdl", SetLastError = true)]
        private static extern IntPtr dlopen(String s, int some );
        
	// GEt the function out of the library
        [DllImport("libdl", SetLastError = true)]
        private static extern IntPtr dlsym(IntPtr hand, String funcName );

	//Unload Lib
        [DllImport("libdl", SetLastError = true)]
        private static extern int dlclose(IntPtr hand);

        //delegate for the function from library
        internal delegate int MyCrossplatMethod();


        public static void funcWithLoadUnload(string pathTo){
            //RTLD_LAZY =1;
            //RTLD_NOW = 2;

            var handle = dlopen(pathTo,2);
            var functionHandle = dlsym(handle, "helpingLib");

            var method =(MyCrossplatMethod)Marshal.GetDelegateForFunctionPointer(
                functionHandle,
                typeof(MyCrossplatMethod));

            int someInt = method();
            Console.WriteLine("From helping Lib? -"+ someInt);
            someInt = dlclose(handle);
            Console.WriteLine("Unloaded lib? 0 yes non-0 -oops" + someInt);
            return;
        }


        //Windows Kernel32: LoadLibrary("Path/to/myLibrary.dll"), FreeLibrary(...)
        /**
        foreach (System.Diagnostics.ProcessModule mod in System.Diagnostics.Process.GetCurrentProcess().Modules)
        {
            if (mod.FileName == DllPath)
            {
                FreeLibrary(mod.BaseAddress);
                Console.WriteLine("freed" + mod.FileName);
            }
        }
        */
        

        /**
	// Lib has function: int helpingLib(){....}
	// createSimpleWindow.cpp compiled with 
 	// g++ -shared -fPIC createSimpleWindow.cpp -o myLib.so {-lX11}<- dependet library of the createSimpleWindow
        [DllImport("/home/student/Documents/netProbe/LoadUnloadDll/LoadUnload/myLib.so")]
        private static extern int helpingLib();

        public static void get_something_done(){
                            
            int save = helpingLib();
            

        }
        */

       

    }//class Program
}// namespace
