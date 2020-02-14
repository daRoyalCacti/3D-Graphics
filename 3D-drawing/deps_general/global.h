#pragma once


//#define NODEBUG //redundent -- now defined in makefile for debug builds

//#define player_camera	//if the controls are similar to a video game -- undef for precalculated camera (files in 'camera' folder)
//#define vsync		//is currently broken
#define frame_init_increase	//if framerate increments itself by default -- should be the default
#define naive_recording

//for debugging
//#define log_frame_no			//logs the current frame number to standard output
//#define log_camera_vecs			//logs the camera vectors to standard output





#ifndef NODEBUG
	#define timing		//logs timing of major events to standard output
	#ifdef timing
		#define detailed_timing		//logs timing of more minor events to standard output
	#endif

	//#define gore_detail	//logs details useful for updating
	//#define framerate	//prints the framerate to standard output -- only used for debugging (reduces usability)
#endif

#ifdef naive_recording
	#ifndef log_frame_no
		#define log_frame_no	//logging the frame number if recording is enabled
	#endif
#endif

//do not remove
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
	#ifdef precalculated_player_camera
		extern uint32_t total_frames;
	#endif
}
