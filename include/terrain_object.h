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
     #ifndef PLAYER
    #define PLAYER
    #include "player.h"
  #endif
 #ifndef TEXTDISPLAY
    #define TEXTDISPLAY
	#include "../include/display_text.h"
#endif
#ifndef TERRAIN
    #define TERRAIN
    #include "../include/Terrain.h"
  #endif
enum object_type{
	 type_bush,
	 type_track_marker
};
 class terrain_object{
	  public:
		  void Init();
		  void SetRadius(float Radius);
		  //void SetHeight(float Height);
		  virtual void Render()=0;
		  void SetTextureFile(char* par_Texture_File);
		  char* GetTextureFile();
		  void SetPosition(vector2 par_position);
		  vector2 GetPosition();
		  void SetTerrain(terrain *par_Terrain);
		  terrain_object(){
			 InitCalled=false;
		  }
		  float GetRadius();
		  object_type GetObjectType();
	protected:
		  object_type Type;
		  terrain* Terrain;
		  vector2 position;
		  texture Texture;
		  bool InitCalled;
		  float radius;
		  char* TextureFile;
		  GLUquadricObj *quadratic;
	 };
