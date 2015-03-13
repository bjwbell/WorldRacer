/***************************************************************************
                          Object_Loader.h  -  description
                             -------------------
    begin                : Fri Aug 30 2002
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
    #ifndef Graphics
       #define Graphics
          #include <SDL/SDL.h>
          #include <GL/gl.h>
          #include <GL/glu.h>
          #include <GL/glext.h>
          #define GL_COMBINE_ARB						0x8570
          #define GL_RGB_SCALE_ARB					0x8573
          #include "Texture.h"
    #endif
	      #ifndef Functions
    #define Functions
    #include "Functions.h"
  #endif
	#include "Quad_Object.h"										// Called VERTEX

  typedef	struct										// Structure For An Object
{
 int		verts;									// Number Of Vertices For The Object
	int Num_Quads;
	VERTEX	*points;								// One Vertice (Vertex x,y & z)
	
} Points;										// Called OBJECT

 class Object{
    public:
     ~Object(){
      objfree();
    };

    void objload(char *name);							// Loads Object From File (name)
    bool Render();


   private:
    texture Texture1;
     void objfree();								// Frees The Object (Releasing The Memory)
        void objallocate(int n);							// Allocate Memory For Each Object
         int maxver;
		int num_quads;
    Points  Vertexes ;
	quad *Quad;

    void readstr(FILE *f,char *string);							// Reads A String From File (f)

};
