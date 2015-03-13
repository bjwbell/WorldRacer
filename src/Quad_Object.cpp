#include "../include/Quad_Object.h"
VERTEX quad::getVertex1(){
		return vertex[1];
	};
	
VERTEX quad::getVertex2(){
		return vertex[2];
	};
	
VERTEX quad::getVertex3(){
		return vertex[3];
	};
	
VERTEX quad::getVertex4(){
		return vertex[4];
	};
	
bool quad::setVertex1(float x , float y, float z){
		vertex[0].x=x;
		vertex[0].y=y;
		vertex[0].z=z;
	
		return true;
	};
	
bool quad::setVertex2(float x , float y,float z){
		vertex[1].x=x;
		vertex[1].y=y;
		vertex[1].z=z;
		return true;
	};
	
bool quad::setVertex3(float x,float y, float z){
		vertex[2].x=x;
		vertex[2].y=y;
		vertex[2].z=z;
		return true;
	};
	
bool quad::setVertex4(float x , float y,float z){
		vertex[3].x=x;
		vertex[3].y=y;
		vertex[3].z=z;
	
		return true;
	};
	
bool quad::setVertex(int num,float x , float y,float k){
		if(num>=0&&num<=3){
			vertex[num].x=x;
			vertex[num].y=y;
			vertex[num].z=k;
	
			return true;
		}else{
				return false;
		}
	};	
VERTEX quad::getVertex(int num){
		try{
		if(num>=0&&num<=3){
			return vertex[num];
		}else{
			cout<<"Error in getting vertex"<<endl;
		}
	}
	catch(int n){
		cout<<"Error in getting verttex"<<endl;
		}
	}
bool quad::setTexture(char* file_name){
	//	cout<<"Setting texture"<<endl;
	//	x=5;
		//Texture1.LoadTexture("Right.tga");
		//cout<<"Getting this freaking teexture "<<Texture1.GetTexture()<<endl;
	return Texture1.LoadTexture(file_name);
	};

GLuint quad::getTexture(){
		//return x;
		return Texture1.GetTexture();
	};	
bool quad::setX(int X){
	//	cout<<"Setting texture"<<endl;
		x=X;
		//Texture1.LoadTexture("Right.tga");
		//cout<<"Getting this freaking teexture "<<Texture1.GetTexture()<<endl;
	//return Texture1.LoadTexture(file_name);
	};

int quad::getX(){
		return x;
		//return Texture1.GetTexture();
	};	
