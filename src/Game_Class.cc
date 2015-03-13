#include "../include/Game_Class.h"
void game::Set_Key_Pressed(SDL_Event Event,bool KeyPressed){
	if(GameOver()==true){
		if(Event.type==SDL_KEYUP){
			if(Event.key.keysym.sym==SDLK_RETURN){
				
				track_num=0;
				GameBegun=false;
				InitComponents();
			}
		}

		//}
	}else{
		World.GetHumanPlayer()->Set_Key_Pressed(Event,KeyPressed);
		if(GameBegun==false){
			Track_Selector.key_input(Event);
		}
	}
};


void game::InitComponents(){
	World.InitComponents(&tracks[track_num]);
	HUD.SetTrack(&tracks[track_num]);

};





void game::Display_Won_Screen(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
			glLoadIdentity();									// Reset The matrix

		// 	  Position      View	   Up Vector
		gluLookAt(0, 0, 3,     0, 0, 0,     0, 1, 0);		// This determines where the camera's position and view is

		glEnable(GL_TEXTURE_2D);
		

	if(World.AI_Won()){	
		glBindTexture(GL_TEXTURE_2D, Won_AI.GetTexture());
	}else{
		glBindTexture(GL_TEXTURE_2D, Won_Player.GetTexture());
	}



		glPushMatrix();


		glTranslatef(0, 0, 0);

		
		glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f);glVertex3f(-1, 1, 0);

			glTexCoord2f(0.0f, 0.0f);glVertex3f(-1, -1, 0);

		
			glTexCoord2f(1.0f, 0.0f);glVertex3f(1, -1, 0);

			glTexCoord2f(1.0f, 1.0f);glVertex3f(1, 1, 0);

		glEnd();


		glPopMatrix();
	};
;

void game::Render(){

if(GameOver()||GameBegun!=true){
	if(GameBegun==false){
		Track_Selector.Render();
	}
if(GameOver()){
	Display_Won_Screen();
}

	
		
		
	
	
}else{
	
	World.Render();

	
	HUD.Render();
	
	if(pause==true){
		TextDisplay.glPrint(Screen_Dimension.width/2,Screen_Dimension.height/2,"%1.0f",3-time/1000);
	};

}
};
void game::UpdateScene(){
	static double t1;
	static double t2;
	static bool not_first_time;
	double t;
	phy_vector force;

	
	if(not_first_time!=true){
		t=0;
		not_first_time=true;
	}else{
	t2=SDL_GetTicks();
	}		//}
	t=t2-t1;
 

if((GameOver()==true)||(GameBegun!=true)){
	if(GameBegun==false){
		int num=Track_Selector.Get_Selected_Track();
	

		if(num!=-1){
			track_num=num;
			InitComponents();
			cout<<"Game Begun "<<num<<endl;
			pause=true;
			time=0;
			GameBegun=true;
		};
	};
}else{
	if(pause==true){
		if(time+t>=3000){
			pause=false;
			time=0;
		};
		time=time+t;
		t=t/100000;
	}
	
	World.UpdateScene(t);
	
	}
	phy_vector V=World.GetHumanPlayer()->GetVelocity();
	float speed=sqrt(V.i*V.i+V.k*V.k)*100;	//don't include vertical speed because that code is still buggy
	vector2 player_position;
	player_position.x=World.GetHumanPlayer()->GetPosition().i;
	player_position.y=World.GetHumanPlayer()->GetPosition().k;
	
	vector2 AI_position;
	AI_position.x=World.Get_AI_Player()->GetPosition().i;	
	AI_position.y=World.Get_AI_Player()->GetPosition().k;
	HUD.SetPlayerSpeed(speed);
	HUD.SetPosition(player_position,AI_position);
	HUD.SetNumLapsCompleted(World.GetPlayerNumLaps()+1);
	
	t1=SDL_GetTicks();

};

bool game::Set_Player_Model(char* path,char* name){
	World.Set_Player_Model(path,name);

	return true;
};
bool game::Set_AI_Model(char* path,char* name){
	World.Set_AI_Model(path,name);
	return true;
};

bool game::GameOver(){
	
	
	
	if(World.AI_Won()||World.Player_Won()){
		return true;
	}else{
		return false;
	}
};

bool game::Init(screen_dimension var_Screen_Dimension){
	Screen_Dimension=var_Screen_Dimension;
	World.Init(&tracks[0],var_Screen_Dimension);
	HUD.Init(Screen_Dimension);	
	Won_AI.LoadTexture("data/AI_Won.tga");
	Won_Player.LoadTexture("data/Player_Won.tga");
	

	TextDisplay.BuildFont();
	Track_Selector.Init(Screen_Dimension);
	return true;
	};
Human_player *game::GetHumanPlayer(){
	return World.GetHumanPlayer();
};
game::game(){
	GameBegun=false;
	pause=false;
	num_tracks=3;
	string Directory;
	char* Xstring;
	int c=1;
	int t2=1;
	for(int i=0;i<num_tracks;i++){
	
		Xstring=ecvt(i+1,c,&c,&t2);
		
		char* dest=(char*)malloc(6*sizeof(char));
		strcpy(dest,"track");
		dest=strcat(dest, Xstring);
		tracks[i].directory=dest;
	}

	track_num=0;
int	num_laps_to_complete_race=2;
	HUD.SetTrack(&tracks[track_num]);
	HUD.SetTotalNumLaps(num_laps_to_complete_race);	
	time=0;

};

