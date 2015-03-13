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
class track_selection{
	public:
		int Get_Selected_Track();
		void Init(screen_dimension var_screen);
		void Render();
		void key_input(SDL_Event Event);
	private:
		int selected_track;
		int num_tracks;
		bool End_Selecting;
		display_text TextDisplay;
		screen_dimension screen;
};
