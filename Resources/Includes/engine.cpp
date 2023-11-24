////////////////////////////////////////////////////////////////////////////////////////////
// "engine.cpp", main processor of the AI-Scripting.                                      //
//                                                                                        //
// Originally written by Doix and Som1Lse.                                                   //
// With enhancement by zort.                                                              //
////////////////////////////////////////////////////////////////////////////////////////////

// Includes
 #include "platform.h"

 #include "AngelScript/angelscript.h"
 #include "AngelScript/scriptbuilder.h"
 #include "AngelScript/scriptany.h"
 #include "AngelScript/scriptarray.h"
 #include "AngelScript/scriptmath.h"
 #include "AngelScript/scriptmathcomplex.h"
 #include "AngelScript/scriptstdstring.h"

 #include <filesystem>

// Early Declaration
 int0 M_Update(statics string) perfect;

// Global Variables
 asIScriptModule  *ScriptModule;
 asIScriptEngine  *ScriptEngine;
 asIScriptContext *ScriptContext;

 #ifdef AISCRIPT_DEBUG
  #include <map>
  std::map < int32, std::time_t > Maps0001; // Modules' Modified Time.
 #endif

// Light Functions
 int0   L_Base()                          perfect
 {
  elapsed_time = *(int32*)0x450b8c;
  difficulty = *(int32*)0x450c30;
  mode = *(int32*)0x451160;
  if(background != *(int32*)0x44d024)
  {
   background = *(int32*)0x44d024;
   bg_width = game->files->backgrounds[background].bg_width;
   bg_zwidth1 = game->files->backgrounds[background].bg_zwidth1;
   bg_zwidth2 = game->files->backgrounds[background].bg_zwidth2;
   stage_bound = bg_width;
   stage_clear = false;
  }
  if(mode == 1)
  {
   stage_bound = *(int *)0x450bb4;
   stage_clear = stage_bound == 0;
  }
  
  current_phase = *(int *)0x44fb6c;
  current_phase_count = *(int *)0x44f880;
  current_stage = *(int *)0x450b94; 
 }
 int1   L_Exist(statics string &Temp01)   perfect {struct stat Stat01; return (stat(Temp01.c_str(), &Stat01) == 0);}
 int32  L_Numbering(string Temp01)        perfect {while(Temp01.size() > 0 && Temp01.at(0) != '-' && (Temp01.at(0) < '0' || Temp01.at(0) > '9')) Temp01.erase(0, 1); uint32 Vrab01 = Temp01.size(); if(Vrab01 == 0) return 0; while(Vrab01 != 1) if(Temp01.at(Vrab01 - 1) < '0' || Temp01.at(Vrab01 - 1) > '9'){Vrab01 -= 1;} else {break;} int32 Vrab02 = 0; if(Temp01.at(0) == '-'){if(Vrab01 == 1) return 0; if(Temp01.at(1) < '0' || Temp01.at(1) > '9') return 0; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1; break; case '2': Vrab02 -= 2; break; case '3': Vrab02 -= 3; break; case '4': Vrab02 -= 4; break; case '5': Vrab02 -= 5; break; case '6': Vrab02 -= 6; break; case '7': Vrab02 -= 7; break; case '8': Vrab02 -= 8; break; case '9': Vrab02 -= 9; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10; break; case '2': Vrab02 -= 20; break; case '3': Vrab02 -= 30; break; case '4': Vrab02 -= 40; break; case '5': Vrab02 -= 50; break; case '6': Vrab02 -= 60; break; case '7': Vrab02 -= 70; break; case '8': Vrab02 -= 80; break; case '9': Vrab02 -= 90; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100; break; case '2': Vrab02 -= 200; break; case '3': Vrab02 -= 300; break; case '4': Vrab02 -= 400; break; case '5': Vrab02 -= 500; break; case '6': Vrab02 -= 600; break; case '7': Vrab02 -= 700; break; case '8': Vrab02 -= 800; break; case '9': Vrab02 -= 900; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1000; break; case '2': Vrab02 -= 2000; break; case '3': Vrab02 -= 3000; break; case '4': Vrab02 -= 4000; break; case '5': Vrab02 -= 5000; break; case '6': Vrab02 -= 6000; break; case '7': Vrab02 -= 7000; break; case '8': Vrab02 -= 8000; break; case '9': Vrab02 -= 9000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10000; break; case '2': Vrab02 -= 20000; break; case '3': Vrab02 -= 30000; break; case '4': Vrab02 -= 40000; break; case '5': Vrab02 -= 50000; break; case '6': Vrab02 -= 60000; break; case '7': Vrab02 -= 70000; break; case '8': Vrab02 -= 80000; break; case '9': Vrab02 -= 90000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000; break; case '2': Vrab02 -= 200000; break; case '3': Vrab02 -= 300000; break; case '4': Vrab02 -= 400000; break; case '5': Vrab02 -= 500000; break; case '6': Vrab02 -= 600000; break; case '7': Vrab02 -= 700000; break; case '8': Vrab02 -= 800000; break; case '9': Vrab02 -= 900000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1000000; break; case '2': Vrab02 -= 2000000; break; case '3': Vrab02 -= 3000000; break; case '4': Vrab02 -= 4000000; break; case '5': Vrab02 -= 5000000; break; case '6': Vrab02 -= 6000000; break; case '7': Vrab02 -= 7000000; break; case '8': Vrab02 -= 8000000; break; case '9': Vrab02 -= 9000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10000000; break; case '2': Vrab02 -= 20000000; break; case '3': Vrab02 -= 30000000; break; case '4': Vrab02 -= 40000000; break; case '5': Vrab02 -= 50000000; break; case '6': Vrab02 -= 60000000; break; case '7': Vrab02 -= 70000000; break; case '8': Vrab02 -= 80000000; break; case '9': Vrab02 -= 90000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000000; break; case '2': Vrab02 -= 200000000; break; case '3': Vrab02 -= 300000000; break; case '4': Vrab02 -= 400000000; break; case '5': Vrab02 -= 500000000; break; case '6': Vrab02 -= 600000000; break; case '7': Vrab02 -= 700000000; break; case '8': Vrab02 -= 800000000; break; case '9': Vrab02 -= 900000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; for(int32 Vrab03 = 10; Vrab01 > 0; Vrab03 *= 10){switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000000 * Vrab03; break; case '2': Vrab02 -= 200000000 * Vrab03; break; case '3': Vrab02 -= 300000000 * Vrab03; break; case '4': Vrab02 -= 400000000 * Vrab03; break; case '5': Vrab02 -= 500000000 * Vrab03; break; case '6': Vrab02 -= 600000000 * Vrab03; break; case '7': Vrab02 -= 700000000 * Vrab03; break; case '8': Vrab02 -= 800000000 * Vrab03; break; case '9': Vrab02 -= 900000000 * Vrab03; break; default: break;} Vrab01 -= 1;} return Vrab02;} else {Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1; break; case '2': Vrab02 += 2; break; case '3': Vrab02 += 3; break; case '4': Vrab02 += 4; break; case '5': Vrab02 += 5; break; case '6': Vrab02 += 6; break; case '7': Vrab02 += 7; break; case '8': Vrab02 += 8; break; case '9': Vrab02 += 9; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10; break; case '2': Vrab02 += 20; break; case '3': Vrab02 += 30; break; case '4': Vrab02 += 40; break; case '5': Vrab02 += 50; break; case '6': Vrab02 += 60; break; case '7': Vrab02 += 70; break; case '8': Vrab02 += 80; break; case '9': Vrab02 += 90; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100; break; case '2': Vrab02 += 200; break; case '3': Vrab02 += 300; break; case '4': Vrab02 += 400; break; case '5': Vrab02 += 500; break; case '6': Vrab02 += 600; break; case '7': Vrab02 += 700; break; case '8': Vrab02 += 800; break; case '9': Vrab02 += 900; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1000; break; case '2': Vrab02 += 2000; break; case '3': Vrab02 += 3000; break; case '4': Vrab02 += 4000; break; case '5': Vrab02 += 5000; break; case '6': Vrab02 += 6000; break; case '7': Vrab02 += 7000; break; case '8': Vrab02 += 8000; break; case '9': Vrab02 += 9000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10000; break; case '2': Vrab02 += 20000; break; case '3': Vrab02 += 30000; break; case '4': Vrab02 += 40000; break; case '5': Vrab02 += 50000; break; case '6': Vrab02 += 60000; break; case '7': Vrab02 += 70000; break; case '8': Vrab02 += 80000; break; case '9': Vrab02 += 90000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000; break; case '2': Vrab02 += 200000; break; case '3': Vrab02 += 300000; break; case '4': Vrab02 += 400000; break; case '5': Vrab02 += 500000; break; case '6': Vrab02 += 600000; break; case '7': Vrab02 += 700000; break; case '8': Vrab02 += 800000; break; case '9': Vrab02 += 900000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1000000; break; case '2': Vrab02 += 2000000; break; case '3': Vrab02 += 3000000; break; case '4': Vrab02 += 4000000; break; case '5': Vrab02 += 5000000; break; case '6': Vrab02 += 6000000; break; case '7': Vrab02 += 7000000; break; case '8': Vrab02 += 8000000; break; case '9': Vrab02 += 9000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10000000; break; case '2': Vrab02 += 20000000; break; case '3': Vrab02 += 30000000; break; case '4': Vrab02 += 40000000; break; case '5': Vrab02 += 50000000; break; case '6': Vrab02 += 60000000; break; case '7': Vrab02 += 70000000; break; case '8': Vrab02 += 80000000; break; case '9': Vrab02 += 90000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000000; break; case '2': Vrab02 += 200000000; break; case '3': Vrab02 += 300000000; break; case '4': Vrab02 += 400000000; break; case '5': Vrab02 += 500000000; break; case '6': Vrab02 += 600000000; break; case '7': Vrab02 += 700000000; break; case '8': Vrab02 += 800000000; break; case '9': Vrab02 += 900000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; for(int32 Vrab03 = 10; Vrab01 != -1; Vrab03 *= 10){switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000000 * Vrab03; break; case '2': Vrab02 += 200000000 * Vrab03; break; case '3': Vrab02 += 300000000 * Vrab03; break; case '4': Vrab02 += 400000000 * Vrab03; break; case '5': Vrab02 += 500000000 * Vrab03; break; case '6': Vrab02 += 600000000 * Vrab03; break; case '7': Vrab02 += 700000000 * Vrab03; break; case '8': Vrab02 += 800000000 * Vrab03; break; case '9': Vrab02 += 900000000 * Vrab03; break; default: break;} Vrab01 -= 1;} return Vrab02;}}
 int32  L_Rounding(statics xint64 Vrab01) perfect {statics int1 Vrab02 = Vrab01 < 0; if(rint64(Vrab01) == rint64(Vrab01 + (Vrab02 ? -0.5 : 0.5))) return rint32(Vrab01); return rint32(Vrab01) + (Vrab02 ? -1 : 1);} // Round xint64 into int32.
 string L_Lowercase(string Temp01)        perfect {insize Vrab01 = Temp01.size(); while(Vrab01 != 0){Vrab01 -= 1; if(Temp01.at(Vrab01) >= 'A' && Temp01.at(Vrab01) <= 'Z') Temp01.at(Vrab01) += 32;} return Temp01;}

