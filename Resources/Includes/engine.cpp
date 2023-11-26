////////////////////////////////////////////////////////////////////////////////////////////
// "engine.cpp", main processor of the AI-Scripting.                                      //
//                                                                                        //
// Originally written by Doix and Som1Lse.                                                //
// With enhancement by zort.                                                              //
////////////////////////////////////////////////////////////////////////////////////////////

// Includes
 #include "platform.h"
 #include "game.h"

 #include "AngelScript/angelscript.h"
 #include "AngelScript/scriptbuilder.h"
 #include "AngelScript/scriptany.h"
 #include "AngelScript/scriptarray.h"
 #include "AngelScript/scriptmath.h"
 #include "AngelScript/scriptmathcomplex.h"
 #include "AngelScript/scriptstdstring.h"

 #include <filesystem>

// Early Declaration
 int0 M_Update(statics int32, statics string) perfect;

// Global Variables
 int1   full_script = false;
 int32  mode;
 int32  difficulty;
 int32  elapsed_time;
 int32  background = -1;
 int32  bg_width;
 int32  bg_zwidth1;
 int32  bg_zwidth2;
 int32  stage_bound;
 int32  current_phase;
 int32  current_phase_count;
 int32  current_stage;
 int8   stage_clear;
 int8   key_load[7];
 int8   key_last[_AISCRIPT_MAXOBJECTNUMBER][7];
 int32  max_frames = _AISCRIPT_MAXOBJECTFRAMES;
 int32  max_objnum = _AISCRIPT_MAXOBJECTNUMBER;
 string version = _AISCRIPT_DDRAWDLLVERSION;
 AISCRIPT_GAME *game = (AISCRIPT_GAME*)0x458b00;
 AISCRIPT_INFO self;
 AISCRIPT_INFO target;
 asIScriptModule  *ScriptModule;
 asIScriptEngine  *ScriptEngine;
 asIScriptContext *ScriptContext;

 #if _AISCRIPT_NEORACOMPATIBLE
  AISCRIPT_GAMEPTR *gamePtr = (AISCRIPT_GAMEPTR*)0x458b00;
 #endif

 #ifdef AISCRIPT_DEBUG
  #include <map>
  std::map < int32, std::time_t > Maps0001; // Modules' Modified Time.
 #endif

// Structure/Class Functions Declaration
 AISCRIPT_INFO *Info_Factory(){return new AISCRIPT_INFO();}
 AISCRIPT_INFO *Info_Factory(int32 object_num){return new AISCRIPT_INFO(object_num);}
 AISCRIPT_INFO *Info_Factory(statics AISCRIPT_INFO &info){return new AISCRIPT_INFO(info);}
 int32 AISCRIPT_INFO::operator=(int32 object_num)
 {
  if(object_num < 0 || object_num >= _AISCRIPT_MAXOBJECTNUMBER) return -1;
  if(!game->exists[object_num]) return -1;
  
  num  = object_num;
  id   = game->objects[object_num]->data->id;
  type = game->objects[object_num]->data->type;

  x = game->objects[object_num]->x;
  y = game->objects[object_num]->y;
  z = game->objects[object_num]->z;
  x_real = game->objects[object_num]->x_real;
  y_real = game->objects[object_num]->y_real;
  z_real = game->objects[object_num]->z_real;
  x_velocity = game->objects[object_num]->x_velocity;
  y_velocity = game->objects[object_num]->y_velocity;
  z_velocity = game->objects[object_num]->z_velocity;

  facing = game->objects[object_num]->facing;
  
  holding_up    = game->objects[object_num]->holding_up;
  holding_left  = game->objects[object_num]->holding_left;
  holding_down  = game->objects[object_num]->holding_down;
  holding_right = game->objects[object_num]->holding_right;
  holding_a     = game->objects[object_num]->holding_a;
  holding_d     = game->objects[object_num]->holding_d;
  holding_j     = game->objects[object_num]->holding_j;
  up    = game->objects[object_num]->up;
  left  = game->objects[object_num]->left;
  down  = game->objects[object_num]->down;
  right = game->objects[object_num]->right;
  A = game->objects[object_num]->A;
  D = game->objects[object_num]->D;
  J = game->objects[object_num]->J;
  
  DrA = game->objects[object_num]->DrA;
  DlA = game->objects[object_num]->DlA;
  DuA = game->objects[object_num]->DuA;
  DdA = game->objects[object_num]->DdA;
  DrJ = game->objects[object_num]->DrJ;
  DlJ = game->objects[object_num]->DlJ;
  DuJ = game->objects[object_num]->DuJ;
  DdJ = game->objects[object_num]->DdJ;
  DJA = game->objects[object_num]->DJA;
  
  hp      = game->objects[object_num]->hp;
  dark_hp = game->objects[object_num]->dark_hp;
  max_hp  = game->objects[object_num]->max_hp;
  mp      = game->objects[object_num]->mp;
  
  frame   = game->objects[object_num]->frame1;
  fall    = game->objects[object_num]->fall;
  bdefend = game->objects[object_num]->bdefend;
  team    = game->objects[object_num]->team;
  blink   = game->objects[object_num]->blink;
  state   = game->objects[object_num]->data->frames[frame].state;

  weapon_type   = game->objects[object_num]->weapon_type;
  weapon_holder = game->objects[object_num]->weapon_holder;
  if(weapon_type == 0){weapon_held = -1;} else {weapon_held = game->objects[object_num]->weapon_held;}

  shake        = game->objects[object_num]->shake;
  wait_counter = game->objects[object_num]->wait_counter;
  ctimer       = game->objects[object_num]->ctimer;
  arest        = game->objects[object_num]->arest;
  memcpy(vrests, game->objects[object_num]->vrests, _AISCRIPT_MAXOBJECTNUMBER);

  vrest    = (int32)(*(int8*)(*(int32*)(0x458c94 + object_num * 4) + 0xF0));
  if(vrest < (int32)(*(int8*)(*(int32*)(0x458c94 + object_num * 4) + 0xF3))) vrest = (int32)(*(int8*)(*(int32*)(0x458c94 + object_num * 4) + 0xF3));

  clone   = game->objects[object_num]->clone;
  reserve = game->objects[object_num]->reserve;
  data    = game->objects[object_num]->data;

  position = AISCRIPT_VECTOR(x_real, y_real, z_real);
  velocity = AISCRIPT_VECTOR(x_velocity, y_velocity, z_velocity);

  return type;
 }

