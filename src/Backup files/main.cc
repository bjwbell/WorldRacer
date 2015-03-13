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
#include "../include/Terrain.h"
 //#include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <iostream.h>
#include <stdlib.h>
#include "../include/Camera.h"
#include "../include/Light.h"
#include "../include/Object_Loader.h"  
SDL_Surface *screen;
SDL_Surface *background;
terrain Terrain;
camera Camera;
  double x;
  double y;
double z;
  bool right,left,up,down;
  vector LookAt;
 vector Position;

  texture Texture1,Texture2,Texture3,Texture4,Texture5,Texture6;
   Object Object1;




























static bool setup_opengl( int width, int height )
{
    float ratio = (float) width / (float) height;

    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );

    /* Setup our viewport. */
    glViewport( 0, 0, width, height );

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
    gluPerspective( 60.0, ratio, 1.0, 1024.0 );



     glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
      glEnable(GL_DEPTH_TEST);
	
   // cout<<"Texture Laoding "<<Texture1.LoadTexture("Texture1.tga")<<endl;
	/*Uint8 r,g,b;
	  SDL_Surface* background;
    vector vector_detail1,vector_detail2;
    vector_detail1.i=4;
    vector_detail1.j=2;
    vector_detail1.k=1;
    vector_detail2.i=1;
    vector_detail2.j=1;
    vector_detail2.k=1;


    Terrain.SetHeightMap("Test.bmp");
    Terrain.SetTexture1("Texture1.tga");
    Terrain.SetTexture2("Texture2.tga");
    Terrain.SetTexture1Detail(vector_detail1);
    Terrain.SetTexture2Detail(vector_detail2);




    cout<<"Texture Laoding "<<Texture1.LoadTexture("Texture1.tga")<<endl;
    Texture2.LoadTexture("Front.tga");
    Texture3.LoadTexture("Bottom.tga");
    Texture4.LoadTexture("Top.tga");
    Texture6.LoadTexture("Left.tga");
    Texture5.LoadTexture("Right.tga");

    Position.i=212;
    Position.j=30;
    Position.k=294;

    LookAt.i=186;
    LookAt.j=15;
    LookAt.k=171;
    Camera.SetPosition(Position);
    Camera.SetView(LookAt);*/
    // vector Position;


    //Position.k=2;
    //Position.i=0;
    //Position.j=1;
// Light.SetPosition(Position);
 //  Light.SetColor(GL_AMBIENT,0.05,0.05,0.05,1);
 //   Light.SetColor(GL_DIFFUSE,1,1,1,1);
   //glEnable(GL_LIGHT1);							// Enable Light One
   //  glEnable(GL_LIGHTING);		// Enable Lighting
  //Terrain.BuildTerrain();                      
  Object1.objload("data/box.txt");
   
   /*   maxver=0;                                                                       // Sets Max Vertices To 0 By Default
cout<<"Test1"<<endl;
   objload("data/box.txt",&morph1);                                             // Load The First Object Into morph1 From File sphere.txt
cout<<"Test2"<<endl;
        objload("data/torus.txt",&morph2);                                              // Load The Second Object Into morph2 From File torus.txt
        objload("data/tube.txt",&morph3); */                                              // Load The Third Object Into morph3 From File tube.txt

           

return true;
}














bool InitScene(){


	return true;
}




 void DrawScene(float t){
    //Position.k+=-100;
//Light.SetPosition(Position);
	 // Position.k+=100;
 //   vector vector1,vector2;
	static float x;
x+=0.1;
          glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );


glTranslatef(0,0.0f,-14.0f);
    static float angle;
    angle+=0.1;
    glRotatef(angle,1,1,0);
    Object1.Render();

      // cout<<"Test"<<endl;
 //     gluLookAt(12, 160, 294,  186, 55, 171,  0, 1, 0);	// This Determines The Camera's Position And View
  // Front Face
