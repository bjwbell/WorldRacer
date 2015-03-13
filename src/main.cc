/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Jul  6 11:27:50 PDT 2002
    copyright            : (C) 2002 by Bryan Bell
    email                : Bryan@localhost.localdomain
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>

#endif
    #ifndef Graphics
       #define Graphics
          #include <SDL/SDL.h>
          #include <GL/gl.h>
          #include <GL/glu.h>
          #include <GL/glext.h>
          #define GL_COMBINE_ARB						0x8570
          #define GL_RGB_SCALE_ARB					0x8573
          #include "../include/Texture.h"
    #endif

	//	#include "../include/Terrain.h"
     #ifndef Functions
    #define Functions
    #include "../include/Functions.h"
  #endif

 //#include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <iostream.h>
#include <stdlib.h>

# include <GL/glx.h>

#include "../include/Light.h"
#include "../include/Object_Loader.h"  
//#include "../include/Functions.h"
//#include "../include/display_text.h"
#include "../include/Md3.h"
#include "../include/Game_Class.h"
SDL_Surface *screen;
SDL_Surface *background;
//terrain Terrain;
camera Camera;
  double x;
  double y;
double z;
  bool right,left,up,down;
  phy_vector LookAt;
 phy_vector Position;

 // texture Texture1,Texture2,Texture3,Texture4,Texture5,Texture6;
   Object Object1;
PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;
/*#define MODEL_PATH  "tux"              // This stores the folder name the character is in
#define MODEL_NAME  "tux"              // This stores the prefix for all the character files
#define GUN_NAME    "Railgun"           // This stores the name of our gun to load

CModelMD3 g_Model;                      // This is our global md3 character model instance
// texture Texture1,Texture2,Texture3,Texture4,Texture5,Texture6;*/

game Game1;





















static bool setup_opengl( int width, int height )
{
    float ratio = (float) width / (float) height;

    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    
	glCullFace(GL_FRONT);
    /* Set the clear color. */
    glClearColor( 1, 1, 1, 1 );

    /* Setup our viewport. */
    glViewport( 0, 0, width, height );

    glEnable(GL_NORMALIZE);
	/*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    /*
     * EXERCISE:
     * Replace this with a call to glFrustum.
     */
    gluPerspective( 60.0, ratio, 1.0, 8024.0 );



     glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
      glEnable(GL_DEPTH_TEST);
	Game1.Set_Player_Model("tux","tux");
	screen_dimension D;
	D.width=width;D.height=height;
	Game1.Init(D);
               





return true;
}














bool InitScene(){


	return true;
}




 void DrawScene(float t){


     glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
	

	 Game1.UpdateScene();
	
	 Game1.Render();

 
	

}


     int main(int argc, char *argv[])
{


	SDL_Event event;
  atexit(SDL_Quit);
    if(SDL_Init(SDL_INIT_VIDEO)!= 0){
  		cout<<"error"<<endl;
  		return 1;
  }









glFogCoordfEXT  =  (PFNGLFOGCOORDFEXTPROC) glXGetProcAddressARB((const GLubyte *)"glFogCoordfEXT");

  atexit(SDL_Quit);
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,8);
  atexit(SDL_Quit);
screen=SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF|SDL_OPENGL|SDL_FULLSCREEN);

SDL_ShowCursor(SDL_DISABLE);
// screen=SDL_SetVideoMode(640,480,32,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_HWSURFACE);
  //screen=SDL_SetVideoMode(640,480,32,SDL_DOUBLEBUF);
  //InitScene();
  if(setup_opengl(640,480)!=0){
  	while(true){
  		if(SDL_PollEvent(&event)!=0){
  				switch(event.type){
  					case SDL_QUIT:
  						//KillFont();
						exit(0);
					case SDL_KEYUP:

						if(event.key.keysym.sym==SDLK_ESCAPE){
							//KillFont();
							exit(0);
						}
						Game1.Set_Key_Pressed(event,false);







					break;

				case SDL_KEYDOWN:
					Game1.Set_Key_Pressed(event,true);


					
					break;





				}




			}else{

			static double t1;
			static double t2;
			//if(t1!=0){
			t2=SDL_GetTicks();
			//}
			DrawScene(t2-t1);
			t1=SDL_GetTicks();



  			    SDL_GL_SwapBuffers( );
			}

  	}
  }else{
  		//KillFont();
	  exit(1);
  }

  return EXIT_SUCCESS;
//	return 10;
}
