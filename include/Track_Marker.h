    #ifndef Graphics
       #define Graphics
          #include <SDL/SDL.h>
          #include <GL/gl.h>
          #include <GL/glu.h>
          #include <GL/glext.h>
          #define GL_COMBINE_ARB						0x8570
          #define GL_RGB_SCALE_ARB					0x8573
          #include "../include/Texture.h"
    #endif
 #ifndef TERRAIN
    #define TERRAIN
    #include "../include/Terrain.h"
  #endif
     #ifndef Functions
    #define Functions
    #include "Functions.h"
  #endif
       #ifndef TERRAIN_OBJECT
    #define TERRAIN_OBJECT
    #include "../include/terrain_object.h"
  #endif
  class track_marker:public terrain_object{
	  public:
		  void Init();
		//  void SetRadius(float Radius);
		  void SetHeight(float Height);
		  float GetHeight();
		  void Render();
		  //void SetTextureFile(char* par_Texture_File);
		  //void SetPosition(vector2 par_position);
		 // void SetTerrain(terrain *par_Terrain);
		 //track_marker(){
		//	 InitCalled=false;
		//}
	  private:
		 // terrain* Terrain;
		 // vector2 position;
		 // texture Texture;
		 // bool InitCalled;
		  float height;
		 // float radius;
		 // char* TextureFile;
		  //GLUquadricObj *quadratic;
	 };
