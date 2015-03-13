#include "../include/Bushes.h"
void bushes::Init(terrain* var_Terrain){
	Terrain=var_Terrain;
	Radius=10;
	num_bushes=0;
};
void bushes::SetRadius(float var_Radius){
	Radius=var_Radius;
};
void bushes::Render(){
	if(Bush_Map==NULL){
	}else{
		for(int i=1;i<num_bushes;i++){
			
			Bushes[i]->Render();
		
		}
	}
};
bool bushes::CreateBushes(char* var_map_file){
	num_bushes=0;
	Bush_Map=SDL_LoadBMP(var_map_file);
	bush* Bush;
	
	   
	if(Bush_Map==NULL){
		return false;
	}



Uint8 red,green,blue;
	int STEP_SIZE=1;
	int MAP_SIZE=Bush_Map->w;
	float x,y,z;
	vector2 Pos;
for (int X = 0; X <= MAP_SIZE; X += STEP_SIZE )
	{
		
			for (int Y = MAP_SIZE; Y > 0; Y -= STEP_SIZE )
			{
				
				blue=0;
				red=0;
				green=0;
				GetRGB(Bush_Map,X,Y, &red,&green, &blue);
				if(blue>=255&&red==0&&green==0){
					Bush=new bush;
				
					Pos.x=X*Terrain->Get_Terrain_Scale().i;
					Pos.y=Y*Terrain->Get_Terrain_Scale().k;
					Bush->Init();
					Bush->SetRadius(Radius);
					Bush->SetPosition(Pos);
					Bush->SetTerrain(Terrain);
					Bush->SetTextureFile("data/Bush.tga");
					Bushes.push_back(Bush);
					num_bushes++;
				}
				//y = getHeight(Bush_Map,X, Y );
				//z = Y;
				
				//glVertex3i(x, y, z);
			}
	}

	


 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);			// Reset The Color

};
