/***************************************************************************
                          Camera.cpp  -  description
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
  #include "../include/Camera.h"
  bool camera::SetPosition(phy_vector Position){
    position=Position;
    return true;
  };
  phy_vector camera::GetPosition(){
    return position;
  };
   bool camera::SetView(phy_vector Look_At){
     look_at=Look_At;
     return true;
  };
   phy_vector camera::GetView(){

      return look_at;
  };
   bool camera::SetUpVector(phy_vector Up_Vector){
    up_vector=Up_Vector;
    return true;
  };
   phy_vector camera::GetUpVector(){
    return up_vector;
  };
   bool camera::PlaceCamera(){
   
	gluLookAt(position.i,position.j,position.k,look_at.i,look_at.j,look_at.k,0,1,0);
    //gluLookAt(212, 160, 294,  186, 55, 171,  0, 1, 0);
    return true;
  };
void camera::Rotate(float Rotation,float x,float y,float z){
	rotation=Rotation;
	v_rotation.i=x;
	v_rotation.j=y;
	v_rotation.k=z;
 glRotatef(rotation,v_rotation.i,v_rotation.j,v_rotation.k);
};