// Light Functions
 int0   L_Base(int32 Vrab01, int1 Vrab02 = true) perfect
 {
  elapsed_time = *(int32*)0x450b8c;
  difficulty   = *(int32*)0x450c30;
  mode         = *(int32*)0x451160;
  if(background != *(int32*)0x44d024)
  {
   background  = *(int32*)0x44d024;
   bg_width    = game->files->backgrounds[background].bg_width;
   bg_zwidth1  = game->files->backgrounds[background].bg_zwidth1;
   bg_zwidth2  = game->files->backgrounds[background].bg_zwidth2;
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

  if(Vrab01 < 0 || Vrab01 >= _AISCRIPT_MAXOBJECTNUMBER) return;
  if(!game->exists[Vrab01]) return;
  
  key_load[0] = 0;
  key_load[1] = 0;
  key_load[2] = 0;
  key_load[3] = 0;
  key_load[4] = 0;
  key_load[5] = 0;
  key_load[6] = 0;

  if(Vrab02)
  {
   remains uint32 Vrab03[_AISCRIPT_MAXOBJECTNUMBER];
   if(Vrab03[Vrab01] == elapsed_time - 1)
   {
    key_load[0] = key_last[Vrab01][0];
    key_load[1] = key_last[Vrab01][1];
    key_load[2] = key_last[Vrab01][2];
    key_load[3] = key_last[Vrab01][3];
    key_load[4] = key_last[Vrab01][4];
    key_load[5] = key_last[Vrab01][5];
    key_load[6] = key_last[Vrab01][6];
   }

   Vrab03[Vrab01] = elapsed_time;
   return;
  }
  
  if(game->objects[Vrab01]->holding_up != 0){key_load[0] = 2;} else
  {if(game->objects[Vrab01]->up != 0){key_load[0] = 1; game->objects[Vrab01]->up = 0; game->objects[Vrab01]->holding_up = 1;}}
  if(game->objects[Vrab01]->holding_left != 0){key_load[1] = 2;} else
  {if(game->objects[Vrab01]->left != 0){key_load[1] = 1; game->objects[Vrab01]->left = 0; game->objects[Vrab01]->holding_left = 1;}}
  if(game->objects[Vrab01]->holding_down != 0){key_load[2] = 2;} else
  {if(game->objects[Vrab01]->down != 0){key_load[2] = 1; game->objects[Vrab01]->down = 0; game->objects[Vrab01]->holding_down = 1;}}
  if(game->objects[Vrab01]->holding_right != 0){key_load[3] = 2;} else
  {if(game->objects[Vrab01]->right != 0){key_load[3] = 1; game->objects[Vrab01]->right = 0; game->objects[Vrab01]->holding_right = 1;}}
  if(game->objects[Vrab01]->holding_a != 0){key_load[4] = 2;} else
  {if(game->objects[Vrab01]->A != 0){key_load[4] = 1; game->objects[Vrab01]->A = 0; game->objects[Vrab01]->holding_a = 1;}}
  if(game->objects[Vrab01]->holding_d != 0){key_load[5] = 2;} else
  {if(game->objects[Vrab01]->D != 0){key_load[5] = 1; game->objects[Vrab01]->D = 0; game->objects[Vrab01]->holding_d = 1;}}
  if(game->objects[Vrab01]->holding_j != 0){key_load[6] = 2;} else
  {if(game->objects[Vrab01]->J != 0){key_load[6] = 1; game->objects[Vrab01]->J = 0; game->objects[Vrab01]->holding_j = 1;}}
 }
 int0   L_Keeping(int32 Vrab01)           perfect
 {
  if(Vrab01 < 0 || Vrab01 >= _AISCRIPT_MAXOBJECTNUMBER) return;
  if(!game->exists[Vrab01]) return;
 
  if(game->objects[Vrab01]->up != 0) key_last[Vrab01][0] = 1;
  if(game->objects[Vrab01]->holding_up != 0) key_last[Vrab01][0] = 2;
  if(game->objects[Vrab01]->left != 0) key_last[Vrab01][1] = 1;
  if(game->objects[Vrab01]->holding_left != 0) key_last[Vrab01][1] = 2;
  if(game->objects[Vrab01]->down != 0) key_last[Vrab01][2] = 1;
  if(game->objects[Vrab01]->holding_down != 0) key_last[Vrab01][2] = 2;
  if(game->objects[Vrab01]->right != 0) key_last[Vrab01][3] = 1;
  if(game->objects[Vrab01]->holding_right != 0) key_last[Vrab01][3] = 2;
  if(game->objects[Vrab01]->A != 0) key_last[Vrab01][4] = 1;
  if(game->objects[Vrab01]->holding_a != 0) key_last[Vrab01][4] = 2;
  if(game->objects[Vrab01]->D != 0) key_last[Vrab01][5] = 1;
  if(game->objects[Vrab01]->holding_d != 0) key_last[Vrab01][5] = 2;
  if(game->objects[Vrab01]->J != 0) key_last[Vrab01][6] = 1;
  if(game->objects[Vrab01]->holding_j != 0) key_last[Vrab01][6] = 2;
 }
 int0   L_Empty()                         perfect 
 {
  game->objects[self.num]->up = 0; self.up = 0;
  game->objects[self.num]->holding_up = 0; self.holding_up = 0;
  game->objects[self.num]->left = 0; self.left = 0;
  game->objects[self.num]->holding_left = 0; self.holding_left = 0;
  game->objects[self.num]->down = 0; self.down = 0;
  game->objects[self.num]->holding_down = 0; self.holding_down = 0;
  game->objects[self.num]->right = 0; self.right = 0;
  game->objects[self.num]->holding_right = 0; self.holding_right = 0;
  game->objects[self.num]->A = 0; self.A = 0;
  game->objects[self.num]->holding_a = 0; self.holding_a = 0;
  game->objects[self.num]->D = 0; self.D = 0;
  game->objects[self.num]->holding_d = 0; self.holding_d = 0;
  game->objects[self.num]->J = 0; self.J = 0;
  game->objects[self.num]->holding_j = 0; self.holding_j = 0;
 }
 int1   L_Exist(statics string &Temp01)   perfect {struct stat Stat01; return (stat(Temp01.c_str(), &Stat01) == 0);}
 int32  L_Numbering(string Temp01)        perfect {while(Temp01.size() > 0 && Temp01.at(0) != '-' && (Temp01.at(0) < '0' || Temp01.at(0) > '9')) Temp01.erase(0, 1); uint32 Vrab01 = Temp01.size(); if(Vrab01 == 0) return 0; while(Vrab01 != 1) if(Temp01.at(Vrab01 - 1) < '0' || Temp01.at(Vrab01 - 1) > '9'){Vrab01 -= 1;} else {break;} int32 Vrab02 = 0; if(Temp01.at(0) == '-'){if(Vrab01 == 1) return 0; if(Temp01.at(1) < '0' || Temp01.at(1) > '9') return 0; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1; break; case '2': Vrab02 -= 2; break; case '3': Vrab02 -= 3; break; case '4': Vrab02 -= 4; break; case '5': Vrab02 -= 5; break; case '6': Vrab02 -= 6; break; case '7': Vrab02 -= 7; break; case '8': Vrab02 -= 8; break; case '9': Vrab02 -= 9; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10; break; case '2': Vrab02 -= 20; break; case '3': Vrab02 -= 30; break; case '4': Vrab02 -= 40; break; case '5': Vrab02 -= 50; break; case '6': Vrab02 -= 60; break; case '7': Vrab02 -= 70; break; case '8': Vrab02 -= 80; break; case '9': Vrab02 -= 90; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100; break; case '2': Vrab02 -= 200; break; case '3': Vrab02 -= 300; break; case '4': Vrab02 -= 400; break; case '5': Vrab02 -= 500; break; case '6': Vrab02 -= 600; break; case '7': Vrab02 -= 700; break; case '8': Vrab02 -= 800; break; case '9': Vrab02 -= 900; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1000; break; case '2': Vrab02 -= 2000; break; case '3': Vrab02 -= 3000; break; case '4': Vrab02 -= 4000; break; case '5': Vrab02 -= 5000; break; case '6': Vrab02 -= 6000; break; case '7': Vrab02 -= 7000; break; case '8': Vrab02 -= 8000; break; case '9': Vrab02 -= 9000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10000; break; case '2': Vrab02 -= 20000; break; case '3': Vrab02 -= 30000; break; case '4': Vrab02 -= 40000; break; case '5': Vrab02 -= 50000; break; case '6': Vrab02 -= 60000; break; case '7': Vrab02 -= 70000; break; case '8': Vrab02 -= 80000; break; case '9': Vrab02 -= 90000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000; break; case '2': Vrab02 -= 200000; break; case '3': Vrab02 -= 300000; break; case '4': Vrab02 -= 400000; break; case '5': Vrab02 -= 500000; break; case '6': Vrab02 -= 600000; break; case '7': Vrab02 -= 700000; break; case '8': Vrab02 -= 800000; break; case '9': Vrab02 -= 900000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 1000000; break; case '2': Vrab02 -= 2000000; break; case '3': Vrab02 -= 3000000; break; case '4': Vrab02 -= 4000000; break; case '5': Vrab02 -= 5000000; break; case '6': Vrab02 -= 6000000; break; case '7': Vrab02 -= 7000000; break; case '8': Vrab02 -= 8000000; break; case '9': Vrab02 -= 9000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 10000000; break; case '2': Vrab02 -= 20000000; break; case '3': Vrab02 -= 30000000; break; case '4': Vrab02 -= 40000000; break; case '5': Vrab02 -= 50000000; break; case '6': Vrab02 -= 60000000; break; case '7': Vrab02 -= 70000000; break; case '8': Vrab02 -= 80000000; break; case '9': Vrab02 -= 90000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000000; break; case '2': Vrab02 -= 200000000; break; case '3': Vrab02 -= 300000000; break; case '4': Vrab02 -= 400000000; break; case '5': Vrab02 -= 500000000; break; case '6': Vrab02 -= 600000000; break; case '7': Vrab02 -= 700000000; break; case '8': Vrab02 -= 800000000; break; case '9': Vrab02 -= 900000000; break; default: break;} Vrab01 -= 1; if(Vrab01 == 0) return Vrab02; for(int32 Vrab03 = 10; Vrab01 > 0; Vrab03 *= 10){switch(Temp01.at(Vrab01)){case '1': Vrab02 -= 100000000 * Vrab03; break; case '2': Vrab02 -= 200000000 * Vrab03; break; case '3': Vrab02 -= 300000000 * Vrab03; break; case '4': Vrab02 -= 400000000 * Vrab03; break; case '5': Vrab02 -= 500000000 * Vrab03; break; case '6': Vrab02 -= 600000000 * Vrab03; break; case '7': Vrab02 -= 700000000 * Vrab03; break; case '8': Vrab02 -= 800000000 * Vrab03; break; case '9': Vrab02 -= 900000000 * Vrab03; break; default: break;} Vrab01 -= 1;} return Vrab02;} else {Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1; break; case '2': Vrab02 += 2; break; case '3': Vrab02 += 3; break; case '4': Vrab02 += 4; break; case '5': Vrab02 += 5; break; case '6': Vrab02 += 6; break; case '7': Vrab02 += 7; break; case '8': Vrab02 += 8; break; case '9': Vrab02 += 9; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10; break; case '2': Vrab02 += 20; break; case '3': Vrab02 += 30; break; case '4': Vrab02 += 40; break; case '5': Vrab02 += 50; break; case '6': Vrab02 += 60; break; case '7': Vrab02 += 70; break; case '8': Vrab02 += 80; break; case '9': Vrab02 += 90; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100; break; case '2': Vrab02 += 200; break; case '3': Vrab02 += 300; break; case '4': Vrab02 += 400; break; case '5': Vrab02 += 500; break; case '6': Vrab02 += 600; break; case '7': Vrab02 += 700; break; case '8': Vrab02 += 800; break; case '9': Vrab02 += 900; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1000; break; case '2': Vrab02 += 2000; break; case '3': Vrab02 += 3000; break; case '4': Vrab02 += 4000; break; case '5': Vrab02 += 5000; break; case '6': Vrab02 += 6000; break; case '7': Vrab02 += 7000; break; case '8': Vrab02 += 8000; break; case '9': Vrab02 += 9000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10000; break; case '2': Vrab02 += 20000; break; case '3': Vrab02 += 30000; break; case '4': Vrab02 += 40000; break; case '5': Vrab02 += 50000; break; case '6': Vrab02 += 60000; break; case '7': Vrab02 += 70000; break; case '8': Vrab02 += 80000; break; case '9': Vrab02 += 90000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000; break; case '2': Vrab02 += 200000; break; case '3': Vrab02 += 300000; break; case '4': Vrab02 += 400000; break; case '5': Vrab02 += 500000; break; case '6': Vrab02 += 600000; break; case '7': Vrab02 += 700000; break; case '8': Vrab02 += 800000; break; case '9': Vrab02 += 900000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 1000000; break; case '2': Vrab02 += 2000000; break; case '3': Vrab02 += 3000000; break; case '4': Vrab02 += 4000000; break; case '5': Vrab02 += 5000000; break; case '6': Vrab02 += 6000000; break; case '7': Vrab02 += 7000000; break; case '8': Vrab02 += 8000000; break; case '9': Vrab02 += 9000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 10000000; break; case '2': Vrab02 += 20000000; break; case '3': Vrab02 += 30000000; break; case '4': Vrab02 += 40000000; break; case '5': Vrab02 += 50000000; break; case '6': Vrab02 += 60000000; break; case '7': Vrab02 += 70000000; break; case '8': Vrab02 += 80000000; break; case '9': Vrab02 += 90000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000000; break; case '2': Vrab02 += 200000000; break; case '3': Vrab02 += 300000000; break; case '4': Vrab02 += 400000000; break; case '5': Vrab02 += 500000000; break; case '6': Vrab02 += 600000000; break; case '7': Vrab02 += 700000000; break; case '8': Vrab02 += 800000000; break; case '9': Vrab02 += 900000000; break; default: break;} if(Vrab01 == 0) return Vrab02; Vrab01 -= 1; for(int32 Vrab03 = 10; Vrab01 != -1; Vrab03 *= 10){switch(Temp01.at(Vrab01)){case '1': Vrab02 += 100000000 * Vrab03; break; case '2': Vrab02 += 200000000 * Vrab03; break; case '3': Vrab02 += 300000000 * Vrab03; break; case '4': Vrab02 += 400000000 * Vrab03; break; case '5': Vrab02 += 500000000 * Vrab03; break; case '6': Vrab02 += 600000000 * Vrab03; break; case '7': Vrab02 += 700000000 * Vrab03; break; case '8': Vrab02 += 800000000 * Vrab03; break; case '9': Vrab02 += 900000000 * Vrab03; break; default: break;} Vrab01 -= 1;} return Vrab02;}}
 int32  L_Rounding(statics xint64 Vrab01) perfect {statics int1 Vrab02 = Vrab01 < 0; if(rint64(Vrab01) == rint64(Vrab01 + (Vrab02 ? -0.5 : 0.5))) return rint32(Vrab01); return rint32(Vrab01) + (Vrab02 ? -1 : 1);} // Round xint64 into int32.
 string L_Lowercase(string Temp01)        perfect {insize Vrab01 = Temp01.size(); while(Vrab01 != 0){Vrab01 -= 1; if(Temp01.at(Vrab01) >= 'A' && Temp01.at(Vrab01) <= 'Z') Temp01.at(Vrab01) += 32;} return Temp01;}

