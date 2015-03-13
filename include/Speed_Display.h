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
 #ifndef TEXTDISPLAY
    #define TEXTDISPLAY
	#include "../include/display_text.h"
#endif
class speed_display{
	public:
	void Init();
	void SetSpeed(float Speed);
	void Display_Speed();
	private:
	float speed;
	display_text Display_Text;
};
