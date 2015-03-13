/***************************************************************************
                          Terrain.cpp  -  description
                             -------------------
    begin                : Wed Jul 10 2002
    copyright            : (C) 2002 by Bryan Bell
    email                : Bryan@localhost.localdomain
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "../include/Terrain.h"
//#include "Texture.h"
/*bool terrain::SetPosition(float x,float y,float z){
    move_x=x;
    move_y=y;
    move_z=z;
    return true;
};*/
bool terrain::Render(){
   glPushMatrix();
	//glLoadIdentity();
	glScalef(Terrain_Scale.i,Terrain_Scale.j,Terrain_Scale.k);
	
	glCallList(terrain_list);			// Draw The Terrain
	
glPopMatrix();

  return true;
};


void terrain::SetTextureCoord(float x, float z)
{
	// Find the (u, v) coordinate for the current vertex
	float MAP_SIZE=Height_Map->w;
	float u =  (float)x / (float)MAP_SIZE;
	float v = -(float)z / (float)MAP_SIZE;


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// Instead of using the normal API for assigning the current texture
	// coordinate, we want to use the glMultiTexCoord2fARB() function.
	// This will allow us to choose the (u, v) coordinate for every texture
	// map, since we are using multitexturing.  Due to the fact that we
	// are going to be using the texture matrix to set the tiling of our
	// detail texture, we just assign the same (u, v) coordinate for both
	// textures.

	// Give OpenGL the current terrain texture coordinate for our height map
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);

	// Give OpenGL the current detail texture coordinate for our height map
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


}

