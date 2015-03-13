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

//	#include "../include/Terrain.h"


     #ifndef PLAYER
    #define PLAYER
    #include "player.h"
  #endif
 #ifndef TEXTDISPLAY
    #define TEXTDISPLAY
	#include "../include/display_text.h"
#endif
   #ifndef TERRAIN_OBJECT
    #define TERRAIN_OBJECT
    #include "../include/terrain_object.h"
  #endif
class bush: public terrain_object{
	public:
		void Init();
	    void Render();
		//void SetPosition(vector2 var_Position);
		//vector2 GetPosition();
		//void SetRadius(float var_Radius);
		//float GetRadius();
		//void SetTerrain(terrain *var_Terrain);
	private:
		//vector2 Position;
		//texture Texture;
		//float Radius;
		//terrain *Terrain;
	    //GLUquadricObj *quadratic;
		//bool InitCalled;
};
