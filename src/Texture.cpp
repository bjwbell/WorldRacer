/***************************************************************************
                          Texture.cpp  -  description
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
#include "../include/Texture.h"
#include "tga.c"
GLuint texture::Texture[1000];
int texture::current;
bool texture::LoadTexture(char* var_file){
	return this->LoadFile(var_file);
}
bool texture::LoadFile(char* var_file){
    cout<<"Binding Texture "<<this_texture<<endl;
    cout<<"Texture file "<<var_file<<endl;
   glGenTextures ( 1, &Texture[this_texture] );
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, Texture[this_texture] );
   int x;
            x=loadTGA(var_file);
cout<<"Return code x "<<x<<endl;
   file=var_file;
  if(x==1){
  return true;
  }else{
    return false;
  }
}
GLuint texture:: GetTexture(){
    /*cout<<"Binding Texture "<<this_texture<<endl;
    cout<<"Texture file "<<file<<endl;
    glGenTextures ( 1, &Texture[this_texture] );
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, Texture[this_texture] );
   int x;
            x=loadTGA("Front.tga");*/
  //cout<<"Getting Texture "<<this_texture<<endl;
  return Texture[this_texture];
}
