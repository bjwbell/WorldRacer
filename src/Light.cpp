/***************************************************************************
                          Light.cpp  -  description
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

#include "../include/Light.h"
//int light::num_lights;
light::light(GLenum Light_number){
      light_number=Light_number;
      //num_lights++;
      //  if(num_lights>7){
       // cout<<"Error More than eight lights have created. I don't know if the graphics card supports more then 8 lights "<<endl;
       // }
      }
light::~light(){
}
bool light::SetColor(GLenum light_type,float r,float g,float b,float a){
    GLfloat color[]={r,g,b,a};
    glLightfv(light_number,light_type,color);
    return true;
}

bool light::SetPosition(phy_vector Light_Position){
    light_position=Light_Position;
    GLfloat light_Position[]={Light_Position.i,Light_Position.j,Light_Position.k,1};

    glLightfv(light_number,GL_POSITION,light_Position);



    return true;
};
phy_vector light::GetPosition(){
  return light_position;
};