void terrain::SetFogCoord(float depth, float height)
{
	// This function takes the depth of the fog, as well as the height
	// of the current vertex.  If the height is greater than the depth, there
	// is no fog applied to it (0), but if it's below the depth, then we
	// calculate the fog value that should be applied to it.  Since the higher
	// the number passed into glFogCoordfEXT() produces more fog, we need to
	// subtract the depth from the height, then negate that value to switch
	// the ratio from 0 to the depth around.  Otherwise it would have more
	// fog on the top of the fog volume than the bottom of it.

	float fogY = 0;
	//fogdensity=0.7;
	// Check if the height of this vertex is greater than the depth (needs no fog)
	if(height > depth)
		fogY = 0;
	// Otherwise, calculate the fog depth for the current vertex
	else
		fogY = -(height - depth)*fogdensity;

	// Assign the fog coordinate for this vertex using our extension function pointer
	glFogCoordfEXT(fogY);
}
bool terrain:: SetConfig(const char* file){

										
	float	x,y;									
	FILE	*filein;									// Filename To Open
	char	oneline[255];								// Holds One Line Of Text (255 Chars Max)
	phy_vector Vector;
	filein = fopen(file, "rt");							// Opens The File For Reading Text In Translated Mode
    if(!filein) {
        printf("failed to open file: %s\n", file);
        return false;
		//exit(0);
    }
														
	readstr(filein,oneline);							
	
	
	
	float t;
	for(int i=1;i<=8;i++)							
	{
							
			switch(i){
			
				case 1:	sscanf(oneline, "FOG_DEPTH %f", &FogDepth);break;
				case 2: sscanf(oneline,"FOG_DENSITY %f",&fogdensity);break;	
				case 3: sscanf(oneline,"LIGHT_MAX_BRIGHTNESS %f",&MAX_BRIGHT);break;
				case 4: sscanf(oneline,"LIGHT_MIN_BRIGHTNESS %f",&MIN_BRIGHT);break;
				case 5: sscanf(oneline,"LIGHT_SOFTNESS %f",&LIGHT_SOFTNESS);break;
				case 6: sscanf(oneline,"TERRAIN_SCALE %f %f %f",&Terrain_Scale.i,&Terrain_Scale.j,&Terrain_Scale.k);
				case 7: sscanf(oneline,"LIGHT_DIRECTION %f %f",&LightDir.x,&LightDir.y);
				
			}
			
			readstr(filein,oneline);// Reads In The Next Line Of Text	
	}

	fclose(filein);	


			return true;
	 
};
float terrain::GetFogDensity(){
	return fogdensity;
};
float terrain::GetFogDepth(){
	return FogDepth;
}
void terrain::Setup_Lighting(){



//the good stuff
int SIZE=Height_Map->w  ;        //your map size


map_shade=new float [SIZE*SIZE+SIZE];
UnitVector(LightDir);


  //lighting, could be placed immediately after map loading/generation, etc.
  // any elite coder could put this where he wanted.
  for(int y = 0; y < SIZE; y++)
  {
    for(int x = 0; x < SIZE; x++)
    {
      map_shade[y*SIZE+x] = 1 - (getHeight(Height_Map,x-LightDir.x, y-LightDir.y ) - getHeight(Height_Map,x, y )) / LIGHT_SOFTNESS;

      if(map_shade[y*SIZE+x] > MAX_BRIGHT)
        map_shade[y*SIZE+x] = MAX_BRIGHT;

      if(map_shade[y*SIZE+x] < MIN_BRIGHT)
        map_shade[y*SIZE+x] = MIN_BRIGHT;
    }
  }


};
void terrain::SetLight(int x,int y){
	int SIZE=Height_Map->w  ;        //your map size
	//float color=map_shade[y*SIZE+x];
	if(y*SIZE+x>SIZE*SIZE+SIZE){
		return;
	}
	glColor4f(map_shade[y*SIZE+x],map_shade[y*SIZE+x],map_shade[y*SIZE+x],Transparency);
};
vector2 terrain::GetSize(){
	vector2 Size;
	Size.x=Height_Map->w*Terrain_Scale.i;
	
	Size.y=Height_Map->w*Terrain_Scale.k;
	return Size;
};
bool terrain::BuildTerrain(){
   	
	glPushMatrix();
	
  // glEnable(GL_TEXTURE_2D);
	SDL_Surface* surface=Height_Map;
      Setup_Lighting();
	 Reflection_Map.BuildReflectionMap();
int Size_X=surface->w;
   int Size_Y=surface->h;
	  int  MAP_SIZE=Size_Y;
	int X = 0, Y = 0;						// Create some variables to walk the array with.
	int x, y, z;							// Create some variables for readability
	float fColor = 0.0f;					// Create a variable to hold our color of the polygon

	 
   terrain_list=glGenLists(1);				// Building Two Lists

  glNewList(terrain_list,GL_COMPILE);			// New Compiled box Display List




	    float fogColor[4] = {0.8f, 0.8f, 0.8f, 1.0f};

    glEnable(GL_FOG);                       // Turn on fog
    glFogi(GL_FOG_MODE, GL_LINEAR);         // Set the fog mode to LINEAR (Important)
    glFogfv(GL_FOG_COLOR, fogColor);        // Give OpenGL our fog color
    glFogf(GL_FOG_START, 0.0);              // Set the start position for the depth at 0
    glFogf(GL_FOG_END, FogDepth);               // Set the end position for the detph at 50
	
    // Now we tell OpenGL that we are using our fog extension for per vertex
    // fog calculations.  For each vertex that needs fog applied to it we must
    // use the glFogCoordfEXT() function with a depth value passed in.
    // These flags are defined in main.h and are not apart of the normal opengl headers.
    glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);


 	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,  Texture1.GetTexture());
  		glMatrixMode(GL_TEXTURE);

			// Reset the current matrix and apply our chosen scale value
			glLoadIdentity();
			glScalef((float)vector_detail1.i, (float)vector_detail1.j, vector_detail1.k);

		// Leave the texture matrix and set us back in the model view matrix
		glMatrixMode(GL_MODELVIEW);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);

  		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

glBindTexture(GL_TEXTURE_2D,  Texture2.GetTexture());
  		glMatrixMode(GL_TEXTURE);

			// Reset the current matrix and apply our chosen scale value
			glLoadIdentity();
			glScalef((float)vector_detail2.i, (float)vector_detail2.j, vector_detail2.k);

		// Leave the texture matrix and set us back in the model view matrix
		glMatrixMode(GL_MODELVIEW);
glEnable(GL_BLEND);
//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);					// Set Color To White With 80% Alpha




  //glBegin( GL_TRIANGLE_STRIP );					// Render Quads
	glBegin(GL_TRIANGLES);
	// Next we actually need to draw the terrain from the height map.
	// To do that, we just walk the array of height data and pluck out
	// some heights to plot our points.  If we could see this happening,
	// it would draw the columns first (Y), then draw the rows.
	// Notice that we have a STEP_SIZE.  This determines how defined our
	// height map is.  The higher the STEP_SIZE, the more blocky the terrain
	// looks, while the lower it gets, the more rounded it becomes.
	// If we set STEP_SIZE = 1 it would create a vertex for every pixel in the height map.
	// I chose 16 as a decent size.  Anything too much less gets to be insane and slow.
	// Of course, you can increase the number when you get lighting in.
	// Then vertex lighting would cover up the blocky shape.  Instead of lighting,
	// we just put a color value associated with every poly to simplify the tutorial.
	// The higher the polygon, the brighter the color is.
	bool bSwitchSides=false;
