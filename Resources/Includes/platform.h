////////////////////////////////////////////////////////////////////////////////////////////
// "platform.h", main header for the entire DirectDraw.                                   //
//                                                                                        //
// No comment.                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _AISCRIPT_PRAGMA_PLATFORM_H
 #define _AISCRIPT_PRAGMA_PLATFORM_H
 
 // Commands
  #define NOMINMAX   // Use the C++ standard templated min/max.
  #define NODRAWTEXT // No need for GDI.
  #define NOBITMAP   // No need for GDI.
  #define NOMCX      // Include <mcx.h> if you need this.
  #define NOSERVICE  // Include <winsvc.h> if you need this.
  #define NOHELP     // WinHelp is deprecated.
  #define WIN32_LEAN_AND_MEAN

  #include <windows.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <tchar.h>
  #include <fstream>
  #include <sstream>
  #include <vector>
  #include <format>

  #include "DirectDraw\ddraw.h"
  #include "DirectDraw\myIDDraw.h"
  #include "Detours\detours.h"

  using int0   = void;               // -
  using int1   = bool;               // I know, it's not 1 byte.
  using int8   = char;               // -
  using int16  = short;              // -
  using int32  = int;                // -
  using int64  = long long;          // -
  using sint8  = signed char;        // -
  using sint16 = signed short;       // -
  using sint32 = signed int;         // -
  using sint64 = signed long long;   // -
  using lint32 = long;               // -
  using uint8  = unsigned char;      // -
  using uint16 = unsigned short;     // -
  using uint32 = unsigned int;       // -
  using uint64 = unsigned long long; // -
  using xint32 = float;              // -
  using xint64 = double;             // -
  using string = std::string;        // -
  using stream = std::stringstream;  // -
  using insize = size_t;             // Vector's maximum size.

  #define unique std::unique_ptr

  #define rint1   static_cast < int1 >
  #define rint8   static_cast < int8 >
  #define rint16  static_cast < int16 >
  #define rint32  static_cast < int32 >
  #define rint64  static_cast < int64 >
  #define rsint8  static_cast < sint8 >
  #define rsint16 static_cast < sint16 >
  #define rsint32 static_cast < sint32 >
  #define rsint64 static_cast < sint64 >
  #define ruint8  static_cast < uint8 >
  #define ruint16 static_cast < uint16 >
  #define ruint32 static_cast < uint32 >
  #define ruint64 static_cast < uint64 >
  #define rxint32 static_cast < xint32 >
  #define rxint64 static_cast < xint64 >
  #define rinsize static_cast < insize >

  #define remains static
  #define written constexpr
  #define statics const
  #define univers virtual
  #define stacked inline
  #define perfect noexcept

 // Global Function
  int0 G_Error(HRESULT Hres01, statics string Temp01 = "") perfect
  {
   if(SUCCEEDED(Hres01)) return;
   if(FACILITY_WINDOWS == HRESULT_FACILITY(Hres01)) Hres01 = HRESULT_CODE(Hres01);
   
   string Temp02 = "Exception Occur, Error Code : 0x" + std::format("{:X}", ruint32(Hres01)); if(Temp01 != "") Temp02 += " (" + Temp01 + ")";
   statics std::wstring Temp03 = L"\n\nWould be helpful if you would inform the developer.";

   TCHAR* Temp04; std::wstring Temp05;
   if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, Hres01, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&Temp04, 0, NULL) != 0) 
   {Temp05 = std::wstring(Temp04); Temp05.pop_back(); Temp05.pop_back(); Temp05 = std::wstring(Temp02.begin(), Temp02.end()) + L"\n\"" + Temp05 + L".\"" + Temp03;} else 
   {Temp05 = std::wstring(Temp02.begin(), Temp02.end()) + Temp03;}
   
   MessageBox(NULL, Temp05.c_str(), L"Platform Error", MB_OK | MB_ICONERROR);
   exit(0);
  }

 // Engine's Contact
  int0 M_Starting() perfect;
  int0 M_Cleaning() perfect;

#endif
