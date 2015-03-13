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
#include "HUD.h"
//	#include "../include/Terrain.h"


     #ifndef PLAYER
    #define PLAYER
    #include "player.h"
  #endif
 #ifndef TEXTDISPLAY
    #define TEXTDISPLAY
	#include "../include/display_text.h"
#endif
#include "../include/track_selection.h"
#include "../include/World.h"

/*class player;
class Human_player;
class AI_player;*/
class game{
	public:
		bool Init(screen_dimension var_Screen_Dimension);
		void Set_Key_Pressed(SDL_Event Event,bool KeyPressed);
		void Render();
		bool Set_AI_Model(char* path,char* name);
		bool Set_Player_Model(char* path,char* name);
		void UpdateScene();
		Human_player *GetHumanPlayer();
		game();
	   
	private:
		screen_dimension Screen_Dimension;
		void InitComponents();
		void Display_Won_Screen();
		
		bool GameOver();
		bool GameBegun;

		texture Won_AI,Won_Player;

		hud HUD;
		display_text TextDisplay;

		bool Up_Key_Pressed;
		bool Down_Key_Pressed;
		bool Left_Key_Pressed;
		bool Right_Key_Pressed;
	    track tracks[3];
		int num_tracks;
		int track_num;
		track_selection Track_Selector;
		bool pause;
		
		float time;
		world World;


};
