/***************************************************************************
                          Functions.h  -  description
                             -------------------
    begin                : Sat Jul 6 2002
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
          #include <GL/glx.h>
		  #define GL_COMBINE_ARB						0x8570
          #define GL_RGB_SCALE_ARB					0x8573
          #include "Texture.h"
    #endif
 #include <math.h>
struct track{
	string directory;
	string map_path;
	string reflection_map_path;


	string Texture_Path1;
	string Texture_Path2;
	string bushes_map_path;
	string Terrain_Config;	
};
struct phy_vector{
	float i;
	float j;
  float k;
}; 
struct vector2{
	float x,y;
	
};
struct vector3{
	float x,y,z;
};
struct vector4{
	float x,y,z,w;
};
struct screen_dimension{
		int height;
	    int width;
};
extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
//struct 2d_vector{
//	float i;
//	float k;
//};
typedef struct										// Structure For 3D Points
{
	float	x, y, z;									// X, Y & Z Points
} VERTEX;	
struct point{
	float x,y,z;
};	
struct plane{
		float A;
		float B;
		float C;
		float D;
	};
float find_min_distance_between_points_through_line(phy_vector node1,phy_vector node2,phy_vector Point);
void readstr(FILE *f,char *string);	

phy_vector Apply_Friction(phy_vector V,float m,float u,float time);

float Dot_Product(phy_vector v1,phy_vector v2);
float FindDirectionalDerivative(phy_vector Gradiant,phy_vector Direction);
phy_vector FindPlaneGradiant(point Point1,phy_vector Vector1,phy_vector Vector2);

float FindForceInDirectionOfSlope(phy_vector Slope,float m);
phy_vector NormalVector(phy_vector v1,phy_vector v2);
phy_vector FindPlaneSlope(point Point1,phy_vector Vector1,phy_vector Vector2);
phy_vector FindForceXYZ(phy_vector Slope,float m);
void SetFogCoord(float depth, float height,float fogdensity);

float FindForceNormalToSlope(phy_vector Slope,float m);

Uint32 getpixel(SDL_Surface *surface, int x, int y);
  bool  GetRGB(SDL_Surface *surface,int x,int y, Uint8 *r,Uint8 *g, Uint8 *b);
  int getHeight(SDL_Surface *surface,int x,int y);

  void SetVertexColor(SDL_Surface* surface, int x, int y);		// This Sets The Color Value For A Particular Index

   bool RenderTerrian(char* file_Map,char* file_Color);
   void CreateSkyBox(float x, float y, float z, float width, float height, float length,texture Texture1,texture Texture2,texture Texture3,texture Texture4,texture Texture5,texture Texture6);
   phy_vector CreateNormal(phy_vector vector1,phy_vector vector2);
void RenderSky(texture* Sky, float x,float y ,float z,float width,float length);
phy_vector Find_Velocity(phy_vector V,float m,float u,float t);
void UnitVector(vector3& vector);
void UnitVector(vector2& vector);
plane FindClipPlane(vector3 Vector[3]);
vector3 normal_vector(vector3 Vector1,vector3 Vector2);
vector3 unit_normal_vector(vector3 Vector1,vector3 Vector2);

/*GLuint  base;  //Base Display List For The Font Set
texture FontTexture;
GLvoid KillFont( GLvoid );
GLvoid BuildFont( GLvoid );
GLvoid glPrint( float x,float y,const char *fmt, ... );*/