// Detour Functions
 int32 (__stdcall *D_DetourID )(int32 object_num, int32 unkwn1);
 int32 (__stdcall *D_DetourEGO)(int32 target_num, int32 object_num, int32 x, int32 y, int32 z, int32 a, int32 b);
 int0  D_CallID(int32 object_num, asIScriptFunction *Function)
 {
  L_Base(); statics string Temp01 = std::to_string(0) + ".as";

  if((self = object_num) == -1)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare self.");
   #endif
  }
  if(ScriptContext->Prepare(Function) < 0)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
   #endif
   return;
  }
  if(ScriptContext->Execute() < 0)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
   #endif
   return;
  }
 }
 int32 D_CallEGO(int32 object_num, int32 target_num, asIScriptFunction *Function)
 {
  L_Base(); statics string Temp01 = std::to_string(0) + ".as";

  if((self = object_num) == -1)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare self.");
   #endif
  }
  if((target = target_num) == -1)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare target.");
   #endif
  }
  if(ScriptContext->Prepare(Function) < 0)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to prepare the context.");
   #endif
   return 0;
  }
  if(ScriptContext->Execute() < 0)
  {
   #ifdef AISCRIPT_DEBUG
    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to execute the context.");
   #endif
   return 0;
  }
  
  return ScriptContext->GetReturnDWord();
 }
 int0  __stdcall D_ID(int32 object_num, int32 unkwn1)
 {
  DWORD unkwn2;
  
  _asm
  {
   mov dword ptr ds:[unkwn2], ecx;
  }

  int32 id_int = game->objects[object_num]->data->id;
  std::string fileName = std::to_string(id_int) + ".as";

  #ifdef AISCRIPT_DEBUG
   M_Update(id_int, fileName);
  #endif

  ScriptModule = ScriptEngine->GetModule(std::to_string(id_int).c_str());
  if(ScriptModule)
  {
   asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("void id()");
   if(Function){D_CallID(object_num, Function); return;}
   #ifdef AISCRIPT_DEBUG
    else
    {
     if(!ScriptModule->GetFunctionByDecl("int ego()"))
     {
      ScriptEngine->WriteMessage(fileName.c_str(), 0, 0, asMSGTYPE_ERROR, "Neither 'void id()' nor 'int ego()' are defined.");
     }
    }
   #endif
  }

  _asm
  {
   mov ecx, dword ptr ds:[unkwn1];
   push ecx;
   mov ecx, dword ptr ds:[object_num];
   push ecx;
   mov ecx, dword ptr ds:[unkwn2];
   call D_DetourID;
  }
 }
 int32 __stdcall D_EGO(int32 target_num, int32 object_num, int32 unkwn1, int32 unkwn2, int32 unkwn3, int32 unkwn4, int32 unkwn5)
 {
  DWORD return_value;
  DWORD unkwn6;
  
  __asm
  {
   mov dword ptr ds:[unkwn6], ecx;
  }

  ScriptModule = ScriptEngine->GetModule(std::to_string(game->objects[object_num]->data->id).c_str());
  if(ScriptModule)
  {
   asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("int ego()");
   if(Function) return D_CallEGO(object_num, target_num, Function);
  }

  __asm
  {
   mov ecx, dword ptr ds:[unkwn5];
   push ecx;
   mov ecx, dword ptr ds:[unkwn4];
   push ecx;
   mov ecx, dword ptr ds:[unkwn3];
   push ecx;
   mov ecx, dword ptr ds:[unkwn2];
   push ecx;
   mov ecx, dword ptr ds:[unkwn1];
   push ecx;
   mov ecx, dword ptr ds:[object_num];
   push ecx;
   mov ecx, dword ptr ds:[target_num];
   push ecx;
   mov ecx, dword ptr ds:[unkwn6];
   call D_DetourEGO;
   mov dword ptr ds:[return_value], eax;
  }
  
  return return_value;
 }

