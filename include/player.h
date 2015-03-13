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
     #ifndef Functions
    #define Functions
    #include "Functions.h"
  #endif
#include "../include/Md3.h"
//#include "../include/Terrain.h"
 
 #ifndef TERRAIN
    #define TERRAIN
    #include "../include/Terrain.h"
  #endif
#include "../include/path.h"
     #ifndef Functions
    #define Functions
    #include "Functions.h"
  #endif
//#include "Game_Class.h"
class player :public CModelMD3{
	public:
		void SetPosition(phy_vector position);
		void SetVelocity(phy_vector velocity);
		void SetAcceleration(phy_vector acceleration);
		void SetRotation(float rotation);
		float GetRotation();
		phy_vector GetAcceleration();
		phy_vector GetVelocity();
		phy_vector GetPosition();
		bool UpdatePositionVelocity(float t);
		virtual bool Update(float t)=0;
		virtual ~player(){
		};
		bool SetTerrain(terrain *Terrain1);
		bool UpdateAccelerationPosition(float t);
		phy_vector FindForceOnPlayer();
		void SetPlayerForce(phy_vector Force);
		bool Render();
		
		void RenderReflection();
		void SetReflectionTransparency(float Transparency);
		virtual void SetConfig(const char* Config_File)=0;

		//void SetParent(game* Parent);
	protected:
		void RenderShadow();//need to clip shadow so it doesn't go through the player;
		// game* parent;
		const char* config_file;

		float trans;
		point GetPoint();
		void FindPlaneVectors(phy_vector &vector1,phy_vector &vector2);
		phy_vector Player_Position;
		phy_vector Player_Velocity;
		phy_vector Acceleration;
		float Player_Rotation;
		terrain* Terrain;
		phy_vector player_force;
	
};
class Human_player:public player{
	public:
		void SetConfig(const char* Config_File);
		void Set_Key_Pressed(SDL_Event Event,bool KeyPressed);
		bool Update(float t);
		Human_player();
		bool SetMaxSpeed(float Max_Speed);
		void SetMaxHeight(float Max_Height);
	
	private:
		float max_speed;
		float max_height;
		bool Up_Key_Pressed;
		bool Down_Key_Pressed;
		bool Left_Key_Pressed;
		bool Right_Key_Pressed;
		bool falling;
		bool old_time;
};

class AI_player:public player{
	public:
		void SetConfig(const char* Config_File);
		bool Update(float t);	
		bool SetPath(path var_path);
		AI_player();
		virtual ~AI_player(){
		};
		void SetSpeedMultiplyer(float new_speed_multiplyer);
		void SetNewAISpeed(Human_player* Player);
		void SetTrack(track* var_Track);
	private:
		bool first_time_called;
		void FindClosestNodesToHumanPlayer(Human_player *Player);
		int GetClosestNodeToHumanPlayer(Human_player *Player);
		float max_speed;
		float speed_mult;
		path Path;
		phy_vector AI_force; 
		int node_num;
		track *Track;
		
		//phy_vector Path[100];
		
};


/*class path{
	public:
		void PathFile(char* file);
		vector<float> GetPath();
	private:
		char* path_file;
		vector<float>path;
};*/
