#include "../include/terrain_objects.h"
void terrain_objects::Init(terrain* var_Terrain){
	Terrain=var_Terrain;
	TemplateObject=NULL;
	num_objects=0;
};
/*void terrain_objects::SetRadius(float var_Radius){
	Radius=var_Radius;
};*/
void terrain_objects::Render(){
	if(TemplateObject->GetObjectType()!=type_bush&&TemplateObject->GetObjectType()!=type_track_marker||TemplateObject==NULL)
		return;
	if(Objects_Map==NULL)
		return;
		for(int i=1;i<num_objects;i++){
			
			Objects[i]->Render();
		
		}
	
};
bool terrain_objects::CreateObjects(char* var_map_file){
	if(TemplateObject->GetObjectType()!=type_bush&&TemplateObject->GetObjectType()!=type_track_marker||TemplateObject==NULL)
		return false;
	num_objects=0;
	Objects_Map=SDL_LoadBMP(var_map_file);
	bush* Bush;
	
	   
	if(Objects_Map==NULL){
		return false;
	}



Uint8 red,green,blue;
	int STEP_SIZE=1;
	int MAP_SIZE=Objects_Map->w;
	float x,y,z;
	vector2 Pos;
for (int X = 0; X <= MAP_SIZE; X += STEP_SIZE )
	{
		
			for (int Y = MAP_SIZE; Y > 0; Y -= STEP_SIZE )
			{
				
				blue=0;
				red=0;
				green=0;
				GetRGB(Objects_Map,X,Y, &red,&green, &blue);
				if(blue>=255&&red==0&&green==0){
					
					if(TemplateObject->GetObjectType()==type_bush){
						Object=new bush;
						
					}else{
						Object=new track_marker;
						((track_marker*)Object)->SetHeight(((track_marker*)TemplateObject)->GetHeight());
						
					}
					
					Pos.x=X*Terrain->Get_Terrain_Scale().i;
					Pos.y=Y*Terrain->Get_Terrain_Scale().k;
					
					Object->Init();
					Object->SetRadius(TemplateObject->GetRadius());
					Object->SetPosition(Pos);
					Object->SetTerrain(Terrain);
					Object->SetTextureFile(TemplateObject->GetTextureFile());
					Objects.push_back(Object);
					
				
					
					num_objects++;
				
				}
				//y = getHeight(Bush_Map,X, Y );
				//z = Y;
				
				//glVertex3i(x, y, z);
			}
	}

	


 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);			// Reset The Color

};
void terrain_objects::SetTemplateObject(terrain_object* object){
	TemplateObject=object;
};
