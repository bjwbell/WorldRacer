#include "../include/World.h"
void world::Set_Key_Pressed(SDL_Event Event,bool KeyPressed){
	/*if(GameOver()==true){
		if(Event.type==SDL_KEYUP){
			if(Event.key.keysym.sym==SDLK_RETURN){
				
				track_num=0;
				GameBegun=false;
				InitComponents();
			}
		}

		//}
	}else{
		Player.Set_Key_Pressed(Event,KeyPressed);
		if(GameBegun==false){
			Track_Selector.key_input(Event);
		}
	}*/
};


void world::InitComponents(track* var_Track){
	Track=var_Track;
	phy_vector Player_Velocity1;
	Player_Velocity1.i=0;
	Player_Velocity1.j=0;
	Player_Velocity1.k=0;
	player_num_laps=0;
	ai_num_laps=0;


	Player.SetVelocity(Player_Velocity1);	
	
	AI_Player.SetVelocity(Player_Velocity1);	
	
	phy_vector vector_detail1,vector_detail2;
    vector_detail1.i=4;
    vector_detail1.j=2;
    vector_detail1.k=1;
    vector_detail2.i=1;
    vector_detail2.j=1;
    vector_detail2.k=1;

string map_path=Track->directory+"/Map.bmp";
string reflection_map_path=Track->directory+"/ReflectionMap.bmp";


string Texture_Path1=Track->directory+"/TerrainTexture1.tga";
string Texture_Path2=Track->directory+"/TerrainTexture2.tga";
string bushes_map_path=Track->directory+"/Bush_Map.bmp";
string Terrain_Config=Track->directory+"/config";
string Human_Player_Config=Track->directory+"/human_player_config";
string AI_Player_Config=Track->directory+"/ai_player_config";
//string bushes_map_path=Track->directory+"/Bush_Map.bmp";
//Bushes.CreateBushes((char*)bushes_map_path.c_str());
	AI_Player.SetConfig(AI_Player_Config.c_str());
	Player.SetConfig(Human_Player_Config.c_str());
	//Bushes.CreateBushes((char*)bushes_map_path.c_str());
		
	Terrain.SetConfig(Terrain_Config.c_str());
	
	Terrain_Objects.CreateObjects((char*)bushes_map_path.c_str());
	Terrain.SetHeightMap((char*)map_path.c_str());
    Terrain.SetReflectionMap((char*)reflection_map_path.c_str());
	Terrain.SetTexture1((char*)Texture_Path1.c_str());
    Terrain.SetTexture2((char*)Texture_Path2.c_str());
    Terrain.SetTexture1Detail(vector_detail1);
    Terrain.SetTexture2Detail(vector_detail2);
	Terrain.SetTransparency(1);
	Terrain.BuildTerrain();
	phy_vector Player_Position;
	phy_vector Player_Velocity;
	
    Camera_Position.i=212;
    Camera_Position.j=80;
    Camera_Position.k=494;

	Player_Position.i=Terrain.GetSize().x-240;
    Player_Position.j=0;
    Player_Position.k=Terrain.GetSize().y-240;
	Player.SetPosition(Player_Position);
	Player_Position.i=Terrain.GetSize().x-244;
	
	
	AI_Player.SetFogDensity(Terrain.GetFogDensity());
	AI_Player.SetFogDepth(Terrain.GetFogDepth());
	AI_Player.SetPosition(Player_Position);
	
	Player.SetFogDensity(Terrain.GetFogDensity());
	Player.SetFogDepth(Terrain.GetFogDepth());	
	Player.SetRotation(0);
    LookAt.i=0;
    LookAt.j=0;
    LookAt.k=0;
    Camera.SetPosition(Camera_Position);
    Camera.SetView(LookAt);
	vector2 Pos;
	Pos.x=Terrain.GetSize().x-240;
	Pos.y=Terrain.GetSize().y-120;
	Track_Marker.SetPosition(Pos);
	Pos.x=Terrain.GetSize().x-340;
	Pos.y=Terrain.GetSize().x-360;	
	Track_Marker2.SetPosition(Pos);
	AI_Player.SetTrack(Track);
};







void world::Render(){
		LookAt.i=Player.GetPosition().i;
       
       LookAt.k=Player.GetPosition().k;

		
	
		
		LookAt.j=Player.GetPosition().j;
		
			Camera_Position.i=Player.GetPosition().i-sin(0.017453*Player.GetRotation())*50;
		Camera_Position.k=Player.GetPosition().k+cos(0.017453*Player.GetRotation())*50;
		Camera_Position.j=Terrain.Height(Camera_Position.i,Camera_Position.k)+10;
		
		if(Camera_Position.j<Player.GetPosition().j){
			Camera_Position.j=Player.GetPosition().j+3;
		}
		Camera.SetView(LookAt);
        Camera.SetPosition(Camera_Position);
        
		Camera.PlaceCamera();	//must be called before rendering calls;

	    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_FOG);
	RenderSky(&Sky,-10000,300,-10000,20000,20000);
    glPopAttrib();

	Track_Marker.Render();  
    Track_Marker2.Render();  	
	 glPushAttrib(GL_ALL_ATTRIB_BITS);
	// Bushes.Render();
	
	 Terrain_Objects.Render();
 glPopAttrib();
	
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	Player.Render();
	 glPopAttrib();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	AI_Player.Render();
	glPopAttrib();
				  
	glPopMatrix();
glPushMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
    
	

	Terrain.Render();

	
	//Player.RenderReflection();
	
	//Terrain.Render();
    glPopAttrib();
	glPopMatrix();



      



	

};
void world::UpdateScene(float t){

	phy_vector force;

	


	
	Update_Num_Laps();	
	
	
	
	AI_Player.Update(t);
	Player.Update(t);
	AI_Player.SetNewAISpeed(&Player);
	Player_Old_Position=Player_New_Position;
	Player_New_Position=Player.GetPosition();
	
	AI_Player_Old_Position=AI_Player_New_Position;
	AI_Player_New_Position=AI_Player.GetPosition();	
	
		

	
	
	
    phy_vector V=Player.GetVelocity();
	float speed=sqrt(V.i*V.i+V.j*V.j+V.k*V.k)*1000;	
	vector2 player_position;
	player_position.x=Player.GetPosition().i;
	player_position.y=Player.GetPosition().k;
	
	vector2 AI_position;
	AI_position.x=AI_Player.GetPosition().i;	
	AI_position.y=AI_Player.GetPosition().k;

	

};

bool world::Set_Player_Model(char* path,char* name){
	AI_Player.LoadModel(path,name);
	Player.LoadModel(path,name);
	return true;
};
bool world::Set_AI_Model(char* path,char* name){

	return true;
};
void world::Update_Num_Laps(){
	if(Player_Old_Position.k>4880&&Player_New_Position.k<=4880&&Player_New_Position.i>4560&&Player_New_Position.i<5120){
		player_num_laps++;
		
	};
	if(Player_Old_Position.k<=4880&&Player_New_Position.k>4880&&Player_New_Position.i>4560&&Player_New_Position.i<5120){
		player_num_laps--;//going backwards over the finish line so decrease the number of laps
		
	};
	if(AI_Player_Old_Position.k>4880&&AI_Player_New_Position.k<=4880&&AI_Player_New_Position.i>4560&&AI_Player_New_Position.i<5120){
		//cout<<"Ai num laps "<<ai_num_laps<<endl;
		ai_num_laps++;
		
	};
	if(AI_Player_Old_Position.k<=4880&&AI_Player_New_Position.k>4880&&AI_Player_New_Position.i>4560&&AI_Player_New_Position.i<5120){
		ai_num_laps--;//going backwards over the finish line so decrease the number of laps;
		
	};
};


bool world::AI_Won(){
	if(ai_num_laps>=num_laps_to_complete_race){
		return true;
	}else{
		return false;
	}

};
bool world::Player_Won(){
	if(player_num_laps>=num_laps_to_complete_race){
		return true;
	}else{
		return false;
	};

};
bool world::Init(track* var_Track,screen_dimension var_Screen_Dimension){
	Track=var_Track;
	bool return_value;
	Screen_Dimension=var_Screen_Dimension;
	Player.SetTorsoAnimation("TORSO_STAND");

    // Set the walking animation for the legs
    Player.SetLegsAnimation("LEGS_RUN");
	
	
	
	AI_Player.SetTorsoAnimation("TORSO_STAND");

    // Set the walking animation for the legs
    AI_Player.SetLegsAnimation("LEGS_RUN");	



	Player.SetTerrain(&Terrain);
	AI_Player.SetTerrain(&Terrain);
	
	Track_Marker.Init();
	vector2 Pos;
	Pos.x=4880;
	Pos.y=5000;
	Track_Marker.SetTextureFile("data/Top.tga");
	Track_Marker.SetPosition(Pos);
	Track_Marker.SetHeight(100);
	Track_Marker.SetRadius(10);
	Track_Marker.SetTerrain(&Terrain);
	Track_Marker2.Init();
	
	Pos.x=4780;
	Pos.y=4760;
	Track_Marker2.SetTextureFile("data/Top.tga");
	Track_Marker2.SetPosition(Pos);
	Track_Marker2.SetHeight(100);
	Track_Marker2.SetRadius(10);
	Track_Marker2.SetTerrain(&Terrain);
	TextDisplay.BuildFont();
	Sky.LoadTexture("data/Top.tga");
	Bushes.Init(&Terrain);
	Terrain_Objects.Init(&Terrain);
	Bush.Init();
	Bush.SetRadius(10);
	Bush.SetTextureFile("data/Bush.tga");
	Bush.SetTerrain(&Terrain);
	Terrain_Objects.SetTemplateObject(&Bush);
	return true;
	};
Human_player *world::GetHumanPlayer(){
	return &Player;
};
AI_player *world::Get_AI_Player(){
	return &AI_Player;
};
int world::GetPlayerNumLaps(){
	return player_num_laps;
};
world::world(){

	
	num_laps_to_complete_race=2;
		player_num_laps=0;
	ai_num_laps=0;

};