/* glTranslatef(0,0.0f,-5.0f);
 glRotatef(x,1,0,0);

//glColor3f(0.8,0.5,0.4);
  glBindTexture(GL_TEXTURE_2D, Texture1.GetTexture());				// Select A Texture Based On filter


glBegin(GL_QUADS);
 // Front Face
glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 1 (Front)
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 2 (Front)
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Front)
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 4 (Front)
// Back Face
glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Back)
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 2 (Back)
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 3 (Back)
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 4 (Back)
// Top Face
//vector1.i=2; vector1.j=0; vector1.k=0;
//vector2.i=0;vector2.j=0;vector2.k=2;
//vector vnormal=CreateNormal(vector1,vector2);
//cout<<vnormal.i<<" "<<vnormal.j<<" "<<vnormal.k<<endl;
glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 1 (Top)
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 2 (Top)
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Top)
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 4 (Top)
// Bottom Face
glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 2 (Bottom)
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 3 (Bottom)
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 4 (Bottom)
// Right face
glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 1 (Right)
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 2 (Right)
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Right)
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 4 (Right)
// Left Face
glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Left)
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 2 (Left)
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 3 (Left)
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 4 (Left)




glEnd();     */
 //     gluLookAt(12, 160, 294,  186, 55, 171,  0, 1, 0);	// This Determines The Camera's Position And View
 /* #define		HEIGHT_RATIO	1.5f				// Ratio That The Y Is Scaled According To The X And Z ( NEW )



       // glTranslatef(-100,-170,-200);
        if (left==true){
            x+=0.5;
            Position.i=Position.i-3.5;
        }
        if (right==true){
            x+=-0.5;
            Position.i=Position.i+3.5;

        }

          if (up==true){
            z+=0.5;
            Position.k=Position.k-3.5;
        }

         if (down==true){
          z+=-0.5;
          Position.k=Position.k+3.5;
          }

        LookAt.i=Position.i+0;
        LookAt.j=Position.j-0.5;
        LookAt.k=Position.k-1;
        Camera.SetView(LookAt);
        Camera.SetPosition(Position);
        Camera.PlaceCamera();
       glPushMatrix();

      glScalef(1, 0.05, 1);
       glPushAttrib(GL_ALL_ATTRIB_BITS);
      Terrain.Render();
      glPopAttrib();
 glPopMatrix();
 glPushAttrib(GL_ALL_ATTRIB_BITS);
glPushMatrix();
glEnable(GL_TEXTURE_2D);

CreateSkyBox(0, 0, 0, 1000, 400, 800,Texture1,Texture2,Texture3,Texture4,Texture5,Texture6);
 glPopAttrib();
  glPopMatrix();  */
	

}


     int main(int argc, char *argv[])
{


	SDL_Event event;
  atexit(SDL_Quit);
    if(SDL_Init(SDL_INIT_VIDEO)!= 0){
  		cout<<"error"<<endl;
  		return 1;
  }











  atexit(SDL_Quit);
        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  atexit(SDL_Quit);
screen=SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF|SDL_OPENGL);


// screen=SDL_SetVideoMode(640,480,32,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_HWSURFACE);
  //screen=SDL_SetVideoMode(640,480,32,SDL_DOUBLEBUF);
  //InitScene();
  if(setup_opengl(640,480)!=0){
  	while(true){
  		if(SDL_PollEvent(&event)!=0){
  				switch(event.type){
  					case SDL_QUIT:
  						exit(0);
					  				case SDL_KEYUP:

					if(event.key.keysym.sym==SDLK_ESCAPE){
					exit(0);
					}






					if(event.key.keysym.sym==SDLK_DOWN){
					     down=false;
					//	Man_Event.SignalEvent(Key_Up,(void*)&"Down",0);

					}
					if(event.key.keysym.sym==SDLK_UP){
					   up=false;
						//Man_Event.SignalEvent(Key_Up,(void*)&"Up",0);
					}
					if(event.key.keysym.sym==SDLK_LEFT){
						 left=false;
						//Man_Event.SignalEvent(Key_Up,(void*)&"Left",0);

					}
					if(event.key.keysym.sym==SDLK_RIGHT){
						 right=false;
						//Man_Event.SignalEvent(Key_Up,(void*)&"Right",0);

					}


					break;

				case SDL_KEYDOWN:
					if(event.key.keysym.sym==SDLK_DOWN){
				      down=true;

						//Man_Event.SignalEvent(Key_Down,(void*)&"Down",0);


					}
					if(event.key.keysym.sym==SDLK_UP){
						up=true;
						//Man_Event.SignalEvent(Key_Down,(void*)&"Up",0);
					}
					if(event.key.keysym.sym==SDLK_LEFT){
						 left=true;
						//Man_Event.SignalEvent(Key_Down,(void*)&"Left",0);

					}
					if(event.key.keysym.sym==SDLK_RIGHT){
						 right=true;
						//Man_Event.SignalEvent(Key_Down,(void*)&"Right",0);

					}
					break;





				}




			}else{



			DrawScene(0);




  			    SDL_GL_SwapBuffers( );
			}

  	}
  }else{
  		exit(1);
  }

  return EXIT_SUCCESS;
//	return 10;
}