for ( X = 0; X <= MAP_SIZE; X += STEP_SIZE )
	{
		// Check if we need to render the opposite way for this column
		//if(bSwitchSides)
		//{
			// Render a column of the terrain, for this current X.
			// We start at MAP_SIZE and render down to 0.
			for ( Y = MAP_SIZE; Y > 0; Y -= STEP_SIZE )
			{
				// Get the (X, Y, Z) value for the bottom left vertex
				x = X;
				//y = GetHeight(X, Y );
				y = getHeight(surface,X, Y );
				z = Y;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				SetFogCoord(FogDepth, (float)y);
				SetLight(x,z);
				//glColor3f(map_shade[x][z],map_shade[x][z],map_shade[x][z]);
				glVertex3i(x, y, z);

				// Get the (X, Y, Z) value for the bottom right vertex
				x = X + STEP_SIZE;
				//y = GetHeight(X + STEP_SIZE, Y ); 
				y = getHeight(surface,X + STEP_SIZE, Y ); 
				z = Y;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				
				SetFogCoord(FogDepth, (float)y);
				SetLight(x,z);
				//glColor3f(map_shade[x][z],map_shade[x][z],map_shade[x][z]);
				glVertex3i(x, y, z);			

				
				
				
				
								// Get the (X, Y, Z) value for the bottom left vertex
				x = X+STEP_SIZE;
				//y = GetHeight(X+STEP_SIZE, Y+STEP_SIZE );
				y = getHeight(surface,X+STEP_SIZE, Y+STEP_SIZE );
				z = Y+STEP_SIZE;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				SetFogCoord(FogDepth, (float)y);
				SetLight(x,z);
				//glColor3f(map_shade[x][z],map_shade[x][z],map_shade[x][z]);
				glVertex3i(x, y, z);









				x = X+STEP_SIZE;
				//y = GetHeight(X+STEP_SIZE, Y+STEP_SIZE );
				y = getHeight(surface,X+STEP_SIZE, Y+STEP_SIZE );
				z = Y+STEP_SIZE;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				SetFogCoord(FogDepth, (float)y);
				SetLight(x,z);
				glVertex3i(x, y, z);

				// Get the (X, Y, Z) value for the bottom right vertex
				x = X;
				//y = GetHeight(X, Y+STEP_SIZE );
				y = getHeight(surface,X, Y+STEP_SIZE ); 
				z = Y+STEP_SIZE;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				SetFogCoord(FogDepth, (float)y);
				SetLight(x,z);
				//glColor3f(map_shade[x][z],map_shade[x][z],map_shade[x][z]);
				glVertex3i(x, y, z);			

				
				
				
				
								// Get the (X, Y, Z) value for the bottom left vertex
				x = X;
				//y = GetHeight(X, Y );
				y = getHeight(surface,X, Y );
				z = Y;

				// Set the current texture coordinate and render the vertex
				SetTextureCoord( (float)x, (float)z );
				SetFogCoord(FogDepth, (float)y);
				SetLight(x,z);
				//glColor3f(map_shade[x][z],map_shade[x][z],map_shade[x][z]);
				glVertex3i(x, y, z);
			}
	}

	glEnd();
	

glDisable(GL_BLEND);
 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);			// Reset The Color


   	glPopMatrix();

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D,  Texture1.GetTexture());
  		glMatrixMode(GL_TEXTURE);

			// Reset the current matrix and apply our chosen scale value
			glLoadIdentity();
			glScalef((float)1, (float)1,1);

		// Leave the texture matrix and set us back in the model view matrix
		glMatrixMode(GL_MODELVIEW);
  glEndList();									// Done Building The terrain List


    return true;
};
bool terrain::SetTexture1(char* file){

  	

return Texture1.LoadTexture(file);
};
bool terrain::SetHeightMap(char* file){
       Height_Map=SDL_LoadBMP(file);
  	   if(Height_Map==NULL){
		   return false;
	   }else{
		   terrain_file=file;
		   return true;
	   }
};