// Main Functions
 #ifdef AISCRIPT_DEBUG
  int0 M_Message(statics asSMessageInfo *Amsg01, int0*) perfect
  {
   if(Amsg01->section[0] == '\0')
   {
    printf("%s: %s\n", Amsg01->type == asMSGTYPE_ERROR ? ("ERROR") : (Amsg01->type == asMSGTYPE_WARNING ? "WARNING" : "INFO"), Amsg01->message);
   } else if(Amsg01->row == 0 && Amsg01->col == 0)
   {
    printf("%s: %s : %s\n", Amsg01->section, Amsg01->type == asMSGTYPE_ERROR ? ("ERROR") : (Amsg01->type == asMSGTYPE_WARNING ? "WARNING" : "INFO"), Amsg01->message);
   } else
   {
    printf("%s(%d, %d): %s : %s\n", Amsg01->section, Amsg01->row, Amsg01->col, Amsg01->type == asMSGTYPE_ERROR ? ("ERROR") : (Amsg01->type == asMSGTYPE_WARNING ? "WARNING" : "INFO"), Amsg01->message);
   }
  }
  int0 M_Update(statics int32 Vrab01, statics string Temp01) perfect
  {
   std::time_t Time01 = 0; struct stat Stat01; if(L_Exist(Temp01)) if(stat(Temp01.c_str(), &Stat01) == 0) Time01 = Stat01.st_mtime;
   if(Maps0001.count(Vrab01))
   {
    if(Maps0001[Vrab01] < Time01)
    {
	 CScriptBuilder Builder;
     Builder.DefineWord("debug");

     if(Temp01.at(0) == '_')
     {Builder.DefineWord("module");} else {Builder.DefineWord("character");}

     ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
     Builder.StartNewModule(ScriptEngine, string(Temp01, 0, Temp01.size() - 3).c_str());

     if(Builder.AddSectionFromFile(Temp01.c_str()) < 0)
     {
      ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
      ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
      return;
     }
     if(Builder.BuildModule() < 0)
     {
      ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
      ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
      return;
     }
    }
   } else
   {
	Maps0001.insert(std::pair < int32 , std::time_t > (Vrab01, Time01));
    CScriptBuilder Builder;
    Builder.DefineWord("debug");

    if(Temp01.at(0) == '_')
    {Builder.DefineWord("module");} else {Builder.DefineWord("character");}

    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
    Builder.StartNewModule(ScriptEngine, string(Temp01, 0, Temp01.size() - 3).c_str());

    if(Builder.AddSectionFromFile(Temp01.c_str()) < 0)
    {
     ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
     ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
     return;
    }
    if(Builder.BuildModule() < 0)
    {
     ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
     ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
     return;
    }
   }
  }
 #endif

 int0 M_Functions(int1 Vrab01) perfect
 {
  
 }
 int0 M_Starting() perfect
 {
  #ifdef AISCRIPT_DEBUG
   AllocConsole();
   freopen("CONIN$", "rb", stdin);   // Reopen stdin handle as console window input.
   freopen("CONOUT$", "wb", stdout); // Reopen stout handle as console window output.
   freopen("CONOUT$", "wb", stderr); // Reopen stderr handle as console window output.
  #endif

  ScriptModule = NULL;
  ScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  if(!ScriptEngine) ExitProcess(0);

  #ifdef AISCRIPT_DEBUG
   ScriptEngine->SetMessageCallback(asFUNCTION(M_Message), NULL, asCALL_CDECL);
  #endif

  ScriptContext = ScriptEngine->CreateContext();
  M_Functions(false);
  
  D_DetourID  = (int32 (__stdcall *)(int32, int32))DetourFunction((PBYTE)0x004094b0, (PBYTE)D_ID);
  D_DetourEGO = (int32 (__stdcall *)(int32, int32, int32, int32, int32, int32, int32))DetourFunction((PBYTE)0x00403a40, (PBYTE)D_EGO);

  statics string Temp01 = "ai";
  for(auto statics &Temp02 : std::filesystem::directory_iterator(Temp01))
  {
   statics string Temp03 = Temp02.path().string(); if(Temp03.size() < Temp01.size() + 5) continue;
   statics string Temp04 = L_Lowercase(string(Temp03, Temp01.size() + 1, Temp03.size() - (Temp01.size() + 1)));

   if(string(Temp04, Temp04.size() - 3, 3) != ".as") continue;
   if(Temp04.at(0) == '_') goto Labl01;
   if(Temp04.at(0) == '0') if(Temp04 != "0.as") continue;
   {
    uint32 Vrab01 = Temp04.size() - 3; int1 Vrab02 = true;
    while(Vrab01 > 0){Vrab01 -= 1; if(Temp04.at(Vrab01) < '0' || Temp04.at(Vrab01) > '9' ){Vrab02 = false; break;}}
    if(Vrab02) goto Labl02;
   }
   continue;
   Labl01: // Module.
   {
   
   }
   continue;
   Labl02: // AI-Script.
   {
    #ifdef AISCRIPT_DEBUG
	 std::time_t Time01 = 0; struct stat Stat01; if(stat(Temp03.c_str(), &Stat01) == 0) Time01 = Stat01.st_mtime;
     Maps0001.insert(std::pair < int32, std::time_t > (L_Numbering(string(Temp04, 0, Temp04.size() - 3)), Time01));
    #endif
     
	CScriptBuilder Builder;
	#ifdef AISCRIPT_DEBUG
	 Builder.DefineWord("debug");
     ScriptEngine->WriteMessage(Temp04.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Building.");
	#else
	 Builder.DefineWord("release");
	#endif

    Builder.DefineWord("character");	
    Builder.StartNewModule(ScriptEngine, string(Temp04, 0, Temp04.size() - 3).c_str());
    if(Builder.AddSectionFromFile(Temp03.c_str()) < 0)
    {
	 #ifdef AISCRIPT_DEBUG
	  ScriptEngine->WriteMessage(Temp04.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
	 #endif
     ScriptEngine->DiscardModule(string(Temp04, 0, Temp04.size() - 3).c_str());
	 continue;
    }
    if(Builder.BuildModule() < 0)
    {
     #ifdef AISCRIPT_DEBUG
      ScriptEngine->WriteMessage(Temp04.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
     #endif
     ScriptEngine->DiscardModule(string(Temp04, 0, Temp04.size() - 3).c_str());
     continue;
    }
	#ifdef AISCRIPT_DEBUG
     ScriptEngine->WriteMessage(Temp04.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Successfully build.");
	#endif
   }
   continue;
  }
 }
 int0 M_Cleaning() perfect
 {
  if(ScriptContext) ScriptContext->Release();
  if(ScriptEngine) ScriptEngine->Release();
 }