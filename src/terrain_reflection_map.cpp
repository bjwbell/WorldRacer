#include "../include/terrain_reflection_map.h"
void terrain_reflection_map::BuildReflectionMap(){

	//if(TemplateObject->GetObjectType()!=type_bush&&TemplateObject->GetObjectType()!=type_track_marker||TemplateObject==NULL)
	//	return false;
	//num_objects=0;
SDL_Surface*	Objects_Map=SDL_LoadBMP(map_file);
	//bush* Bush;
	
	   
	if(Objects_Map==NULL){
		MAP_SIZE=0;
		return;
	}



Uint8 red,green,blue;
	int STEP_SIZE=1;
	MAP_SIZE=Objects_Map->w;
	float x,y,z;
	vector2 Pos;

map_reflection=new float[MAP_SIZE*MAP_SIZE+MAP_SIZE];	
	

	
	
  for(int y = 0; y < MAP_SIZE; y++)
  {
    for(int x = 0; x < MAP_SIZE; x++)
    {
      
		
		
				blue=0;
				red=0;
				green=0;
				GetRGB(Objects_Map,x,y, &red,&green, &blue);
				map_reflection[y*MAP_SIZE+x]=((float)(red+green+blue))/765;
	 /*map_shade[y*SIZE+x] = 1 - (getHeight(Height_Map,x-LightDir.x, y-LightDir.y ) - getHeight(Height_Map,x, y )) / LIGHT_SOFTNESS;

      if(map_shade[y*SIZE+x] > MAX_BRIGHT)
        map_shade[y*SIZE+x] = MAX_BRIGHT;

      if(map_shade[y*SIZE+x] < MIN_BRIGHT)
        map_shade[y*SIZE+x] = MIN_BRIGHT;*/
    }
  }	
	
};
  
  
  
  
  
  
 float terrain_reflection_map::GetReflectionTransparency(int x,int y){
	if(MAP_SIZE==0)
		return 0;
	 if(x<=MAP_SIZE&&y<=MAP_SIZE){
		return map_reflection[y*MAP_SIZE+x];
	}else{
		return 0;
	};
};
void terrain_reflection_map::SetMapFile(char* file){
	
	map_file=file;
};
	
terrain_reflection_map::terrain_reflection_map(){
	MAP_SIZE=0;
};
	
	
	
	
	
	
	
	
/*	
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
*/
	


 
	
	
	

	
	
	
