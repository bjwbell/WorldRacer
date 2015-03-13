#include "../include/Bush.h"
void bush::Init(){
	//Texture.LoadFile("data/Bush.tga");
	Type=type_bush;
	InitCalled=true;
	quadratic=gluNewQuadric();
	gluQuadricTexture(quadratic,GL_TRUE);
	gluQuadricNormals(quadratic,GL_SMOOTH);
};
void bush::Render(){
	
	if(InitCalled==true){
	
		glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	  
		glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		vector2 Pos;
		Pos.x=4890;
		Pos.y=5000;
	//glTranslatef(Pos.x,Terrain->Height(Pos.x,Pos.y),Pos.y);
	glTranslatef(position.x,Terrain->Height(position.x,position.y),position.y);
	//glRotatef(-90,1,0,0);
	
		glBindTexture(GL_TEXTURE_2D,Texture.GetTexture());
		cout<<"Rendering Bush"<<endl;
		//gluCylinder(quadratic,10,10,100,32,32);
		gluSphere(quadratic,radius,32,32);
	glPopAttrib();
	glPopMatrix();
	}
};
/*void bush::SetTerrain(terrain *var_Terrain){
	Terrain=var_Terrain;
};
void bush::SetPosition(vector2 var_Position){
	Position=var_Position;
};
vector2 bush::GetPosition(){
	return Position;
};
void bush::SetRadius(float var_Radius){
	Radius=var_Radius;
};
float bush::GetRadius(){
	return Radius;
};*/
