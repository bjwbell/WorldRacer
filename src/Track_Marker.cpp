#include "../include/Track_Marker.h"

void track_marker::Render(){
	if(InitCalled!=true)
		return;
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);

	if(Terrain!=NULL){
		glTranslatef(position.x,Terrain->Height(position.x,position.y),position.y);
	}else{
		glTranslatef(position.x,0,position.y);
	}
	glRotatef(-90,1,0,0);
	
		glBindTexture(GL_TEXTURE_2D,Texture.GetTexture());
 
		//SetFogCoord(Terrain->GetFogDepth(),Terrain->Height(position.x,position.y),Terrain->GetFogDensity());
		gluCylinder(quadratic,radius,radius,height,32,32);
	glPopAttrib();
	glPopMatrix();
	
};
void track_marker::Init(){
	Type=type_track_marker;
	InitCalled=true;
	quadratic=gluNewQuadric();
	gluQuadricTexture(quadratic,GL_TRUE);
	gluQuadricNormals(quadratic,GL_SMOOTH);
	
};/*
void track_marker::SetPosition(vector2 par_position){
	position=par_position;
};
void track_marker::SetTextureFile(char* par_Texture_File){
	TextureFile=par_Texture_File;
	Texture.LoadFile(TextureFile);
};
void track_marker::SetTerrain(terrain *Terrain1){
	Terrain=Terrain1;
};
void track_marker::SetRadius(float Radius){
	radius=Radius;
};

*/
float track_marker::GetHeight(){
	return height;
};
void track_marker::SetHeight(float Height){
		height=Height;
};

