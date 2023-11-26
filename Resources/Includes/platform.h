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

  // Version Control
   #define _AISCRIPT_OLDVANGELSCRIPT false
   #define _AISCRIPT_NEORACOMPATIBLE false
   #define _AISCRIPT_FORDARKFIRENEXE false
   #define _AISCRIPT_MAXOBJECTNUMBER 400i32
   #define _AISCRIPT_MAXOBJECTFRAMES 400i32
   #define _AISCRIPT_MAXSTAGESIDSLOT 60i32
   #define _AISCRIPT_AISCRIPTADDRESS "ai"
   #define _AISCRIPT_DDRAWDLLVERSION string("v2.4") + string(_AISCRIPT_OLDVANGELSCRIPT ? "A" : "") + string(_AISCRIPT_NEORACOMPATIBLE ? "N" : "") + string(_AISCRIPT_FORDARKFIRENEXE ? "DF" : "")

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
  #define typedef typedef

 // Global Structure/Class
  struct AISCRIPT_VECTOR
  {
   xint64 x, y, z;

   AISCRIPT_VECTOR()
   {
    x = 0.0; y = 0.0; z = 0.0; return;
   }
   AISCRIPT_VECTOR(xint64 Vrab01, xint64 Vrab02, xint64 Vrab03)
   {
    return;
   }
  };

 // Engine's Contact
  int0 M_Starting() perfect;
  int0 M_Cleaning() perfect;

#endif
