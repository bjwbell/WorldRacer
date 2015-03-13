#include "../include/Speed_Display.h"
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
class hud{
	public:
	void Display_Speed(float speed);
	void Display_Map(vector2 player_position,vector2 AI_position);
	void Display_Num_Laps(int num_laps_completed,int num_laps);
	void Init(screen_dimension var_Screen_Dimension);
	
	void Render();
	void SetPlayerSpeed(float speed);

	void SetPosition(vector2 player_position,vector2 ai_position);

	void SetNumLapsCompleted(int num_laps);

	void SetTotalNumLaps(int num_laps);
	void SetTrack(track* var_Track);
	
	
	hud();
	private:
	vector2 Player_Position,AI_Position;
	float Speed;
	int Num_Laps_Completed,Num_Laps;
	track *Track;
	screen_dimension Screen_Dimension;
	display_text Display_Text;
	texture map;
	texture player_icon;
	texture AI_icon;
	speed_display Speed_Display;
};
