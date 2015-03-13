/***************************************************************************
                          Camera.h  -  description
                             -------------------
    begin                : Thu Jul 11 2002
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
  class camera {
      public:

         bool SetPosition(phy_vector Position);
         bool SetView(phy_vector Look_At);
         bool SetUpVector(phy_vector Up_Vector);
         phy_vector GetPosition();
         phy_vector GetView();
         phy_vector GetUpVector();
         bool PlaceCamera();
		 void Rotate(float Rotation,float x,float y,float z);
	  private:
         phy_vector position;
         phy_vector look_at;
         phy_vector up_vector;
		 phy_vector v_rotation;  
		 float rotation;
	 };