// Shared Functions
 int0  clr() perfect
 {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  if(hConsole == INVALID_HANDLE_VALUE) return;
  COORD coordScreen = {0, 0};
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;
  if(!GetConsoleScreenBufferInfo(hConsole, &csbi)){return;}
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  if(!FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten)){return;}
  if(!GetConsoleScreenBufferInfo(hConsole, &csbi)){return;}
  if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)){return;}
  SetConsoleCursorPosition(hConsole, coordScreen);
 }
 int0  printAddr(int0 *Addr){printf("%p", Addr);}
 int0  print(int1 p)  {printf(p ? "true" : "false");}
 int0  print(int8 p)  {printf("%d", p);}
 int0  print(int16 p) {printf("%d", p);}
 int0  print(int32 p) {printf("%d", p);}
 int0  print(int64 p) {printf("%lld", p);}
 int0  print(uint8 p) {printf("%u", p);}
 int0  print(uint16 p){printf("%u", p);}
 int0  print(uint32 p){printf("%u", p);}
 int0  print(uint64 p){printf("%llu", p);}
 int0  print(xint32 p){printf("%f", p);}
 int0  print(xint64 p){printf("%Lf", p);}
 int0  print(statics string &p){printf("%s", p.c_str());}
 int32 random(int32 Vrab01) perfect //random function that works with replays
 {
  int32  Vrab02 = 0;  // eax@2
  sint32 Vrab03 = 0; // eax@3
  DWORD  &Dwrd01 = *((DWORD*)0x450C34);
  DWORD  &Dwrd02 = *((DWORD*)0x450BCC);
  if(Vrab01 > 0)
  {
   Dwrd01 = (Dwrd01 + 1) % 1234;
   Vrab03 = Dwrd01 + (unsigned __int8)*(((BYTE*)0x44FF90) + (Dwrd02 + 1) % 3000);
   Dwrd02 = (Dwrd02 + 1) % 3000;
   Vrab02 = Vrab03 % Vrab01;
  } else {Vrab02 = 0;}
  return Vrab02;
 }
 int32 loadTarget(int32 target_num){return target = target_num;}
 int32 setEnemy(int32 object_num){if(object_num < 0 || object_num >= _AISCRIPT_MAXOBJECTNUMBER) return -1; if(!game->exists[object_num]) return -1; return game->objects[self.num]->enemy = object_num;}
 
 int0  up(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[0] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[0] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->up = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_up = Vrab02 ? 1 : 0;
  self.up = Vrab01 ? 1 : 0; self.holding_up = Vrab02 ? 1 : 0;
 }
 int0  left(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[1] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[1] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->left = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_left = Vrab02 ? 1 : 0;
  self.left = Vrab01 ? 1 : 0; self.holding_left = Vrab02 ? 1 : 0;
 }
 int0  down(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[2] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[2] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->down = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_down = Vrab02 ? 1 : 0;
  self.down = Vrab01 ? 1 : 0; self.holding_down = Vrab02 ? 1 : 0;
 }
 int0  right(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[3] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[3] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->right = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_right = Vrab02 ? 1 : 0;
  self.right = Vrab01 ? 1 : 0; self.holding_right = Vrab02 ? 1 : 0;
 }
 int0  A(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[4] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[4] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->A = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_a = Vrab02 ? 1 : 0;
  self.A = Vrab01 ? 1 : 0; self.holding_a = Vrab02 ? 1 : 0;
 }
 int0  D(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[5] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[5] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->D = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_d = Vrab02 ? 1 : 0;
  self.D = Vrab01 ? 1 : 0; self.holding_d = Vrab02 ? 1 : 0;
 }
 int0  J(int8 key, int8 holding)
 {
  int1 Vrab01 = false, Vrab02 = false;
  if(holding > 0) 
  {
   if(key_load[6] == 0)
   {Vrab01 = true; Vrab02 = false;} else {Vrab01 = true; Vrab02 = true;}
  } else
  {
   if(key > 0) if(key_load[6] == 0)
   {Vrab01 = true; Vrab02 = false;}
  }
  
  game->objects[self.num]->J = Vrab01 ? 1 : 0;
  game->objects[self.num]->holding_j = Vrab02 ? 1 : 0;
  self.J = Vrab01 ? 1 : 0; self.holding_j = Vrab02 ? 1 : 0;
 }

 int0  DrA() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DrA; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D     = Vrab02 ? 1 : 0; self.D     = Vrab02 ? 1 : 0;
  game->objects[self.num]->right = Vrab03 ? 1 : 0; self.right = Vrab03 ? 1 : 0;
  game->objects[self.num]->A     = Vrab04 ? 1 : 0; self.A     = Vrab04 ? 1 : 0;
 }
 int0  DrJ() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DrJ; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D     = Vrab02 ? 1 : 0; self.D     = Vrab02 ? 1 : 0;
  game->objects[self.num]->right = Vrab03 ? 1 : 0; self.right = Vrab03 ? 1 : 0;
  game->objects[self.num]->J     = Vrab04 ? 1 : 0; self.J     = Vrab04 ? 1 : 0;
 }
 int0  DlA() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DlA; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D    = Vrab02 ? 1 : 0; self.D    = Vrab02 ? 1 : 0;
  game->objects[self.num]->left = Vrab03 ? 1 : 0; self.left = Vrab03 ? 1 : 0;
  game->objects[self.num]->A    = Vrab04 ? 1 : 0; self.A    = Vrab04 ? 1 : 0;
 }
 int0  DlJ() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DlJ; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D    = Vrab02 ? 1 : 0; self.D    = Vrab02 ? 1 : 0;
  game->objects[self.num]->left = Vrab03 ? 1 : 0; self.left = Vrab03 ? 1 : 0;
  game->objects[self.num]->J    = Vrab04 ? 1 : 0; self.J    = Vrab04 ? 1 : 0;
 }
 int0  DdA() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DdA; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D    = Vrab02 ? 1 : 0; self.D    = Vrab02 ? 1 : 0;
  game->objects[self.num]->down = Vrab03 ? 1 : 0; self.down = Vrab03 ? 1 : 0;
  game->objects[self.num]->A    = Vrab04 ? 1 : 0; self.A    = Vrab04 ? 1 : 0;
 }
 int0  DdJ() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DdJ; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D    = Vrab02 ? 1 : 0; self.D    = Vrab02 ? 1 : 0;
  game->objects[self.num]->down = Vrab03 ? 1 : 0; self.down = Vrab03 ? 1 : 0;
  game->objects[self.num]->J    = Vrab04 ? 1 : 0; self.J    = Vrab04 ? 1 : 0;
 }
 int0  DuA() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DuA; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D  = Vrab02 ? 1 : 0; self.D  = Vrab02 ? 1 : 0;
  game->objects[self.num]->up = Vrab03 ? 1 : 0; self.up = Vrab03 ? 1 : 0;
  game->objects[self.num]->A  = Vrab04 ? 1 : 0; self.A  = Vrab04 ? 1 : 0;
 }
 int0  DuJ() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DuJ; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D  = Vrab02 ? 1 : 0; self.D  = Vrab02 ? 1 : 0;
  game->objects[self.num]->up = Vrab03 ? 1 : 0; self.up = Vrab03 ? 1 : 0;
  game->objects[self.num]->J  = Vrab04 ? 1 : 0; self.J  = Vrab04 ? 1 : 0;
 }
 int0  DJA() perfect
 {
  statics int8 Vrab01 = game->objects[self.num]->DJA; L_Empty();
  int1 Vrab02 = false, Vrab03 = false, Vrab04 = false;
  if(Vrab01 == 0)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[5] != 0 || key_load[6] != 0){return;} else
   {Vrab02 = true; Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 1)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0 || key_load[6] != 0){return;} else
   {Vrab03 = true; Vrab04 = true;}
  } else if(Vrab01 == 2)
  {
   if(key_load[0] != 0 || key_load[1] != 0 || key_load[2] != 0 || key_load[3] != 0 || key_load[4] != 0){return;} else
   {Vrab04 = true;}
  } else {return;}
  
  game->objects[self.num]->D = Vrab02 ? 1 : 0; self.D = Vrab02 ? 1 : 0;
  game->objects[self.num]->J = Vrab03 ? 1 : 0; self.J = Vrab03 ? 1 : 0;
  game->objects[self.num]->A = Vrab04 ? 1 : 0; self.A = Vrab04 ? 1 : 0;
 }

