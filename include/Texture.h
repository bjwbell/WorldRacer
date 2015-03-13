/***************************************************************************
                          Texture.h  -  description
                             -------------------
    begin                : Mon Jul 1 2002
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
          //#include "Texture.h"
    #endif


#include <string>
class texture{
    public:
      bool LoadTexture(char* file);
      bool LoadFile(char* file);
	//   Gluint GetTexture();
      GLuint GetTexture();
    texture(){
          current++;
          cout<<"Creating Texture "<<current<<endl;
          this_texture=current;
    }
    private:
     static GLuint Texture[1000];
     static int current;
     int this_texture;
     string file;
};
