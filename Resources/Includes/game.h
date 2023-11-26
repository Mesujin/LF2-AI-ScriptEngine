////////////////////////////////////////////////////////////////////////////////////////////
// "game.h", list of game data access.                                                    //
//                                                                                        //
// No comment.                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _AISCRIPT_PRAGMA_GAME_H
 #define _AISCRIPT_PRAGMA_GAME_H
 
 // Commands
  #include "platform.h"

 // Structure/Class
  typedef struct AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY
  {
   int32 dvx;        // +0x00 | Value : game.objects[].data.strength.entry[].dvx      / game.files.datas[].strength.entry[].dvx
   int32 dvy;        // +0x04 | Value : game.objects[].data.strength.entry[].dvy      / game.files.datas[].strength.entry[].dvy
   int32 fall;       // +0x08 | Value : game.objects[].data.strength.entry[].fall     / game.files.datas[].strength.entry[].fall
   int32 arest;      // +0x0C | Value : game.objects[].data.strength.entry[].arest    / game.files.datas[].strength.entry[].arest
   int32 vrest;      // +0x10 | Value : game.objects[].data.strength.entry[].vrest    / game.files.datas[].strength.entry[].vrest
   int32 respond;    // +0x14 | Value : game.objects[].data.strength.entry[].respond  / game.files.datas[].strength.entry[].respond
   int32 effect;     // +0x18 | Value : game.objects[].data.strength.entry[].effect   / game.files.datas[].strength.entry[].effect
   int8  unkwn1[20]; // +0x1C         : game.objects[].data.strength.entry[].unkwn1[] / game.files.datas[].strength.entry[].unkwn1[]
   int32 bdefend;    // +0x30 | Value : game.objects[].data.strength.entry[].bdefend  / game.files.datas[].strength.entry[].bdefend
   int32 injury;     // +0x34 | Value : game.objects[].data.strength.entry[].injury   / game.files.datas[].strength.entry[].injury
   int32 zwidth;     // +0x38 | Value : game.objects[].data.strength.entry[].zwidth   / game.files.datas[].strength.entry[].zwidth
   int8  unkwn2[20]; // +0x3C         : game.objects[].data.strength.entry[].unkwn2[] / game.files.datas[].strength.entry[].unkwn2[]
  } AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY;
  typedef struct AISCRIPT_GAME_FILE_DATA_STRENGTH
  {
   AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY entry[9];

   int8 entry_name[5][30]; // The size was actually [10][30], but considering you'll use "file_Address" or etc, then it supposed to be [5][30].
   int8 unkwn1[30];
  } AISCRIPT_GAME_FILE_DATA_STRENGTH;
  typedef struct AISCRIPT_GAME_FILE_DATA_FILE
  {
   int32 ptr[10];
   int32 w[10];
   int32 h[10];
   int32 row[10];
   int32 col[10];
  } AISCRIPT_GAME_FILE_DATA_FILE;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME_BPOINT
  {
   int32 x;
   int32 y;
  } AISCRIPT_GAME_FILE_DATA_FRAME_BPOINT;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT
  {
   int32 kind;
   int32 x;
   int32 y;
   int32 injury; //if its kind 2 this is fronthurtact
   int32 cover; // if its kind 2 this is backhurtact
   int32 vaction;
   int32 aaction;
   int32 jaction;
   int32 daction;
   int32 throwvx;
   int32 throwvy;
   int32 hurtable;
   int32 decrease;
   int32 dircontrol;
   int32 taction;
   int32 throwinjury;
   int32 throwvz;
  } AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT
  {
   int32 kind;
   int32 x;
   int32 y;
   int32 weaponact;
   int32 attacking;
   int32 cover;
   int32 dvx;
   int32 dvy;
   int32 dvz;
  } AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT
  {
   int32 kind;
   int32 x;
   int32 y;
   int32 action;
   int32 dvx;
   int32 dvy;
   int32 oid;
   int32 facing;
  } AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME_ITR
  {
   int32 kind;
   int32 x;
   int32 y;
   int32 w;
   int32 h;
   int32 dvx;
   int32 dvy;
   int32 fall;
   int32 arest;
   int32 vrest;
   int32 respond;
   int32 effect;
   int32 catchingact1;
   int32 catchingact2;
   int32 caughtact1;
   int32 caughtact2;
   int32 bdefend;
   int32 injury;
   int32 zwidth;
   int32 unkwn1;
  } AISCRIPT_GAME_FILE_DATA_FRAME_ITR;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME_BDY
  {
   int32 kind;
   int32 x;
   int32 y;
   int32 w;
   int32 h;
   int32 unkwn1;
   int32 unkwn2;
   int32 unkwn3;
   int32 unkwn4;
   int32 unkwn5;
  } AISCRIPT_GAME_FILE_DATA_FRAME_BDY;
  typedef struct AISCRIPT_GAME_FILE_DATA_FRAME
  {
   int8  exists;
   int32 pic;
   int32 state;
   int32 wait;
   int32 next;
   int32 dvx;
   int32 dvy;
   int32 dvz;
   int32 unkwn1;
   int32 hit_a;
   int32 hit_d;
   int32 hit_j;
   int32 hit_Fa;
   int32 hit_Ua;
   int32 hit_Da;
   int32 hit_Fj;
   int32 hit_Uj;
   int32 hit_Dj;
   int32 hit_ja;
   int32 mp;
   int32 centerx;
   int32 centery;
   
   AISCRIPT_GAME_FILE_DATA_FRAME_OPOINT opoint;

   int32 unkwn2;
   int32 unkwn3;

   AISCRIPT_GAME_FILE_DATA_FRAME_BPOINT bpoint;
   AISCRIPT_GAME_FILE_DATA_FRAME_CPOINT cpoint;
   
   int32 unkwn4;
   int32 unkwn5;
   int32 unkwn6;
   
   AISCRIPT_GAME_FILE_DATA_FRAME_WPOINT wpoint;
   
   int32 unkwn7;
   int32 unkwn8;
   int32 unkwn9;
   int32 unkwn10;
   int32 unkwn11;
   int32 unkwn12;
   int32 unkwn13;
   int32 unkwn14;
   int32 unkwn15;
   int32 unkwn16;
   int32 unkwn17;
   int32 itr_count;
   int32 bdy_count;

   AISCRIPT_GAME_FILE_DATA_FRAME_ITR *itrs;
   AISCRIPT_GAME_FILE_DATA_FRAME_BDY *bdys;
	
   //vv these values form a rectangle that holds all itrs/bdys within it
   int32 itr_x;
   int32 itr_y;
   int32 itr_w;
   int32 itr_h;
   int32 bdy_x;
   int32 bdy_y;
   int32 bdy_w;
   int32 bdy_h;
	
   int32 unkwn18;
   int8  fname[20];
   int8  (*sound)[20];
   int32 unkwn19;
  } AISCRIPT_GAME_FILE_DATA_FRAME;
  typedef struct AISCRIPT_GAME_FILE_DATA
  {
   int32  walking_frame_rate;
   int32  unkwn1;
   xint64 walking_speed;
   xint64 walking_speedz;
   int32  running_frame_rate;
   xint64 running_speed;
   xint64 running_speedz;
   xint64 heavy_walking_speed;
   xint64 heavy_walking_speedz;
   xint64 heavy_running_speed;
   xint64 heavy_running_speedz;
   xint64 jump_height;
   xint64 jump_distance;
   xint64 jump_distancez;
   xint64 dash_height;
   xint64 dash_distance;
   xint64 dash_distancez;
   xint64 rowing_height;
   xint64 rowing_distance;
   int32  weapon_hp;
   int32  weapon_drop_hurt;
   int8   unkwn2[124];

   AISCRIPT_GAME_FILE_DATA_STRENGTH strength;

   int32  file_count;                     // This is just a redudant, changing it won't affect anything.
   int8   file_address[10][40];           // This is just a redudant, changing it won't affect anything.
   AISCRIPT_GAME_FILE_DATA_FILE file[1];  // This is just a redudant, changing it won't affect anything.

   int32  id;
   int32  type;
   int8   unkwn3[4];
   int8   small_bmp[40];
   int8   unkwn4[4];
   int8   face_bmp[40];
   int8   unkwn5[80];

   AISCRIPT_GAME_FILE_DATA_FRAME frames[_AISCRIPT_MAXOBJECTFRAMES];

   int8   name[12];
  } AISCRIPT_GAME_FILE_DATA;
  typedef struct AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN
  {
   int8   unkwn1[172]; // Seems to have something to do with bosses, is changed during game so I believe it keeps track of whether or not soldiers should respawn.
   int32  id;
   int32  x;
   int32  hp;
   int32  times;
   int32  reserve;
   int32  join;
   int32  join_reserve;
   int32  act;
   int32  y;
   xint64 ratio;
   int32  role;       // 0 = Normal; 1 = "soldier"; 2 = "boss".
   int8   unkwn2[4];
  } AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN;
  typedef struct AISCRIPT_GAME_FILE_STAGE_PHASE
  {
   int32 bound;
   int8  music[52];

   AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN spawns[60];

   int32 when_clear_goto_phase;
  } AISCRIPT_GAME_FILE_STAGE_PHASE;
  typedef struct AISCRIPT_GAME_FILE_STAGE
  {
   int32 phase_count;

   AISCRIPT_GAME_FILE_STAGE_PHASE phases[100];
  } AISCRIPT_GAME_FILE_STAGE;
  typedef struct AISCRIPT_GAME_FILE_BACKGROUND_LAYER
  {
   #if _AISCRIPT_FORDARKFIRENEXE
    int32  transparency[100]; // 0x445 | Value   : game.files.get_backgrounds()[].layer[].transparency
    int32  width[100];        // 0x4BD | Value   : game.files.get_backgrounds()[].layer[].width
    int32  x[100];            // 0x535 | Value   : game.files.get_backgrounds()[].layer[].x
    int32  y[100];            // 0x5AD | Value   : game.files.get_backgrounds()[].layer[].y
    int32  height[100];       // 0x625 | Value   : game.files.get_backgrounds()[].layer[].height
    int32  loop[100];         // 0x69D | Value   : game.files.get_backgrounds()[].layer[].loop
    int32  c1[100];           // 0x715 | Value   : game.files.get_backgrounds()[].layer[].c1
    int32  c2[100];           // 0x78D | Value   : game.files.get_backgrounds()[].layer[].c2
    int32  cc[100];           // 0x805 | Value   : game.files.get_backgrounds()[].layer[].cc
    int32  animation[100];    // 0x87D | Counter : game.files.get_backgrounds()[].layer[].animation
    int32  rect[100];         // 0x8F5 | Value   : game.files.get_backgrounds()[].layer[].rect
   #else
    int32  transparency[30]; // 0x445 | Value   : game.files.get_backgrounds()[].layer[].transparency
    int32  width[30];        // 0x4BD | Value   : game.files.get_backgrounds()[].layer[].width
    int32  x[30];            // 0x535 | Value   : game.files.get_backgrounds()[].layer[].x
    int32  y[30];            // 0x5AD | Value   : game.files.get_backgrounds()[].layer[].y
    int32  height[30];       // 0x625 | Value   : game.files.get_backgrounds()[].layer[].height
    int32  loop[30];         // 0x69D | Value   : game.files.get_backgrounds()[].layer[].loop
    int32  c1[30];           // 0x715 | Value   : game.files.get_backgrounds()[].layer[].c1
    int32  c2[30];           // 0x78D | Value   : game.files.get_backgrounds()[].layer[].c2
    int32  cc[30];           // 0x805 | Value   : game.files.get_backgrounds()[].layer[].cc
    int32  animation[30];    // 0x87D | Counter : game.files.get_backgrounds()[].layer[].animation
    int32  rect[30];         // 0x8F5 | Value   : game.files.get_backgrounds()[].layer[].rect
   #endif
  } AISCRIPT_GAME_FILE_BACKGROUND_LAYER;
  typedef struct AISCRIPT_GAME_FILE_BACKGROUND
  {
   int32  bg_width;             // +0x000 | Value   : game.files.get_backgrounds()[].bg_width
   int32  bg_zwidth1;           // +0x004 | Value   : game.files.get_backgrounds()[].bg_zwidth1
   int32  bg_zwidth2;           // +0x008 | Value   : game.files.get_backgrounds()[].bg_zwidth2
   int32  perspective1;         // +0x00C | Value   : game.files.get_backgrounds()[].perspective1
   int32  perspective2;         // +0x010 | Value   : game.files.get_backgrounds()[].perspective2
   int32  shadow1;              // +0x014 | Value   : game.files.get_backgrounds()[].shadow1
   int32  shadow2;              // +0x018 | Value   : game.files.get_backgrounds()[].shadow2
   int32  layer_count;          // +0x01C | Value   : game.files.get_backgrounds()[].layer_count
   #if _AISCRIPT_FORDARKFIRENEXE
    int8   layer_bmps[100][30]; // +0x020 | Address : game.files.get_backgrounds()[].layer_bmps[][]
   #else
    int8   layer_bmps[30][30];  // +0x020 | Address : game.files.get_backgrounds()[].layer_bmps[][]
   #endif
   int8   shadow_bmp[30];       // +0x3A4 | Address : game.files.get_backgrounds()[].shadow_bmp[]
   int8   unkwn1[10];           // +0x41C           : game.files.get_backgrounds()[].unkwn1[]
   int8   name[30];             // +0x426 | String  : game.files.get_backgrounds()[].name[]
   int8   unkwn2;               // +0x444           : game.files.get_backgrounds()[].unkwn2[]

   AISCRIPT_GAME_FILE_BACKGROUND_LAYER layer;  // [+0x445] | Struct : game.files.get_backgrounds()[].layer[]
   
   #if _AISCRIPT_FORDARKFIRENEXE
    int32  layer_ptrs[100];     // +0x96D | Pointer : game.files.get_backgrounds()[].layer_ptrs[]
   #else
    int32  layer_ptrs[30];      // +0x96D | Pointer : game.files.get_backgrounds()[].layer_ptrs[]
   #endif
   int32  ptrs;                 // +0x9E5 | Pointer : game.files.get_backgrounds()[].ptrs
  } AISCRIPT_GAME_FILE_BACKGROUND;
  typedef struct AISCRIPT_GAME_FILE
  {
   AISCRIPT_GAME_FILE_DATA       *datas[500];                       //
   AISCRIPT_GAME_FILE_STAGE      stages[_AISCRIPT_MAXSTAGESIDSLOT]; //
   AISCRIPT_GAME_FILE_BACKGROUND backgrounds[50];                   //
  } AISCRIPT_GAME_FILE;
  typedef struct AISCRIPT_GAME_OBJECT
  {
   int32  move_counter;      // Walk Animation | Counter : game.objects[].move_counter
   int32  run_counter;       // Run Animation  | Counter
   int32  blink;             // Invisibility   | Value
   int32  unkwn1;            //
   int32  x;                 // X-Axis Display Position | Value
   int32  y;                 // Y-Axis Display Postiion | Value
   int32  z;                 // Z-Axis Display Postiion | Value
   int8   unkwn2[12];        //
   xint64 x_acceleration;    // X-Axis Velocity Accumulation | Value
   xint64 y_acceleration;    // Y-Axis Velocity Accumulation | Value
   xint64 z_acceleration;    // Z-Axis Velocity Accumulation | Value
   xint64 x_velocity;        // X-Axis Velocity              | Value
   xint64 y_velocity;        // Y-Axis Velocity              | Value
   xint64 z_velocity;        // Z-Axis Velocity              | Value
   xint64 x_real;            // X-Axis Position              | Value
   xint64 y_real;            // Y-Axis Position              | Value
   xint64 z_real;            // Z-Axis Position              | Value
   int32  frame1;            // Main Frame                   | Value
   int32  frame2;            // Frame Before Hit             | Value
   int32  frame3;            // Calc Frame                   | Value
   int32  frame4;            // Last Frame                   | Value
   int8   facing;            // Facing                       | Value
   int8   unkwn3[7];         //
   int32  wait_counter;      // Frame Wait Counter   | Counter
   int32  ccatching;         // Catching             | ObjNum
   int32  ccatcher;          // Caught by            | ObjNum
   int32  ctimer;            // Catching Decrease    | Counter  
   int32  weapon_type;       // Held Object's Type   | Value
   int32  weapon_held;       // Held Object's ObjNum | ObjNum
   int32  weapon_holder;     // Held by              | ObjNum
   int32  unkwn4;            //
   int8   unkwn5[8];         //
   int32  fall;              // Fall / Injury Effect | Counter
   int32  shake;             // Hitlag               | Counter
   int32  bdefend;           // Defend Breakness     | Counter
   int8   unkwn6[10];        //
   int8   holding_up;        // Hold Input  | Value
   int8   holding_down;      // Hold Input  | Value
   int8   holding_left;      // Hold Input  | Value
   int8   holding_right;     // Hold Input  | Value
   int8   holding_a;         // Hold Input  | Value
   int8   holding_j;         // Hold Input  | Value
   int8   holding_d;         // Hold Input  | Value
   int8   up;                // Press Input | Value
   int8   down;              // Press Input | Value
   int8   left;              // Press Input | Value
   int8   right;             // Press Input | Value
   int8   A;                 // Press Input | Value
   int8   J;                 // Press Input | Value
   int8   D;                 // Press Input | Value
   int8   DrA;               // Cast Input  | Value
   int8   DlA;               // Cast Input  | Value
   int8   DuA;               // Cast Input  | Value
   int8   DdA;               // Cast Input  | Value
   int8   DrJ;               // Cast Input  | Value
   int8   DlJ;               // Cast Input  | Value
   int8   DuJ;               // Cast Input  | Value
   int8   DdJ;               // Cast Input  | Value
   int8   DJA;               // Cast Input  | Value
   int8   unkwn7[3];         //
   int32  heal;              // Heal Point | Value & Counter
   int8   unkwn8[8];         //

   int32  arest;                             // Applied arest | Counter
   int8   vrests[_AISCRIPT_MAXOBJECTNUMBER]; // vrest Counter | Counter
   int32  attacked_object_num;               // Last Hit by   | ObjNum
                              
   int8   unkwn9[112];       //
   int32  clone;             // Clone by               | ObjNum
   int32  weapon_thrower;    // Thrown by              | ObjNum
   int32  hp;                // Health Point           | Value
   int32  dark_hp;           // Potential Health Point | Value
   int32  max_hp;            // Maximum Health Point   | Value
   int32  mp;                // Mana Point             | Value
   int32  reserve;           // Reserve Counter        | Counter
   int32  unkwn10;           //
   int32  unkwn11;           //
   int32  pic_gain;          // pic Offside        | Value
   int32  bottle_hp;         // Drink Point        | Value
   int32  throwinjury;       // Thrown Drop Damage | Value
   int8   unkwn12[20];       // 
   int32  firzen_counter;    // Firzen Transforming Counter | Counter
   int32  unkwn13;           //
   int32  armour_multiplier; // Defense / Damage Taken Ratio | Value
   int32  unkwn14;           //
   int32  total_attack;      // Summary - Damage Dealt     | Value
   int32  hp_lost;           // Summary - Damage Taken     | Value
   int32  mp_usage;          // Summary - Mana Point Usage | Value
   int32  host;              // Summary - Host             | ObjNum
   int32  kills;             // Summary - Total Kill       | Value
   int32  weapon_picks;      // Summary - Total Pick       | Value
   int32  enemy;             // Target                     | ObjNum
   int32  team;              // Team                       | Value

   AISCRIPT_GAME_FILE_DATA *data; // Address to data.
  } AISCRIPT_GAME_OBJECT;
  typedef struct AISCRIPT_GAME
  {
   int32 state;                                              // +0x4
   int8  exists[_AISCRIPT_MAXOBJECTNUMBER];                  // +0x194
   AISCRIPT_GAME_OBJECT *objects[_AISCRIPT_MAXOBJECTNUMBER]; // +0x7D4
   AISCRIPT_GAME_FILE   *files;                              // +0xFA4
  } AISCRIPT_GAME;
  typedef struct AISCRIPT_INFO
  {
   int32  num, id, type;
   int32  x, y, z;
   xint64 x_real, y_real, z_real;
   xint64 x_velocity, y_velocity, z_velocity;
   int8   facing;
   int8   holding_up, holding_left, holding_down, holding_right, holding_a, holding_d, holding_j;
   int8   up, left, down, right, A, D, J;
   int8   DrA, DlA, DuA, DdA, DrJ, DlJ, DuJ, DdJ, DJA;
   int32  hp, dark_hp, max_hp, mp;
   int32  frame;
   int32  bdefend;
   int32  fall;
   int32  team;
   int32  blink;
   int32  state;
   int32  weapon_type, weapon_held, weapon_holder;
   int32  shake;
   int32  wait_counter;
   int32  ctimer;
   int32  arest;
   int8   vrests[_AISCRIPT_MAXOBJECTNUMBER];
   int32  vrest; // Backwards compatibility.
   int32  clone;
   int32  reserve;
   AISCRIPT_GAME_FILE_DATA *data;
   AISCRIPT_VECTOR position;
   AISCRIPT_VECTOR velocity;

   AISCRIPT_INFO(){num = -1; type = -1; RefCount = 1;}
   AISCRIPT_INFO(int32 object_num){AISCRIPT_INFO(); operator=(object_num);}
   AISCRIPT_INFO(statics AISCRIPT_INFO &info){AISCRIPT_INFO(); operator=(info.num);}

   void AddRef(){RefCount++;}
   void RelRef(){if(--RefCount == 0) delete this;}

   int32 operator= (int32 object_num);
   int32 operator= (statics AISCRIPT_INFO &info){return operator=(info.num);}
   int32 operator+=(int32 object_num){return operator=(num + object_num);}
   int32 operator+=(statics AISCRIPT_INFO &info){return operator=(num + info.num);}
   int32 operator-=(int32 object_num){return operator=(num - object_num);}
   int32 operator-=(statics AISCRIPT_INFO &info){return operator=(num - info.num);}
   int32 operator++(){return operator=(num + 1);}
   int32 operator--(){return operator=(num - 1);}

   private:
    uint32 RefCount;
  } AISCRIPT_INFO;

  // Index Control
   struct AISCRIPT_ARRAY_INT1       {int1  *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_INT8       {int8  *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_INT32      {int32 *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_ARRAY_INT8 {template < int32 Vrab01 > AISCRIPT_ARRAY_INT8 *opIndex(uint32) perfect;};

   struct AISCRIPT_ARRAY_OBJECT     {AISCRIPT_GAME_OBJECT                   *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_DATA       {AISCRIPT_GAME_FILE_DATA                *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_FILE       {AISCRIPT_GAME_FILE_DATA_FILE           *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_ENTRY      {AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_FRAME      {AISCRIPT_GAME_FILE_DATA_FRAME          *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_ITR        {AISCRIPT_GAME_FILE_DATA_FRAME_ITR      *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_BDY        {AISCRIPT_GAME_FILE_DATA_FRAME_BDY      *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_BACKGROUND {AISCRIPT_GAME_FILE_BACKGROUND          *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_LAYER      {AISCRIPT_GAME_FILE_BACKGROUND_LAYER    *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_STAGE      {AISCRIPT_GAME_FILE_STAGE               *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_PHASE      {AISCRIPT_GAME_FILE_STAGE_PHASE         *opIndex(uint32) perfect;};
   struct AISCRIPT_ARRAY_SPAWN      {AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN   *opIndex(uint32) perfect;};

   #pragma warning (disable : 26481) // We're safe to access any offset in this case.
   template < int32 Vrab01 > int0                *Index(int0 *Vrab02)                               perfect {return (int0*)((int8*)Vrab02 + Vrab01);} // AngelScript does not support offsets larger than 0x7fff, and when that is the case, we use this function instead.
   int1                                          *AISCRIPT_ARRAY_INT1::opIndex(uint32 Vrab01)       perfect {return (((int1*)this) + Vrab01);}
   int8                                          *AISCRIPT_ARRAY_INT8::opIndex(uint32 Vrab01)       perfect {return (((int8*)this) + Vrab01);}
   int32                                         *AISCRIPT_ARRAY_INT32::opIndex(uint32 Vrab01)      perfect {return (((int32*)this) + Vrab01);}
   template < int32 Vrab01 > AISCRIPT_ARRAY_INT8 *AISCRIPT_ARRAY_ARRAY_INT8::opIndex(uint32 Vrab02) perfect {return (AISCRIPT_ARRAY_INT8*)(((int8*)this) + (Vrab02 * Vrab01));}
   AISCRIPT_GAME_OBJECT                          *AISCRIPT_ARRAY_OBJECT::opIndex(uint32 Vrab01)     perfect {return *(((AISCRIPT_GAME_OBJECT**)this) + Vrab01);}
   AISCRIPT_GAME_FILE_DATA                       *AISCRIPT_ARRAY_DATA::opIndex(uint32 Vrab01)       perfect {return *(((AISCRIPT_GAME_FILE_DATA**)this) + Vrab01);}
   AISCRIPT_GAME_FILE_DATA_FILE                  *AISCRIPT_ARRAY_FILE::opIndex(uint32 Vrab01)       perfect {return (AISCRIPT_GAME_FILE_DATA_FILE*)(((int32*)this) + Vrab01);}
   AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY        *AISCRIPT_ARRAY_ENTRY::opIndex(uint32 Vrab01)      perfect {return ((AISCRIPT_GAME_FILE_DATA_STRENGTH_ENTRY*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_DATA_FRAME                 *AISCRIPT_ARRAY_FRAME::opIndex(uint32 Vrab01)      perfect {return ((AISCRIPT_GAME_FILE_DATA_FRAME*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_DATA_FRAME_ITR             *AISCRIPT_ARRAY_ITR::opIndex(uint32 Vrab01)        perfect {return ((AISCRIPT_GAME_FILE_DATA_FRAME_ITR*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_DATA_FRAME_BDY             *AISCRIPT_ARRAY_BDY::opIndex(uint32 Vrab01)        perfect {return ((AISCRIPT_GAME_FILE_DATA_FRAME_BDY*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_BACKGROUND                 *AISCRIPT_ARRAY_BACKGROUND::opIndex(uint32 Vrab01) perfect {return ((AISCRIPT_GAME_FILE_BACKGROUND*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_BACKGROUND_LAYER           *AISCRIPT_ARRAY_LAYER::opIndex(uint32 Vrab01)      perfect {return (AISCRIPT_GAME_FILE_BACKGROUND_LAYER*)(((int32*)this) + Vrab01);}
   AISCRIPT_GAME_FILE_STAGE                      *AISCRIPT_ARRAY_STAGE::opIndex(uint32 Vrab01)      perfect {return ((AISCRIPT_GAME_FILE_STAGE*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_STAGE_PHASE                *AISCRIPT_ARRAY_PHASE::opIndex(uint32 Vrab01)      perfect {return ((AISCRIPT_GAME_FILE_STAGE_PHASE*)this) + Vrab01;}
   AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN          *AISCRIPT_ARRAY_SPAWN::opIndex(uint32 Vrab01)      perfect {return ((AISCRIPT_GAME_FILE_STAGE_PHASE_SPAWN*)this) + Vrab01;}
#endif
