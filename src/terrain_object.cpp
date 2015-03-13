#include "../include/terrain_object.h"
void terrain_object::Init(){
	//Type=type_bush;
	InitCalled=true;
	quadratic=gluNewQuadric();
	gluQuadricTexture(quadratic,GL_TRUE);
	gluQuadricNormals(quadratic,GL_SMOOTH);
	
};
void terrain_object::SetPosition(vector2 par_position){
	position=par_position;
};
void terrain_object::SetTextureFile(char* par_Texture_File){
	TextureFile=par_Texture_File;
	Texture.LoadFile(TextureFile);
};
char* terrain_object::GetTextureFile(){
	return TextureFile;
};
void terrain_object::SetTerrain(terrain *Terrain1){
	Terrain=Terrain1;
};
void terrain_object::SetRadius(float Radius){
	radius=Radius;
};

float terrain_object::GetRadius(){
	return radius;
}
object_type terrain_object::GetObjectType(){
	return Type;
}
vector2 terrain_object::GetPosition(){
	return position;
};
/*void terrain_object::SetHeight(float Height){
		height=Height;
};*/

