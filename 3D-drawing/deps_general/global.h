#pragma once

//#define NODEBUG //redundent -- now defined in makefile for debug builds

#define player_camera
//#define vsync





#ifndef NODEBUG
	#define timing
	#ifdef timing
		#define detailed_timing
	#endif

	#define gore_detail
	//#define framerate
#endif


#ifndef player_camera
	#define precalculated_player_camera
#endif

#ifdef precalculated_player_camera
	//#define mod_frame //no longer used -- relevant code deleted
#endif
