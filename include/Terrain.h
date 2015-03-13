/***************************************************************************
                          Terrain.h  -  description
                             -------------------
    begin                : Wed Jul 10 2002
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
  #include "../include/terrain_reflection_map.h"
  // This is our fog extension function pointer to set a vertice's depth
extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
  class terrain {
      public:
       bool Render();
       bool SetTexture1(char* file);
       bool SetHeightMap(char* file);
	   bool SetReflectionMap(char* file);
	   bool SetConfig(const char* file);
	   char* GetHeightMapFile(); 
	   bool SetTexture2(char* file);
       //bool SetPosition(float x,float y,float z);
       bool SetTexture1Detail(phy_vector vector_detail);
       bool SetTexture2Detail(phy_vector vector_detail);
       bool BuildTerrain();
	   float Height(float x ,float y);
	   void Set_Terrain_Scale(phy_vector scale);
	   phy_vector Get_Terrain_Scale();
	   float GetFogDensity();
	   float GetFogDepth();
	  void SetTransparency(float trans);//To take effect the terrain must be Rebuilt;
	  float GetReflectionTransparency(float x,float z);
	  vector2 GetSize(); 
	  terrain();
	   ~terrain();
	  private:
			terrain_reflection_map Reflection_Map;
			void  Setup_Lighting();
			void SetLight(int x,int y);
			void ReadConfig();
		    void SetFogCoord(float depth, float height);
			int STEP_SIZE;
			float GetHeight(float x ,float y);
			void SetTextureCoord(float x,float y);
			SDL_Surface *Height_Map;
			char* terrain_file; 
			texture Texture1;
			texture Texture2;
			phy_vector Terrain_Scale; 
			float FogDepth;
		    float fogdensity;
			float LIGHT_SOFTNESS;     //makes lighting more transitive, smooth, and less abrupt
			float MAX_BRIGHT ;        //maximum brightness
			float MIN_BRIGHT ;        //minimal brightness (hillsides are never pitch black during the day)
			float Transparency;
			vector2 LightDir;
			float* map_shade; 
			phy_vector vector_detail1;
			phy_vector vector_detail2;
			int LastTexture;
			float move_x,move_y,move_z;
			GLuint	terrain_list;						// Storage For The Display List
};
