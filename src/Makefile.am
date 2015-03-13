## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES =

CFLAGS =\
	`sdl-config --cflags --libs`\
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wuninitialized -Wparentheses -Wtraditional -Wpointer-arith -Wmissing-prototypes\
	 -O1\
	 -g

CXXFLAGS =\
	`sdl-config --cflags --libs`\
	 -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wuninitialized -Wparentheses -Wtraditional -Wpointer-arith -Wmissing-prototypes\
	 -O1\
	 -g

bin_PROGRAMS = pod_racer_clone

pod_racer_clone_SOURCES = \
	Camera.cpp\
	Functions.cpp\
	Game_Class.cc\
	Light.cpp\
	MD3Functions.cpp\
	Md3.cpp\
	Object_Loader.cpp\
	Quad_Object.cpp\
	Terrain.cpp\
	Texture.cpp\
	main.cc\
	tga.c\
	player.cpp\
	path.cc\
	HUD.cpp\
	Speed_Display.cc\
	display_text.cpp\
	Track_Marker.cpp\
	track_selection.cpp\
	World.cpp\
	Bush.cpp\
	Bushes.cpp\
	terrain_object.cpp\
	terrain_objects.cpp\
	terrain_reflection_map.cpp

pod_racer_clone_LDFLAGS = 

pod_racer_clone_LDADD = \
	 -lGL -lGLU