char* terrain::GetHeightMapFile(){
	return terrain_file;
};
bool terrain::SetTexture2(char* file){
          //cout<<"Test"<<endl;

     // cout<<"Setting texture2"<<endl;
      return Texture2.LoadTexture(file) ;;
};

bool terrain::SetTexture1Detail(phy_vector vector_detail){
  vector_detail1=vector_detail;
  return true;
};
bool terrain::SetTexture2Detail(phy_vector vector_detail){
  vector_detail2=vector_detail;
  return true;
};
float terrain::GetHeight(float x, float y){
	SDL_Surface* surface=Height_Map;
	 float z=y;
	phy_vector v1,v2;
	if(x>0&&y>0&&x<=surface->w&&y<surface->h){
		float h1,h2,h3;
		if((x-(int)x)>=(z-(int)z)){
			h1=getHeight(surface,(int)x,(int)z);
			h2=getHeight(surface,(int)x+STEP_SIZE,(int)z);
			h3=getHeight(surface,(int)x+STEP_SIZE,(int)z+STEP_SIZE);
			v1.i=STEP_SIZE;
			v1.j=h2-h1;
			v1.k=0;
			v2.i=STEP_SIZE;
			v2.j=h3-h1;
			v2.k=STEP_SIZE;
		}else{
			h1=getHeight(surface,(int)x+STEP_SIZE,(int)z+STEP_SIZE);
			h2=getHeight(surface,(int)x,(int)z+STEP_SIZE);
			h3=getHeight(surface,(int)x,(int)z);
			v1.i=-STEP_SIZE;
			v1.j=h2-h1;
			v1.k=0;
			v2.i=-STEP_SIZE;
			v2.j=h3-h1;
			v2.k=-STEP_SIZE;		
		}

	float t;
	phy_vector vn=NormalVector(v2,v1);
	if((x-(int)x)>=(z-(int)z)){
		t=vn.i*((int)x+STEP_SIZE)+vn.j*h2+vn.k*(int)z;
	}else{
		t=vn.i*((int)x)+vn.j*h2+vn.k*((int)z+STEP_SIZE);
	
	}//cout<<"vn.j "<<vn.k<<endl;
	float h=(t-vn.i*x-vn.k*z)/vn.j;
	
	//cout<<"Height "<<h<<endl;
	//float h=(h2-h1)*x+h1-(h2-h1)*(int)x;
		return h;
		//return getHeight(surface,x,y);//gets the height of the nearest pixel
	}else{
		return 0;
	}
};
float terrain::Height(float x, float y){
	SDL_Surface* surface=Height_Map;
	if(x>0&&y>0&&(x*1/Terrain_Scale.i)<=surface->w&&(y*1/Terrain_Scale.k)<surface->h){//Make sure that we are on the terrain
		//Important the get height gets the height of the nearest pixel so when you use large scaleing values there are rounding errors. 
		return GetHeight(x*1/Terrain_Scale.i,y*1/Terrain_Scale.k)*Terrain_Scale.j;//return the scaled height and position.
	}else{
		return 0;
	}
};

void terrain::Set_Terrain_Scale(phy_vector scale){
	Terrain_Scale.i=scale.i;
	Terrain_Scale.j=scale.j;
	Terrain_Scale.k=scale.k;
};
phy_vector terrain::Get_Terrain_Scale(){
	return Terrain_Scale;
};

void terrain::SetTransparency(float trans){//To take effect the terrain must be Rebuilt;
	if(trans>=0&&trans<=1){
		Transparency=trans;
	}
};
terrain::terrain(){
	LIGHT_SOFTNESS= 1  ;   //makes lighting more transitive, smooth, and less abrupt
	MAX_BRIGHT= 1;        //maximum brightness
	MIN_BRIGHT= 1 ;       //minimal brightness (hillsides are never pitch black during the day)
	fogdensity=0;
	FogDepth=0;
	STEP_SIZE=1;
	LightDir.x=1;
	LightDir.y=1;
	Transparency=1;
	Terrain_Scale.i=1;
	Terrain_Scale.k=1;
	Terrain_Scale.j=1;
};

float terrain::GetReflectionTransparency(float x,float z){
	return Reflection_Map.GetReflectionTransparency((x/Terrain_Scale.i),(z/Terrain_Scale.k));
};
bool terrain::SetReflectionMap(char* file){

		Reflection_Map.SetMapFile(file);
		
};

terrain::~terrain(){
	delete [] map_shade;
};
