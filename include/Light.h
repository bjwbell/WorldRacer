/***************************************************************************
                          Light.h  -  description
                             -------------------
    begin                : Sun Aug 18 2002
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
  class light{
    public:
     light(GLenum Light_number);
    ~light();
    bool SetPosition(phy_vector Light_Position);
    bool SetColor(GLenum light_type,float r,float g,float b,float a);
    phy_vector GetPosition();
    private:
    GLenum light_number;
    static int num_lights;
    phy_vector light_position;
    float red,green,blue;
};
