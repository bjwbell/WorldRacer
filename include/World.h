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
 #include "../include/Md3.h"
 #ifndef PLAYER
    #define PLAYER
    #include "player.h"
  #endif
   #ifndef TEXTDISPLAY
    #define TEXTDISPLAY
	#include "../include/display_text.h"
#endif
	#include "../include/Camera.h"
//#include "../include/Track_Marker.h"
//#include "../include/Bushes.h"
#include "../include/terrain_objects.h"
class world{
	public:
		bool Init(track* var_Track,screen_dimension var_Screen_Dimension);
		void Set_Key_Pressed(SDL_Event Event,bool KeyPressed);
		void Render();
		bool Set_AI_Model(char* path,char* name);
		bool Set_Player_Model(char* path,char* name);
		void UpdateScene(float t);
		Human_player *GetHumanPlayer();
		AI_player *Get_AI_Player();
		world();
	    void InitComponents(track* var_Track);
		bool AI_Won();
		bool Player_Won();
	    int GetPlayerNumLaps();
	private:
		screen_dimension Screen_Dimension;
		
	//	void Display_AI_Won_Screen();
		//void Display_Player_Won_Screen();
		void Update_Num_Laps();
	//	bool GameOver();
		//bool GameBegun;

		int player_num_laps;
		int ai_num_laps;
		int num_laps_to_complete_race;
		phy_vector Player_Old_Position;
		phy_vector Player_New_Position;
		phy_vector AI_Player_Old_Position;
		phy_vector AI_Player_New_Position;
		//texture Won_AI,Won_Player;
		AI_player AI_Player;
		Human_player Player;
		
		phy_vector Accer;
		texture Sky;
		camera Camera;
		phy_vector Camera_Position;
		phy_vector LookAt;
		phy_vector Terrain_Scale;
		terrain Terrain;
		track_marker Track_Marker;
		track_marker Track_Marker2;
		bushes Bushes;
		terrain_objects Terrain_Objects;
		bush Bush;
		display_text TextDisplay;
	    track* Track;
		bool Up_Key_Pressed;
		bool Down_Key_Pressed;
		bool Left_Key_Pressed;
		bool Right_Key_Pressed;

	
	
		float time;
};
