#pragma once


//#define NODEBUG //redundent -- now defined in makefile for debug builds

#define player_camera
//#define vsync		//is currently broken
//#define frame_init_increase




#ifndef NODEBUG
	#define timing
	#ifdef timing
		#define detailed_timing
	#endif

	//#define gore_detail
	//#define framerate
#endif


#ifndef player_camera
	#define precalculated_player_camera
#endif

#ifdef precalculated_player_camera
	//#define mod_frame //no longer used -- relevant code deleted
#endif

#include "player_camera.h"
namespace global {
	extern playerCamera camera;
	extern bool increase_frames;
	extern uint64_t framecounter;	//will essentially never overflow - 5.6*10^6 millenia at 60fps
}