// Detour Functions
 int32 (__stdcall *D_DetourID )(int32 object_num, int32 unkwn1);
 int32 (__stdcall *D_DetourEGO)(int32 target_num, int32 object_num, int32 x, int32 y, int32 z, int32 a, int32 b);
 int0  D_CallID(int32 object_num, asIScriptFunction *Function)
 {
  L_Base(object_num, false); statics string Temp01 = std::to_string(0) + ".as";

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
  L_Base(object_num); statics string Temp01 = std::to_string(0) + ".as";

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
   if(full_script) M_Update(-1, "ai.as");
   M_Update(id_int, fileName);
  #endif

  int1 Vrab01 = false;

  if(full_script)
  {
   ScriptModule = ScriptEngine->GetModule(string("ai").c_str());
   if(ScriptModule)
   {
    asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("void id()");
    if(Function){D_CallID(object_num, Function); Vrab01 = true;} else
    {
     Function = ScriptModule->GetFunctionByDecl("int id()");
     if(Function){D_CallID(object_num, Function); if(ScriptContext->GetReturnDWord() == 0) return; Vrab01 = true;}
     #ifdef AISCRIPT_DEBUG
      else
      {
       ScriptEngine->WriteMessage(string("ai.as").c_str(), 0, 0, asMSGTYPE_ERROR, "Neither 'void id()' nor 'int id()' are defined.");
      }
     #endif
    }
   }
  }

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

  if(Vrab01) return;

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
    printf("%s - %s\n", Amsg01->type == asMSGTYPE_ERROR ? ("ERROR") : (Amsg01->type == asMSGTYPE_WARNING ? "WARNING" : "INFO"), Amsg01->message);
   } else if(Amsg01->row == 0 && Amsg01->col == 0)
   {
    printf("%s: %s - %s\n", Amsg01->section, Amsg01->type == asMSGTYPE_ERROR ? ("ERROR") : (Amsg01->type == asMSGTYPE_WARNING ? "WARNING" : "INFO"), Amsg01->message);
   } else
   {
    printf("%s(%d, %d): %s - %s\n", Amsg01->section, Amsg01->row, Amsg01->col, Amsg01->type == asMSGTYPE_ERROR ? ("ERROR") : (Amsg01->type == asMSGTYPE_WARNING ? "WARNING" : "INFO"), Amsg01->message);
   }
  }
  int0 M_Update(statics int32 Vrab01, statics string Temp01) perfect
  {
   statics string Temp02 = string(_AISCRIPT_AISCRIPTADDRESS) + "/" + Temp01;
   std::time_t Time01 = 0; struct stat Stat01; if(!L_Exist(Temp02)) return; if(stat((Temp02).c_str(), &Stat01) == 0) Time01 = Stat01.st_mtime;
   if(Maps0001.count(Vrab01))
   {
    if(Maps0001[Vrab01] < Time01)
    {
     ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
	 CScriptBuilder Builder;
     Builder.DefineWord("debug");

     if(Temp01.at(0) == '_')
     {Builder.DefineWord("module");} else {Builder.DefineWord("character");}

     ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
     Builder.StartNewModule(ScriptEngine, string(Temp01, 0, Temp01.size() - 3).c_str());

     if(Builder.AddSectionFromFile(Temp02.c_str()) < 0)
     {
      ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
      ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
      return;
     }

     Maps0001[Vrab01] = Time01;

     if(Builder.BuildModule() < 0)
     {
      ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
      ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
      return;
     }
    }
   } else
   {
    CScriptBuilder Builder;
    Builder.DefineWord("debug");

    if(Temp01.at(0) == '_')
    {Builder.DefineWord("module");} else {Builder.DefineWord("character");}

    ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_INFORMATION, "Rebuilding.");
    Builder.StartNewModule(ScriptEngine, string(Temp01, 0, Temp01.size() - 3).c_str());

    if(Builder.AddSectionFromFile(Temp02.c_str()) < 0)
    {
     ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to load file.");
     ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
     return;
    }

	Maps0001.insert(std::pair < int32 , std::time_t > (Vrab01, Time01));

    if(Builder.BuildModule() < 0)
    {
     ScriptEngine->WriteMessage(Temp01.c_str(), 0, 0, asMSGTYPE_ERROR, "Unable to build module.");
     ScriptEngine->DiscardModule(string(Temp01, 0, Temp01.size() - 3).c_str());
     return;
    }
   }
  }
 #endif

 int0 M_Functions() perfect
 {
  RegisterScriptMath(ScriptEngine);
  RegisterScriptMathComplex(ScriptEngine);
  RegisterScriptArray(ScriptEngine, true);
  RegisterStdString(ScriptEngine);
  RegisterStdStringUtils(ScriptEngine);
  
  ScriptEngine->RegisterObjectType("Info", 0, asOBJ_REF);
  ScriptEngine->RegisterObjectType("Game", 0, asOBJ_REF | asOBJ_NOCOUNT);
  #if _AISCRIPT_NEORACOMPATIBLE
   ScriptEngine->RegisterObjectType("Game2", 0, asOBJ_REF | asOBJ_NOCOUNT);
  #endif
  
  ScriptEngine->RegisterObjectType("Object",      0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("FileManager", 0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("DataFile",    0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("File",        0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Strength",    0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Entry",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Frame",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Bpoint",      0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Cpoint",      0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Wpoint",      0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Opoint",      0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Itr",         0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Bdy",         0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Stage",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Phase",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Spawn",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Background",  0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("Layer",       0, asOBJ_REF | asOBJ_NOCOUNT);

  ScriptEngine->RegisterObjectType("BoolArray",        0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("CharArray",        0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("IntArray",         0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("CharArrayArray30", 0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("CharArrayArray40", 0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("ObjectArray",      0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("DataFileArray",    0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("FileArray",        0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("EntryArray",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("FrameArray",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("ItrArray",         0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("BdyArray",         0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("StageArray",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("PhaseArray",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("SpawnArray",       0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("BackgroundArray",  0, asOBJ_REF | asOBJ_NOCOUNT);
  ScriptEngine->RegisterObjectType("LayerArray",       0, asOBJ_REF | asOBJ_NOCOUNT);

  ScriptEngine->RegisterObjectProperty("Game", "const int32 state",         asOFFSET(AISCRIPT_GAME, state));
  ScriptEngine->RegisterObjectProperty("Game", "const BoolArray exists",    asOFFSET(AISCRIPT_GAME, exists));
  ScriptEngine->RegisterObjectProperty("Game", "const ObjectArray objects", asOFFSET(AISCRIPT_GAME, objects));
  ScriptEngine->RegisterObjectProperty("Game", "const FileManager @files",  asOFFSET(AISCRIPT_GAME, files));
  
  ScriptEngine->RegisterObjectProperty("FileManager", "const DataFileArray datas", asOFFSET(AISCRIPT_GAME_FILE, datas));
  ScriptEngine->RegisterObjectProperty("FileManager", "const IntArray data_ptrs",  asOFFSET(AISCRIPT_GAME_FILE, datas)); //allows to check whether or not a datafile exists
  ScriptEngine->RegisterObjectProperty("FileManager", "const StageArray stages",   asOFFSET(AISCRIPT_GAME_FILE, stages));
  ScriptEngine->RegisterObjectMethod  ("FileManager", "const BackgroundArray &get_backgrounds() const", asFUNCTION(Index < asOFFSET(AISCRIPT_GAME_FILE, backgrounds) >), asCALL_CDECL_OBJLAST);

  ScriptEngine->RegisterObjectProperty("Object", "const int32  move_counter", asOFFSET(AISCRIPT_GAME_OBJECT, move_counter));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  run_counter",  asOFFSET(AISCRIPT_GAME_OBJECT, run_counter));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  blink",        asOFFSET(AISCRIPT_GAME_OBJECT, blink));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  unkwn1",       asOFFSET(AISCRIPT_GAME_OBJECT, unkwn1));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  x", asOFFSET(AISCRIPT_GAME_OBJECT, x));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  y", asOFFSET(AISCRIPT_GAME_OBJECT, y));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  z", asOFFSET(AISCRIPT_GAME_OBJECT, z));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn2",      asOFFSET(AISCRIPT_GAME_OBJECT, unkwn2));
  ScriptEngine->RegisterObjectProperty("Object", "const double x_acceleration", asOFFSET(AISCRIPT_GAME_OBJECT, x_acceleration));
  ScriptEngine->RegisterObjectProperty("Object", "const double y_acceleration", asOFFSET(AISCRIPT_GAME_OBJECT, y_acceleration));
  ScriptEngine->RegisterObjectProperty("Object", "const double z_acceleration", asOFFSET(AISCRIPT_GAME_OBJECT, z_acceleration));
  ScriptEngine->RegisterObjectProperty("Object", "const double x_velocity", asOFFSET(AISCRIPT_GAME_OBJECT, x_velocity));
  ScriptEngine->RegisterObjectProperty("Object", "const double y_velocity", asOFFSET(AISCRIPT_GAME_OBJECT, y_velocity));
  ScriptEngine->RegisterObjectProperty("Object", "const double z_velocity", asOFFSET(AISCRIPT_GAME_OBJECT, z_velocity));
  ScriptEngine->RegisterObjectProperty("Object", "const double x_real", asOFFSET(AISCRIPT_GAME_OBJECT, x_real));
  ScriptEngine->RegisterObjectProperty("Object", "const double y_real", asOFFSET(AISCRIPT_GAME_OBJECT, y_real));
  ScriptEngine->RegisterObjectProperty("Object", "const double z_real", asOFFSET(AISCRIPT_GAME_OBJECT, z_real));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  frame1", asOFFSET(AISCRIPT_GAME_OBJECT, frame1));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  frame2", asOFFSET(AISCRIPT_GAME_OBJECT, frame2));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  frame3", asOFFSET(AISCRIPT_GAME_OBJECT, frame3));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  frame4", asOFFSET(AISCRIPT_GAME_OBJECT, frame4));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   facing", asOFFSET(AISCRIPT_GAME_OBJECT, facing));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn3",     asOFFSET(AISCRIPT_GAME_OBJECT, unkwn3));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  wait_counter",  asOFFSET(AISCRIPT_GAME_OBJECT, wait_counter));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  ccatching",     asOFFSET(AISCRIPT_GAME_OBJECT, ccatching));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  ccatcher",      asOFFSET(AISCRIPT_GAME_OBJECT, ccatcher));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  ctimer",        asOFFSET(AISCRIPT_GAME_OBJECT, ctimer));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  weapon_type",   asOFFSET(AISCRIPT_GAME_OBJECT, weapon_type));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  weapon_held",   asOFFSET(AISCRIPT_GAME_OBJECT, weapon_held));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  weapon_holder", asOFFSET(AISCRIPT_GAME_OBJECT, weapon_holder));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  unkwn4",        asOFFSET(AISCRIPT_GAME_OBJECT, unkwn4));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn5",     asOFFSET(AISCRIPT_GAME_OBJECT, unkwn5));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  fall",          asOFFSET(AISCRIPT_GAME_OBJECT, fall));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  shake",         asOFFSET(AISCRIPT_GAME_OBJECT, shake));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  bdefend",       asOFFSET(AISCRIPT_GAME_OBJECT, bdefend));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn6",     asOFFSET(AISCRIPT_GAME_OBJECT, unkwn6));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_up",    asOFFSET(AISCRIPT_GAME_OBJECT, holding_up));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_down",  asOFFSET(AISCRIPT_GAME_OBJECT, holding_down));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_left",  asOFFSET(AISCRIPT_GAME_OBJECT, holding_left));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_right", asOFFSET(AISCRIPT_GAME_OBJECT, holding_right));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_a",     asOFFSET(AISCRIPT_GAME_OBJECT, holding_a));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_j",     asOFFSET(AISCRIPT_GAME_OBJECT, holding_j));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   holding_d",     asOFFSET(AISCRIPT_GAME_OBJECT, holding_d));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   up",    asOFFSET(AISCRIPT_GAME_OBJECT, up));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   down",  asOFFSET(AISCRIPT_GAME_OBJECT, down));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   left",  asOFFSET(AISCRIPT_GAME_OBJECT, left));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   right", asOFFSET(AISCRIPT_GAME_OBJECT, right));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   A",     asOFFSET(AISCRIPT_GAME_OBJECT, A));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   J",     asOFFSET(AISCRIPT_GAME_OBJECT, J));
  ScriptEngine->RegisterObjectProperty("Object", "const bool   D",     asOFFSET(AISCRIPT_GAME_OBJECT, D));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DrA", asOFFSET(AISCRIPT_GAME_OBJECT, DrA));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DlA", asOFFSET(AISCRIPT_GAME_OBJECT, DlA));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DuA", asOFFSET(AISCRIPT_GAME_OBJECT, DuA));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DdA", asOFFSET(AISCRIPT_GAME_OBJECT, DdA));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DrJ", asOFFSET(AISCRIPT_GAME_OBJECT, DrJ));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DlJ", asOFFSET(AISCRIPT_GAME_OBJECT, DlJ));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DuJ", asOFFSET(AISCRIPT_GAME_OBJECT, DuJ));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DdJ", asOFFSET(AISCRIPT_GAME_OBJECT, DdJ));
  ScriptEngine->RegisterObjectProperty("Object", "const int8   DJA", asOFFSET(AISCRIPT_GAME_OBJECT, DJA));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn7", asOFFSET(AISCRIPT_GAME_OBJECT, unkwn7));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  heal",      asOFFSET(AISCRIPT_GAME_OBJECT, heal));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn8", asOFFSET(AISCRIPT_GAME_OBJECT, unkwn8));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  arest",     asOFFSET(AISCRIPT_GAME_OBJECT, arest));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray vrests", asOFFSET(AISCRIPT_GAME_OBJECT, vrests));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  vrest",     asOFFSET(AISCRIPT_GAME_OBJECT, vrests));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  attacked_object_num", asOFFSET(AISCRIPT_GAME_OBJECT, attacked_object_num));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn9",           asOFFSET(AISCRIPT_GAME_OBJECT, unkwn9));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  clone",               asOFFSET(AISCRIPT_GAME_OBJECT, clone));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  weapon_thrower",      asOFFSET(AISCRIPT_GAME_OBJECT, weapon_thrower));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  hp",      asOFFSET(AISCRIPT_GAME_OBJECT, hp));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  dark_hp", asOFFSET(AISCRIPT_GAME_OBJECT, dark_hp));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  max_hp",  asOFFSET(AISCRIPT_GAME_OBJECT, max_hp));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  mp",      asOFFSET(AISCRIPT_GAME_OBJECT, mp));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  reserve", asOFFSET(AISCRIPT_GAME_OBJECT, reserve));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  unkwn10", asOFFSET(AISCRIPT_GAME_OBJECT, unkwn10));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  unkwn11", asOFFSET(AISCRIPT_GAME_OBJECT, unkwn11));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  pic_gain",          asOFFSET(AISCRIPT_GAME_OBJECT, pic_gain));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  bottle_hp",         asOFFSET(AISCRIPT_GAME_OBJECT, bottle_hp));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  throwinjury",       asOFFSET(AISCRIPT_GAME_OBJECT, throwinjury));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn12",        asOFFSET(AISCRIPT_GAME_OBJECT, unkwn12));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  firzen_counter",    asOFFSET(AISCRIPT_GAME_OBJECT, firzen_counter));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  unkwn13",           asOFFSET(AISCRIPT_GAME_OBJECT, unkwn13));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  armour_multiplier", asOFFSET(AISCRIPT_GAME_OBJECT, armour_multiplier));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  unkwn14",           asOFFSET(AISCRIPT_GAME_OBJECT, unkwn14));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  total_attack",      asOFFSET(AISCRIPT_GAME_OBJECT, total_attack));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  hp_lost",           asOFFSET(AISCRIPT_GAME_OBJECT, hp_lost));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  mp_usage",          asOFFSET(AISCRIPT_GAME_OBJECT, mp_usage));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  host",              asOFFSET(AISCRIPT_GAME_OBJECT, host));
  ScriptEngine->RegisterObjectProperty("Object", "const CharArray unkwn15",        asOFFSET(AISCRIPT_GAME_OBJECT, host));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  kills",             asOFFSET(AISCRIPT_GAME_OBJECT, kills));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  weapon_picks",      asOFFSET(AISCRIPT_GAME_OBJECT, weapon_picks));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  enemy",             asOFFSET(AISCRIPT_GAME_OBJECT, enemy));
  ScriptEngine->RegisterObjectProperty("Object", "const int32  team",              asOFFSET(AISCRIPT_GAME_OBJECT, team));
  ScriptEngine->RegisterObjectProperty("Object", "const DataFile @data",           asOFFSET(AISCRIPT_GAME_OBJECT, data));
  
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  walking_frame_rate", asOFFSET(AISCRIPT_GAME_FILE_DATA, walking_frame_rate));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  unkwn1",             asOFFSET(AISCRIPT_GAME_FILE_DATA, unkwn1));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double walking_speed",      asOFFSET(AISCRIPT_GAME_FILE_DATA, walking_speed));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double walking_speedz",     asOFFSET(AISCRIPT_GAME_FILE_DATA, walking_speedz));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  running_frame_rate", asOFFSET(AISCRIPT_GAME_FILE_DATA, running_frame_rate));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double running_speed",      asOFFSET(AISCRIPT_GAME_FILE_DATA, running_speed));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double running_speedz",     asOFFSET(AISCRIPT_GAME_FILE_DATA, running_speedz));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double heavy_walking_speed",  asOFFSET(AISCRIPT_GAME_FILE_DATA, heavy_walking_speed));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double heavy_walking_speedz", asOFFSET(AISCRIPT_GAME_FILE_DATA, heavy_walking_speedz));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double heavy_running_speed",  asOFFSET(AISCRIPT_GAME_FILE_DATA, heavy_running_speed));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double heavy_running_speedz", asOFFSET(AISCRIPT_GAME_FILE_DATA, heavy_running_speedz));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double jump_height",      asOFFSET(AISCRIPT_GAME_FILE_DATA, jump_height));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double jump_distance",    asOFFSET(AISCRIPT_GAME_FILE_DATA, jump_distance));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double jump_distancez",   asOFFSET(AISCRIPT_GAME_FILE_DATA, jump_distancez));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double dash_height",      asOFFSET(AISCRIPT_GAME_FILE_DATA, dash_height));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double dash_distance",    asOFFSET(AISCRIPT_GAME_FILE_DATA, dash_distance));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double dash_distancez",   asOFFSET(AISCRIPT_GAME_FILE_DATA, dash_distancez));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double rowing_height",    asOFFSET(AISCRIPT_GAME_FILE_DATA, rowing_height));
  ScriptEngine->RegisterObjectProperty("DataFile", "const double rowing_distance",  asOFFSET(AISCRIPT_GAME_FILE_DATA, rowing_distance));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  weapon_hp",        asOFFSET(AISCRIPT_GAME_FILE_DATA, weapon_hp));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  weapon_drop_hurt", asOFFSET(AISCRIPT_GAME_FILE_DATA, weapon_drop_hurt));
  ScriptEngine->RegisterObjectProperty("DataFile", "const CharArray unkwn2",        asOFFSET(AISCRIPT_GAME_FILE_DATA, unkwn2));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  file_count",       asOFFSET(AISCRIPT_GAME_FILE_DATA, file_count));
  ScriptEngine->RegisterObjectProperty("DataFile", "const CharArrayArray40 file_address", asOFFSET(AISCRIPT_GAME_FILE_DATA, file_address));
  ScriptEngine->RegisterObjectProperty("DataFile", "const FileArray file", asOFFSET(AISCRIPT_GAME_FILE_DATA, file));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  id",      asOFFSET(AISCRIPT_GAME_FILE_DATA, id));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  type",    asOFFSET(AISCRIPT_GAME_FILE_DATA, type));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  unkwn3",  asOFFSET(AISCRIPT_GAME_FILE_DATA, unkwn3));
  ScriptEngine->RegisterObjectProperty("DataFile", "const CharArray small_bmp", asOFFSET(AISCRIPT_GAME_FILE_DATA, small_bmp));
  ScriptEngine->RegisterObjectProperty("DataFile", "const int32  unkwn4",       asOFFSET(AISCRIPT_GAME_FILE_DATA, unkwn4));
  ScriptEngine->RegisterObjectProperty("DataFile", "const CharArray  face_bmp", asOFFSET(AISCRIPT_GAME_FILE_DATA, face_bmp));
  ScriptEngine->RegisterObjectProperty("DataFile", "const IntArray   unkwn5",   asOFFSET(AISCRIPT_GAME_FILE_DATA, unkwn5));
  ScriptEngine->RegisterObjectProperty("DataFile", "const FrameArray frames",   asOFFSET(AISCRIPT_GAME_FILE_DATA, frames));
  ScriptEngine->RegisterObjectMethod  ("DataFile", "const CharArray  &get_name() const", asFUNCTION(Index < asOFFSET(AISCRIPT_GAME_FILE_DATA, name) >), asCALL_CDECL_OBJLAST);
    
  ScriptEngine->RegisterObjectProperty("File", "const int32 ptr", asOFFSET(AISCRIPT_GAME_FILE_DATA_FILE, ptr[0]));
  ScriptEngine->RegisterObjectProperty("File", "const int32 w",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FILE, w[0]));
  ScriptEngine->RegisterObjectProperty("File", "const int32 h",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FILE, h[0]));
  ScriptEngine->RegisterObjectProperty("File", "const int32 row", asOFFSET(AISCRIPT_GAME_FILE_DATA_FILE, row[0]));
  ScriptEngine->RegisterObjectProperty("File", "const int32 col", asOFFSET(AISCRIPT_GAME_FILE_DATA_FILE, col[0]));

  ScriptEngine->RegisterObjectProperty("Strength", "const EntryArray entry",            asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH, entry[0]));
  ScriptEngine->RegisterObjectProperty("Strength", "const CharArrayArray30 entry_name", asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH, entry_name[0][0]));
  ScriptEngine->RegisterObjectProperty("Strength", "const CharArray unkwn1",            asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH, unkwn1[0]));
 
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 dvx",        asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, dvx));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 dvy",        asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, dvy));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 fall",       asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, fall));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 arest",      asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, arest));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 vrest",      asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, vrest));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 respond",    asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, respond));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 effect",     asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, effect));
  ScriptEngine->RegisterObjectProperty("Entry", "const CharArray unkwn1", asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, unkwn1[0]));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 bdefend",    asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, bdefend));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 injury",     asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, injury));
  ScriptEngine->RegisterObjectProperty("Entry", "const int32 zwidth",     asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, zwidth));
  ScriptEngine->RegisterObjectProperty("Entry", "const CharArray unkwn2", asOFFSET(AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY, unkwn2[0]));

  ScriptEngine->RegisterObjectProperty("Frame", "const bool  exists",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, exists));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 pic",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, pic));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 state",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, state));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 wait",    asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, wait));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 next",    asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, next));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 dvx",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, dvx));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 dvy",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, dvy));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 dvz",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, dvz));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn1",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn1));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_a",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_a));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_d",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_d));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_j",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_j));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_Fa",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_Fa));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_Ua",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_Ua));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_Da",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_Da));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_Fj",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_Fj));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_Uj",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_Uj));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_Dj",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_Dj));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 hit_ja",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, hit_ja));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 mp",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, mp));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 centerx", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, centerx));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 centery", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, centery));
  ScriptEngine->RegisterObjectProperty("Frame", "const Opoint opoint", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, opoint));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn2",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn2));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn3",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn3));
  ScriptEngine->RegisterObjectProperty("Frame", "const Bpoint bpoint", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bpoint));
  ScriptEngine->RegisterObjectProperty("Frame", "const Cpoint cpoint", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, cpoint));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn4",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn4));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn5",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn5));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn6",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn6));
  ScriptEngine->RegisterObjectProperty("Frame", "const Wpoint wpoint", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, wpoint));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn7",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn7));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn8",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn8));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn9",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn9));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn10", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn10));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn11", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn11));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn12", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn12));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn13", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn13));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn14", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn14));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn15", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn15));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn16", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn16));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn17", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn17));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 itr_count", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, itr_count));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 bdy_count", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bdy_count));
  ScriptEngine->RegisterObjectProperty("Frame", "const ItrArray @itrs",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, itrs));
  ScriptEngine->RegisterObjectProperty("Frame", "const BdyArray @bdys",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bdys));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 itr_x",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, itr_x));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 itr_y",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, itr_y));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 itr_w",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, itr_w));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 itr_h",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, itr_h));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 bdy_x",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bdy_x));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 bdy_y",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bdy_y));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 bdy_w",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bdy_w));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 bdy_h",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, bdy_h));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn18", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn18));
  ScriptEngine->RegisterObjectProperty("Frame", "const CharArray fname",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, fname));
  ScriptEngine->RegisterObjectProperty("Frame", "const CharArray @sound", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, sound));
  ScriptEngine->RegisterObjectProperty("Frame", "const int32 unkwn19",    asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME, unkwn19));

  ScriptEngine->RegisterObjectProperty("Bpoint", "const int32 x", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BPOINT, x));
  ScriptEngine->RegisterObjectProperty("Bpoint", "const int32 y", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BPOINT, y));

  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 kind",         asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, kind));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 x",            asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, x));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 y",            asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, y));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 injury",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, injury));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 cover",        asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, cover));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 fronthurtact", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, injury));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 backhurtact",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, cover)); 
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 vaction",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, vaction));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 aaction",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, aaction));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 jaction",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, jaction));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 daction",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, daction));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 throwvx",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, throwvx));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 throwvy",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, throwvy));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 hurtable",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, hurtable));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 decrease",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, decrease));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 dircontrol",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, dircontrol));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 taction",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, taction));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 throwinjury",  asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, throwinjury));
  ScriptEngine->RegisterObjectProperty("Cpoint", "const int32 throwvz",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT, throwvz));

  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 kind",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, kind));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 x",         asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, x));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 y",         asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, y));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 weaponact", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, weaponact));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 attacking", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, attacking));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 cover",     asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, cover));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 dvx",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, dvx));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 dvy",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, dvy));
  ScriptEngine->RegisterObjectProperty("Wpoint", "const int32 dvz",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT, dvz));

  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 kind",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, kind));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 x",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, x));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 y",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, y));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 action", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, action));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 dvx",    asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, dvx));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 dvy",    asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, dvy));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 oid",    asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, oid));
  ScriptEngine->RegisterObjectProperty("Opoint", "const int32 facing", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT, facing));

  ScriptEngine->RegisterObjectProperty("Itr", "const int32 kind",         asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, kind));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 x",            asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, x));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 y",            asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, y));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 w",            asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, w));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 h",            asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, h));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 dvx",          asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, dvx));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 dvy",          asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, dvy));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 fall",         asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, fall));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 arest",        asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, arest));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 vrest",        asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, vrest));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 respond",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, respond));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 effect",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, effect));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 catchingact1", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, catchingact1));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 catchingact2", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, catchingact2));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 caughtact1",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, caughtact1));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 caughtact2",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, caughtact2));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 bdefend",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, bdefend));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 injury",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, injury));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 zwidth",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, zwidth));
  ScriptEngine->RegisterObjectProperty("Itr", "const int32 unkwn2",       asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_ITR, unkwn1));

  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 kind",   asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, kind));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 x",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, x));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 y",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, y));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 w",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, w));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 h",      asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, h));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 unkwn1", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, unkwn1));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 unkwn2", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, unkwn2));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 unkwn3", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, unkwn3));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 unkwn4", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, unkwn4));
  ScriptEngine->RegisterObjectProperty("Bdy", "const int32 unkwn5", asOFFSET(AISCRIPT_GAME_FILE_DATA_FRAME_BDY, unkwn5));

  ScriptEngine->RegisterObjectProperty("Stage", "const int32 phase_count", asOFFSET(AISCRIPT_GAME_FILE_STAGE, phase_count));
  ScriptEngine->RegisterObjectProperty("Stage", "const PhaseArray phases", asOFFSET(AISCRIPT_GAME_FILE_STAGE, phases));

  ScriptEngine->RegisterObjectProperty("Phase", "const int32 bound",       asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE, bound));
  ScriptEngine->RegisterObjectProperty("Phase", "const CharArray  music",  asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE, music));
  ScriptEngine->RegisterObjectProperty("Phase", "const SpawnArray spawns", asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE, spawns));
  ScriptEngine->RegisterObjectProperty("Phase", "const int32 when_clear_goto_phase", asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE, when_clear_goto_phase));
 
  ScriptEngine->RegisterObjectProperty("Spawn", "const IntArray unkwn1",     asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, unkwn1));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  id",           asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, id));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  x",            asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, x));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  hp",           asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, hp));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  times",        asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, times));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  reserve",      asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, reserve));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  join",         asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, join));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  join_reserve", asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, join_reserve));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  act",          asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, act));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  y",            asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, y));
  ScriptEngine->RegisterObjectProperty("Spawn", "const double ratio",        asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, ratio));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  role",         asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, role));
  ScriptEngine->RegisterObjectProperty("Spawn", "const int32  unkwn2",       asOFFSET(AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN, unkwn2));
  
  ScriptEngine->RegisterObjectProperty("Background", "const int32 bg_width",     asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, bg_width));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 bg_zwidth1",   asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, bg_zwidth1));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 bg_zwidth2",   asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, bg_zwidth2));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 perspective1", asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, perspective1));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 perspective2", asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, perspective2));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 shadow1",      asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, shadow1));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 shadow2",      asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, shadow2));
  ScriptEngine->RegisterObjectProperty("Background", "const int32 layer_count",  asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, layer_count));
  ScriptEngine->RegisterObjectProperty("Background", "const CharArrayArray30 layer_bmps", asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, layer_bmps));
  ScriptEngine->RegisterObjectProperty("Background", "const CharArray shadow_bmp", asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, shadow_bmp));
  ScriptEngine->RegisterObjectProperty("Background", "const CharArray unkwn1",     asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, unkwn1));
  ScriptEngine->RegisterObjectProperty("Background", "const CharArray name",       asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, name));
  ScriptEngine->RegisterObjectProperty("Background", "const CharArray unkwn2",     asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, unkwn2));
  ScriptEngine->RegisterObjectProperty("Background", "const LayerArray layer",     asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, layer));
  ScriptEngine->RegisterObjectProperty("Background", "const IntArray layer_ptrs",  asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, layer_ptrs));
  ScriptEngine->RegisterObjectProperty("Background", "const int ptr",              asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND, ptrs));

  ScriptEngine->RegisterObjectProperty("Layer", "const int32 transparency", asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, transparency));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 width",        asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, width));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 x",            asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, x));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 y",            asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, y));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 height",       asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, height));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 loop",         asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, loop));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 c1",           asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, c1));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 c2",           asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, c2));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 cc",           asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, cc));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 animation",    asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, animation));
  ScriptEngine->RegisterObjectProperty("Layer", "const int32 rect",         asOFFSET(AISCRIPT_GAME_FILE_BACKGROUND_LAYER, rect));

  ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_ADDREF,  "void f()", asMETHOD(AISCRIPT_INFO, AddRef), asCALL_THISCALL);
  ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_RELEASE, "void f()", asMETHOD(AISCRIPT_INFO, RelRef), asCALL_THISCALL);
  ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f()",    asFUNCTIONPR(Info_Factory, (), AISCRIPT_INFO*), asCALL_CDECL);
  ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f(int)", asFUNCTIONPR(Info_Factory, (int32 object_num), AISCRIPT_INFO*), asCALL_CDECL);
  ScriptEngine->RegisterObjectBehaviour("Info", asBEHAVE_FACTORY, "Info @f(const Info &in info)", asFUNCTIONPR(Info_Factory, (statics AISCRIPT_INFO &info), AISCRIPT_INFO*), asCALL_CDECL);
  
  ScriptEngine->RegisterObjectMethod("BoolArray",        "const bool &opIndex(uint x) const",       asMETHOD(AISCRIPT_ARRAY_INT1, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("CharArray",        "const int8 &opIndex(uint x) const",       asMETHOD(AISCRIPT_ARRAY_INT8, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("IntArray",         "const int32 &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_INT32, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("CharArrayArray30", "const CharArray &opIndex(uint x) const",  asMETHOD(AISCRIPT_ARRAY_ARRAY_INT8, opIndex < 30 >), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("CharArrayArray40", "const CharArray &opIndex(uint x) const",  asMETHOD(AISCRIPT_ARRAY_ARRAY_INT8, opIndex < 40 >), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("ObjectArray",      "const Object &opIndex(uint x) const",     asMETHOD(AISCRIPT_ARRAY_OBJECT, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("DataFileArray",    "const DataFile &opIndex(uint x) const",   asMETHOD(AISCRIPT_ARRAY_DATA, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("FileArray",        "const File &opIndex(uint x) const",       asMETHOD(AISCRIPT_ARRAY_FILE, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("EntryArray",       "const Entry &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_ENTRY, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("FrameArray",       "const Frame &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_FRAME, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("ItrArray",         "const Itr &opIndex(uint x) const",        asMETHOD(AISCRIPT_ARRAY_ITR, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("BdyArray",         "const Bdy &opIndex(uint x) const",        asMETHOD(AISCRIPT_ARRAY_BDY, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("StageArray",       "const Stage &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_STAGE, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("PhaseArray",       "const Phase &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_PHASE, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("SpawnArray",       "const Spawn &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_SPAWN, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("BackgroundArray",  "const Background &opIndex(uint x) const", asMETHOD(AISCRIPT_ARRAY_BACKGROUND, opIndex), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("LayerArray",       "const Layer &opIndex(uint x) const",      asMETHOD(AISCRIPT_ARRAY_LAYER, opIndex), asCALL_THISCALL);

  ScriptEngine->RegisterObjectMethod("Info", "int opAssign(int object_num)",         asMETHODPR(AISCRIPT_INFO, operator=,  (int32 object_num), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opAssign(const Info &in info)",    asMETHODPR(AISCRIPT_INFO, operator=,  (statics AISCRIPT_INFO &info), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opAddAssign(int object_num)",      asMETHODPR(AISCRIPT_INFO, operator+=, (int32 object_num), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opAddAssign(const Info &in info)", asMETHODPR(AISCRIPT_INFO, operator+=, (statics AISCRIPT_INFO &info), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opSubAssign(int object_num)",      asMETHODPR(AISCRIPT_INFO, operator-=, (int32 object_num), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opSubAssign(const Info &in info)", asMETHODPR(AISCRIPT_INFO, operator-=, (statics AISCRIPT_INFO &info), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opPreInc()",  asMETHODPR(AISCRIPT_INFO, operator++, (), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opPreSub()",  asMETHODPR(AISCRIPT_INFO, operator--, (), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opPostInc()", asMETHODPR(AISCRIPT_INFO, operator++, (), int32), asCALL_THISCALL);
  ScriptEngine->RegisterObjectMethod("Info", "int opPostSub()", asMETHODPR(AISCRIPT_INFO, operator--, (), int32), asCALL_THISCALL);
  
  ScriptEngine->RegisterObjectProperty("Info", "int x",              asOFFSET(AISCRIPT_INFO, x));
  ScriptEngine->RegisterObjectProperty("Info", "int y",              asOFFSET(AISCRIPT_INFO, y));
  ScriptEngine->RegisterObjectProperty("Info", "int z",              asOFFSET(AISCRIPT_INFO, z));
  //ScriptEngine->RegisterObjectProperty("Info", "vector3 position",   asOFFSET(AISCRIPT_INFO, position));
  ScriptEngine->RegisterObjectProperty("Info", "double x_real",      asOFFSET(AISCRIPT_INFO, x_real));
  ScriptEngine->RegisterObjectProperty("Info", "double y_real",      asOFFSET(AISCRIPT_INFO, y_real));
  ScriptEngine->RegisterObjectProperty("Info", "double z_real",      asOFFSET(AISCRIPT_INFO, z_real));
  ScriptEngine->RegisterObjectProperty("Info", "bool facing",        asOFFSET(AISCRIPT_INFO, facing));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_up",    asOFFSET(AISCRIPT_INFO, holding_up));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_down",  asOFFSET(AISCRIPT_INFO, holding_down));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_left",  asOFFSET(AISCRIPT_INFO, holding_left));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_right", asOFFSET(AISCRIPT_INFO, holding_right));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_a",     asOFFSET(AISCRIPT_INFO, holding_a));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_j",     asOFFSET(AISCRIPT_INFO, holding_j));
  ScriptEngine->RegisterObjectProperty("Info", "bool holding_d",     asOFFSET(AISCRIPT_INFO, holding_d));
  ScriptEngine->RegisterObjectProperty("Info", "bool up",            asOFFSET(AISCRIPT_INFO, up));
  ScriptEngine->RegisterObjectProperty("Info", "bool down",          asOFFSET(AISCRIPT_INFO, down));
  ScriptEngine->RegisterObjectProperty("Info", "bool left",          asOFFSET(AISCRIPT_INFO, left));
  ScriptEngine->RegisterObjectProperty("Info", "bool right",         asOFFSET(AISCRIPT_INFO, right));
  ScriptEngine->RegisterObjectProperty("Info", "bool A",             asOFFSET(AISCRIPT_INFO, A));
  ScriptEngine->RegisterObjectProperty("Info", "bool J",             asOFFSET(AISCRIPT_INFO, J));
  ScriptEngine->RegisterObjectProperty("Info", "bool D",             asOFFSET(AISCRIPT_INFO, D));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DrA",           asOFFSET(AISCRIPT_INFO, DrA));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DlA",           asOFFSET(AISCRIPT_INFO, DlA));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DuA",           asOFFSET(AISCRIPT_INFO, DuA));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DdA",           asOFFSET(AISCRIPT_INFO, DdA));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DrJ",           asOFFSET(AISCRIPT_INFO, DrJ));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DlJ",           asOFFSET(AISCRIPT_INFO, DlJ));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DuJ",           asOFFSET(AISCRIPT_INFO, DuJ));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DdJ",           asOFFSET(AISCRIPT_INFO, DdJ));
  ScriptEngine->RegisterObjectProperty("Info", "int8 DJA",           asOFFSET(AISCRIPT_INFO, DJA));
  ScriptEngine->RegisterObjectProperty("Info", "int hp",             asOFFSET(AISCRIPT_INFO, hp));
  ScriptEngine->RegisterObjectProperty("Info", "int dark_hp",        asOFFSET(AISCRIPT_INFO, dark_hp));
  ScriptEngine->RegisterObjectProperty("Info", "int max_hp",         asOFFSET(AISCRIPT_INFO, max_hp));
  ScriptEngine->RegisterObjectProperty("Info", "int mp",             asOFFSET(AISCRIPT_INFO, mp));
  ScriptEngine->RegisterObjectProperty("Info", "int frame",          asOFFSET(AISCRIPT_INFO, frame));
  ScriptEngine->RegisterObjectProperty("Info", "int bdefend",        asOFFSET(AISCRIPT_INFO, bdefend));
  ScriptEngine->RegisterObjectProperty("Info", "int fall",           asOFFSET(AISCRIPT_INFO, fall));
  ScriptEngine->RegisterObjectProperty("Info", "int team",           asOFFSET(AISCRIPT_INFO, team));
  ScriptEngine->RegisterObjectProperty("Info", "int id",             asOFFSET(AISCRIPT_INFO, id));
  ScriptEngine->RegisterObjectProperty("Info", "int blink",          asOFFSET(AISCRIPT_INFO, blink));
  ScriptEngine->RegisterObjectProperty("Info", "int state",          asOFFSET(AISCRIPT_INFO, state));
  ScriptEngine->RegisterObjectProperty("Info", "int weapon_type",    asOFFSET(AISCRIPT_INFO, weapon_type));
  ScriptEngine->RegisterObjectProperty("Info", "int weapon_held",    asOFFSET(AISCRIPT_INFO, weapon_held));
  ScriptEngine->RegisterObjectProperty("Info", "int weapon_holder",  asOFFSET(AISCRIPT_INFO, weapon_holder));
  ScriptEngine->RegisterObjectProperty("Info", "int shake",          asOFFSET(AISCRIPT_INFO, shake));
  ScriptEngine->RegisterObjectProperty("Info", "int wait_counter",   asOFFSET(AISCRIPT_INFO, wait_counter));
  ScriptEngine->RegisterObjectProperty("Info", "int num",            asOFFSET(AISCRIPT_INFO, num));
  ScriptEngine->RegisterObjectProperty("Info", "int ctimer",         asOFFSET(AISCRIPT_INFO, ctimer));
  ScriptEngine->RegisterObjectProperty("Info", "int arest",          asOFFSET(AISCRIPT_INFO, arest));
  ScriptEngine->RegisterObjectProperty("Info", "CharArray vrests",   asOFFSET(AISCRIPT_INFO, vrests));
  ScriptEngine->RegisterObjectProperty("Info", "int vrest",          asOFFSET(AISCRIPT_INFO, vrest));
  //ScriptEngine->RegisterObjectProperty("Info", "vector3 velocity",   asOFFSET(AISCRIPT_INFO, velocity));
  ScriptEngine->RegisterObjectProperty("Info", "double x_velocity",  asOFFSET(AISCRIPT_INFO, x_velocity));
  ScriptEngine->RegisterObjectProperty("Info", "double y_velocity",  asOFFSET(AISCRIPT_INFO, y_velocity));
  ScriptEngine->RegisterObjectProperty("Info", "double z_velocity",  asOFFSET(AISCRIPT_INFO, z_velocity));
  ScriptEngine->RegisterObjectProperty("Info", "int clone",          asOFFSET(AISCRIPT_INFO, clone));
  ScriptEngine->RegisterObjectProperty("Info", "int type",           asOFFSET(AISCRIPT_INFO, type));
  ScriptEngine->RegisterObjectProperty("Info", "int reserve",        asOFFSET(AISCRIPT_INFO, reserve));
  ScriptEngine->RegisterObjectProperty("Info", "DataFile @data",     asOFFSET(AISCRIPT_INFO, data));

  ScriptEngine->RegisterGlobalProperty("const Info  self",    &self);
  ScriptEngine->RegisterGlobalProperty(      "Info  target",  &target);
  ScriptEngine->RegisterGlobalProperty("const Game  game",    game);
  #if _AISCRIPT_NEORACOMPATIBLE
   ScriptEngine->RegisterObjectProperty("Game2", "Game game",  asOFFSET(AISCRIPT_GAMEPTR, game));
   ScriptEngine->RegisterGlobalProperty("const Game2 gamePtr", gamePtr);
  #endif

  ScriptEngine->RegisterGlobalProperty("const int32  mode",                &mode);
  ScriptEngine->RegisterGlobalProperty("const int32  difficulty",          &difficulty);
  ScriptEngine->RegisterGlobalProperty("const int32  elapsed_time",        &elapsed_time);
  ScriptEngine->RegisterGlobalProperty("const int32  background",          &background);
  ScriptEngine->RegisterGlobalProperty("const int32  bg_width",            &bg_width);
  ScriptEngine->RegisterGlobalProperty("const int32  bg_zwidth1",          &bg_zwidth1);
  ScriptEngine->RegisterGlobalProperty("const int32  bg_zwidth2",          &bg_zwidth2);
  ScriptEngine->RegisterGlobalProperty("const int32  stage_bound",         &stage_bound);
  ScriptEngine->RegisterGlobalProperty("const bool   stage_clear",         &stage_clear);
  ScriptEngine->RegisterGlobalProperty("const int32  current_phase",       &current_phase);
  ScriptEngine->RegisterGlobalProperty("const int32  current_phase_count", &current_phase_count);
  ScriptEngine->RegisterGlobalProperty("const int32  current_stage",       &current_stage);
  ScriptEngine->RegisterGlobalProperty("const string version",             &version);
  ScriptEngine->RegisterGlobalProperty("const int32  maxframes",           &max_frames);
  ScriptEngine->RegisterGlobalProperty("const int32  maxobjnum",           &max_objnum);
  
  ScriptEngine->RegisterGlobalFunction("void print(bool p)",             asFUNCTIONPR(print, (int1 p),   int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(int8 p)",             asFUNCTIONPR(print, (int8 p),   int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(int16 p)",            asFUNCTIONPR(print, (int16 p),  int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(int32 p)",            asFUNCTIONPR(print, (int32 p),  int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(int64 p)",            asFUNCTIONPR(print, (int64 p),  int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(uint8 p)",            asFUNCTIONPR(print, (uint8 p),  int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(uint16 p)",           asFUNCTIONPR(print, (uint16 p), int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(uint32 p)",           asFUNCTIONPR(print, (uint32 p), int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(uint64 p)",           asFUNCTIONPR(print, (uint64 p), int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(float p)",            asFUNCTIONPR(print, (xint32 p), int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(double p)",           asFUNCTIONPR(print, (xint64 p), int0), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void print(const string &in p)", asFUNCTIONPR(print, (statics string &p), int0), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void printAddr(const IntArray @addr)",         asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const BoolArray @addr)",        asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArray @addr)",        asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArrayArray30 @addr)", asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArrayArray40 @addr)", asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const DataFileArray @addr)",    asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const ObjectArray @addr)",      asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const FrameArray @addr)",       asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const BackgroundArray @addr)",  asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const SpawnArray @addr)",       asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const PhaseArray @addr)",       asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const StageArray @addr)",       asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const ItrArray @addr)",         asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const BdyArray @addr)",         asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Game @addr)",             asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const FileManager @addr)",      asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Stage @addr)",            asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Phase @addr)",            asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Spawn @addr)",            asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Background @addr)",       asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Object @addr)",           asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const DataFile @addr)",         asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Frame @addr)",            asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Bdy @addr)",              asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Itr @addr)",              asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Wpoint @addr)",           asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Cpoint @addr)",           asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Bpoint @addr)",           asFUNCTION(printAddr), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void printAddr(const Opoint @addr)",           asFUNCTION(printAddr), asCALL_CDECL);
  
  ScriptEngine->RegisterGlobalFunction("void clr()",                     asFUNCTION(clr),        asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("int rand(int n)",                asFUNCTION(random),     asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("int loadTarget(int object_num)", asFUNCTION(loadTarget), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("int setEnemy(int object_num)",   asFUNCTION(setEnemy),   asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void up(int8 key = 1, int8 holding = 0)", asFUNCTION(up), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void up(bool key, int8 holding = 0)",     asFUNCTION(up), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void up(int8 key, bool holding)",         asFUNCTION(up), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void up(bool key, bool holding)",         asFUNCTION(up), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void left(int8 key = 1, int8 holding = 0)", asFUNCTION(left), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void left(bool key, int8 holding = 0)",     asFUNCTION(left), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void left(int8 key, bool holding)",         asFUNCTION(left), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void left(bool key, bool holding)",         asFUNCTION(left), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void down(int8 key = 1, int8 holding = 0)", asFUNCTION(down), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void down(bool key, int8 holding = 0)",     asFUNCTION(down), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void down(int8 key, bool holding)",         asFUNCTION(down), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void down(bool key, bool holding)",         asFUNCTION(down), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void right(int8 key = 1, int8 holding = 0)", asFUNCTION(right), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void right(bool key, int8 holding = 0)",     asFUNCTION(right), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void right(int8 key, bool holding)",         asFUNCTION(right), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void right(bool key, bool holding)",         asFUNCTION(right), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void A(int8 key = 1, int8 holding = 0)", asFUNCTION(A), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void A(bool key, int8 holding = 0)",     asFUNCTION(A), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void A(int8 key, bool holding)",         asFUNCTION(A), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void A(bool key, bool holding)",         asFUNCTION(A), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void D(int8 key = 1,int8 holding = 0)", asFUNCTION(D), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void D(bool key,int8 holding = 0)",     asFUNCTION(D), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void D(int8 key,bool holding)",         asFUNCTION(D), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void D(bool key,bool holding)",         asFUNCTION(D), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void J(int8 key = 1, int8 holding = 0)", asFUNCTION(J), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void J(bool key, int8 holding = 0)",     asFUNCTION(J), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void J(int8 key, bool holding)",         asFUNCTION(J), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void J(bool key, bool holding)",         asFUNCTION(J), asCALL_CDECL);

  ScriptEngine->RegisterGlobalFunction("void DrA()", asFUNCTION(DrA), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DlA()", asFUNCTION(DlA), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DuA()", asFUNCTION(DuA), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DdA()", asFUNCTION(DdA), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DrJ()", asFUNCTION(DrJ), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DlJ()", asFUNCTION(DlJ), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DuJ()", asFUNCTION(DuJ), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DdJ()", asFUNCTION(DdJ), asCALL_CDECL);
  ScriptEngine->RegisterGlobalFunction("void DJA()", asFUNCTION(DJA), asCALL_CDECL);
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
  M_Functions();
  
  D_DetourID  = (int32 (__stdcall *)(int32, int32))DetourFunction((PBYTE)0x004094b0, (PBYTE)D_ID);
  D_DetourEGO = (int32 (__stdcall *)(int32, int32, int32, int32, int32, int32, int32))DetourFunction((PBYTE)0x00403a40, (PBYTE)D_EGO);

  statics string Temp01 = _AISCRIPT_AISCRIPTADDRESS;
  if(L_Exist(Temp01)) for(auto statics &Temp02 : std::filesystem::directory_iterator(Temp01))
  {
   statics string Temp03 = Temp02.path().string(); if(Temp03.size() < Temp01.size() + 5) continue;
   statics string Temp04 = L_Lowercase(string(Temp03, Temp01.size() + 1, Temp03.size() - (Temp01.size() + 1)));

   if(Temp04 == "ai.as") goto Labl02;
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
     Maps0001.insert(std::pair < int32, std::time_t > (Temp04 == "ai.as" ? (-1) : (L_Numbering(string(Temp04, 0, Temp04.size() - 3))), Time01));
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
    if(Temp04 == "ai.as") full_script = true;
   }
   continue;
  }
 }
 int0 M_Cleaning() perfect
 {
  if(ScriptContext) ScriptContext->Release();
  if(ScriptEngine) ScriptEngine->Release();
 }