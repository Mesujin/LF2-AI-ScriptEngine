////////////////////////////////////////////////////////////////////////////////////////////
// "platform.cpp", written based on DirectDraw Wrapper ;                                  //
//                                                                                        //
//----------------------------------------------------------------------------------------//
//                                                                                        //
//  Version 1.0, August 6th, 2010.                                                        //
//  Copyright (C) 2010 Jari Komppa.                                                       //
//                                                                                        //
//  This software is provided 'as-is', without any express or implied                     //
//  warranty. In no event will the authors be held liable for any damages                 //
//  arising from the use of this software.                                                //
//                                                                                        //
//  Permission is granted to anyone to use this software for any purpose,                 //
//  including commercial applications, and to alter it and redistribute it                //
//  freely, subject to the following restrictions:                                        //
//                                                                                        //
//  1. The origin of this software must not be misrepresented; you must not               //
//     claim that you wrote the original software. If you use this software               //
//     in a product, an acknowledgment in the product documentation would be              //
//     appreciated but is not required.                                                   //
//  2. Altered source versions must be plainly marked as such, and must not be            //
//     misrepresented as being the original software.                                     //
//  3. This notice may not be removed or altered from any source distribution.            //
//                                                                                        //
// Jari Komppa http://iki.fi/sol/                                                         //
//                                                                                        //
//----------------------------------------------------------------------------------------//
//                                                                                        //
// Based on a zlib/libpng licensed source code found on the net,                          //
// http://www.mikoweb.eu/index.php?node=28                                                //
// re-worked so much that there's fairly little left of the original.                     //
//                                                                                        //
//----------------------------------------------------------------------------------------//
//                                                                                        //
// Modified by Doix - not the original wrapper                                            //
//                                                                                        //
//----------------------------------------------------------------------------------------//
//                                                                                        //
// More modifications made by Someone else                                                //
//                                                                                        //
//----------------------------------------------------------------------------------------//
//                                                                                        //
// Some enhancement made by zort.                                                         //
//                                                                                        //
//----------------------------------------------------------------------------------------//
//                                                                                        //
// Rearranged by Mesujin.                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////

// Includes
 #include "platform.h"

// Global Variables
 #pragma data_seg (".ddraw_shared")
  HINSTANCE Hins0001; // Original DLL's H-Instance.
  HINSTANCE Hins0002; // This H-Instance.
 #pragma data_seg ()

// DirectDraw's Function
 BOOL    APIENTRY DllMain(HANDLE Hand01, DWORD Dwrd01, LPVOID Lpvd01)
 {
  LPVOID Lpvd02 = Lpvd01; Lpvd02 = NULL;
  
  switch(Dwrd01)
  {
   case DLL_PROCESS_ATTACH:
    M_Starting();
	Hins0001 = NULL; Hins0002 = NULL;
	Hins0002 = (HINSTANCE)Hand01; // Storing Instance handle into global var
   break;
   case DLL_PROCESS_DETACH:
    M_Cleaning();
    if(Hins0001){FreeLibrary(Hins0001); Hins0001 = NULL;}
   break;
   case DLL_THREAD_ATTACH: break;
   case DLL_THREAD_DETACH: break;
  }
  return true;
 }
 HRESULT WINAPI   DirectDrawCreate(GUID FAR *Lpgd01, LPDIRECTDRAW FAR *Lpdd01, IUnknown FAR *Ikwn01)
 {
  if(!Hins0001) // Looking for the "right ddraw.dll".
  {
   int8 Vrab01[MAX_PATH]; GetSystemDirectoryA(Vrab01, MAX_PATH); // Getting path to system dir. (C:\Windows\System32)

   strcat_s(Vrab01,"\\ddraw.dll");
   Hins0001 = LoadLibraryA(Vrab01);
   
   if(!Hins0001) ExitProcess(0); // Exit the hard way.
  }

  // Hooking DDRAW interface from Original Library IDirectDraw *pDD;
  typedef HRESULT (WINAPI* DirectDrawCreate_Type)(GUID FAR *, LPVOID *, IUnknown FAR *);
  DirectDrawCreate_Type DirectDrawCreate_fn = (DirectDrawCreate_Type) GetProcAddress(Hins0001, "DirectDrawCreate");

  if(!DirectDrawCreate_fn) ExitProcess(0); // Exit the hard way.

  LPDIRECTDRAW7 FAR Lpdd02;
  HRESULT Hres01 = DirectDrawCreate_fn(Lpgd01, (LPVOID*) &Lpdd02, Ikwn01);
  *Lpdd01 = (LPDIRECTDRAW) new myIDDraw7(Lpdd02);
  return Hres01;
 }

// Windows' Function (Unused)
 LRESULT CALLBACK wWinCall(HWND Hwnd01, UINT Vrab01, WPARAM Wpar01, LPARAM Lpar01)
 {
  return DefWindowProc(Hwnd01, Vrab01, Wpar01, Lpar01);
 }
 int32   WINAPI   wWinMain(_In_ HINSTANCE Hins01, _In_opt_ HINSTANCE Hins02, _In_ LPWSTR Lpws01, _In_ int32 Vrab01)
 {
  UNREFERENCED_PARAMETER(Hins01); UNREFERENCED_PARAMETER(Lpws01);
  UNREFERENCED_PARAMETER(Hins02); UNREFERENCED_PARAMETER(Vrab01);
  if(FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED))) return 1; return 0;
 }