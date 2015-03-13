/***************************************************************************
                          Object_Loader.cpp  -  description
                             -------------------
    begin                : Fri Aug 30 2002
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
#include "../include/Object_Loader.h"
 void Object::objallocate(int n)							// Allocate Memory For Each Object
{											// And Defines points
    //(&Vertexes)->points=(VERTEX*)malloc(sizeof(VERTEX)*n);					// Sets points Equal To VERTEX * Number Of Vertices
	cout<<n<<endl;
	Quad=new quad[n];//(quad*)malloc(sizeof(quad)*n);
	//Vertexes.Quad=new quad[n];
	//Vertexes.Quad=(quad*)malloc(sizeof(quad)*n);			
}	
void Object::objfree()									// Frees The Object (Releasing The Memory)
{
	  free((&Vertexes)->points);								// Frees Points
}


void Object::readstr(FILE *f,char *string)							// Reads A String From File (f)
{
	  do										// Do This
      {
		    fgets(string, 255, f);							// Gets A String Of 255 Chars Max From f (File)
    } while ((string[0] == '/') || (string[0] == '\n'));				// Until End Of Line Is Reached
    return;										// Return
}

void Object::objload(char *name)							// Loads Object From File (name)
{
	  int	ver;									// Will Hold Vertice Count
    float	rx,ry,rz;								// Hold Vertex X, Y & Z Position
    FILE	*filein;								// Filename To Open
    char	oneline[255];								// Holds One Line Of Text (255 Chars Max)
    char *Texture_Name=(char*)malloc(256);
	char *File_Name=(char*)malloc(256);
	string test;
	//  cout<<"Test1"<<endl;
    filein = fopen(name, "rt");							// Opens The File For Reading Text In Translated Mode
    //cout<<"Test2"<<endl;
// CTRL Z Symbolizes End Of File In Translated Mode
    readstr(filein,oneline);							// Jumps To Code That Reads One Line Of Text From The File
    sscanf(oneline, "Vertices: %d\n", &ver);					// Scans Text For "Vertices: ".  Number After Is Stored In ver
    (&Vertexes)->verts=ver;									// Sets Objects verts Variable To Equal The Value Of ver

    objallocate(ver/4);								// Jumps To Code That Allocates Ram To Hold The Object
	   Quad[1].setX(512);
	readstr(filein,oneline);							// Jumps To Code That Reads One Line Of Text From The File
    sscanf(oneline, "Texture: %s\n", Texture_Name);					// Scans Text For "Vertices: ".  Number After Is Stored In ver
   //  cout<<"TYesting Texutre name "<<Texture_Name<<endl;
    int i=0;
	VERTEX vertex;
	bool break1=false;
	while(1==1)// Loops Through The Vertices
      {
		for(int y=0;y<5;y++){
			//cout<<"y "<<y<<endl;
			//cout<<"Testing"<<endl;
			readstr(filein,oneline);						// Reads In The Next Line Of Text
			
			
			sscanf(oneline, "File: %s/n", File_Name);	
			//cout<<"File_Name "<<File_Name<<endl;
			test=File_Name;
			//cout<<"String test "<<test<<endl;
			if(test=="EndFile"){
				break1=true;
				cout<<"Breaking"<<endl;
				break;
			};
			if(y==0){
				sscanf(oneline, "Texture: %s/n", File_Name);	
				//
				test=File_Name;
				if(test!=""){
			
					
					Quad[i].setTexture(File_Name);
				}else{
					Quad[i].setTexture(Texture_Name);
				}
			}else{
			sscanf(oneline, "%f %f %f", &rx, &ry, &rz);				// Searches For 3 Floating Point Numbers, Store In rx,ry & rz
			//cout<<"The line "<<oneline<<endl;
			//(&Vertexes)->points[i].x = rx;							// Sets Objects (k) points.x Value To rx
			//(&Vertexes)->points[i].y = ry;							// Sets Objects (k) points.y Value To ry
			//(&Vertexes)->points[i].z = rz;							// Sets Objects (k) points.z Value To rz
						// Sets Objects (k) points.y Value To ry
			//vertex.x=rx;
			//vertex.y=ry;
			//vertex.z=rz;
				//cout<<"i "<<i<<endl;
				//Quad[1].setVertex(0,1,1,1);
				//cout<<y-1<<" "<<rx<<" "<<ry<<" "<<rz<<endl;
				Quad[i].setVertex(y-1,rx,ry,rz);// = vertex;
			}
		}
		if(break1==true){
			break;
		}
		i+=1;
		//cout<<"i "<<i<<endl;
		// sscanf(oneline, "End File %s\n", File_Name);
	}
	fclose(filein);									// Close The File
   //cout<<"Test4"<<endl;
   //if(ver>maxver) maxver=ver;							// If ver Is Greater Than maxver Set maxver Equal To ver
	num_quads=ver/4;
   //cout<<"Num of Quads "<<num_quads<<endl;
   cout<<"Texture "<<Texture_Name<<endl;										// Keeps Track Of Highest Number Of Vertices Used
   Texture1.LoadTexture(Texture_Name);
}
bool Object::Render(){
//  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//  glTexGeni(GL_R,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
 // glEnable(GL_TEXTURE_GEN_S);

//  glEnable(GL_TEXTURE_GEN_R);
 // glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_2D);
//glBindTexture(GL_TEXTURE_2D, Texture1.GetTexture());
	cout<<"GetX "<<Quad[1].getX()<<endl;						// Begin Drawing Points
  float tx,ty,tz;
  
 for(int i=0;i<num_quads;i+=1)						// Loop Through All The Verts Of morph1 (All Objects Have
    {									// The Same Amount Of Verts For Simplicity, Could Use maxver Also)
		//cout<<"i "<<i<<endl;
	//	glBindTexture(GL_TEXTURE_2D, ((&Vertexes)->Quad[i]).getTexture());
	//cout<<"Test"<<endl;	
//quad Quad=*Vertexes.Quad;
		
	//	cout<<"O "<<Texture1.GetTexture()<<endl;
		glBindTexture(GL_TEXTURE_2D, Quad[i].getTexture());
		glBegin(GL_QUADS);	
		//for(int j=0;j<3;j+=1){
			//helper.points[i].x-=q.x;					// Subtract q.x Units From helper.points[i].x (Move On X Axis)
		  //helper.points[i].y-=q.y;					// Subtract q.y Units From helper.points[i].y (Move On Y Axis)
		  //helper.points[i].z-=q.z;					// Subtract q.z Units From helper.points[i].z (Move On Z Axis)
	//	cout<<tx<<endl;  
		tx=Quad[i].getVertex(0).x;						// Make Temp X Variable Equal To Helper's X Variable
		  ty=Quad[i].getVertex(0).y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=Quad[i].getVertex(0).z;						// Make Temp Z Variable Equal To Helper's Z Variable

		 // glColor3f(0,1,1);						// Set Color To A Bright Shade Of Off Blue
		  glTexCoord2f(0.0f, 0.0f);
			glVertex3f(tx,ty,tz);						// Draw A Point At The Current Temp Values (Vertex)

		
		
		
			  tx=Quad[i].getVertex(1).x;						// Make Temp X Variable Equal To Helper's X Variable
		  ty=Quad[i].getVertex(1).y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=Quad[i].getVertex(1).z;						// Make Temp Z Variable Equal To Helper's Z Variable

		 // glColor3f(0,1,1);						// Set Color To A Bright Shade Of Off Blue
		  glTexCoord2f(1.0f, 0.0f);
			glVertex3f(tx,ty,tz);				
		
			  tx=Quad[i].getVertex(2).x;						// Make Temp X Variable Equal To Helper's X Variable
		  ty=Quad[i].getVertex(2).y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=Quad[i].getVertex(2).z;						// Make Temp Z Variable Equal To Helper's Z Variable

		 // glColor3f(0,1,1);						// Set Color To A Bright Shade Of Off Blue
		  glTexCoord2f(1.0f, 1.0f);
			glVertex3f(tx,ty,tz);		
			
			
		  tx=Quad[i].getVertex(3).x;						// Make Temp X Variable Equal To Helper's X Variable
		  ty=Quad[i].getVertex(3).y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=Quad[i].getVertex(3).z;						// Make Temp Z Variable Equal To Helper's Z Variable

		 // glColor3f(0,1,1);						// Set Color To A Bright Shade Of Off Blue
		  glTexCoord2f(0.0f, 1.0f);
			glVertex3f(tx,ty,tz);	
		//}
		/*  tx=(&Vertexes)->points[i+1].x;						// Make Temp X Variable Equal To Helper's X Variable
		  ty=(&Vertexes)->points[i+1].y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=(&Vertexes)->points[i+1].z;						// Make Temp Z Variable Equal To Helper's Z Variable
		  glTexCoord2f(1.0f, 0.0f);
		  glVertex3f(tx,ty,tz);						// Draw A Point At The Current Temp Values (Vertex)


		   tx=(&Vertexes)->points[i+2].x;						// Make Temp X Variable Equal To Helper's X Variable
		  ty=(&Vertexes)->points[i+2].y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=(&Vertexes)->points[i+2].z;						// Make Temp Z Variable Equal To Helper's Z Variable
		  glTexCoord2f(1.0f, 1.0f);
		  glVertex3f(tx,ty,tz);						// Draw A Point At The Current Temp Values (Vertex)

		   tx=(&Vertexes)->points[i+3].x;						
			ty=(&Vertexes)->points[i+3].y;						// Make Temp Y Variable Equal To Helper's Y Variable
		  tz=(&Vertexes)->points[i+3].z;						// Make Temp Z Variable Equal To Helper's Z Variable
		  glTexCoord2f(0.0f, 1.0f);
		  glVertex3f(tx,ty,tz);	*/					// Draw A Point At The Current Temp Values (Vertex)

		//}
glEnd();	
}									// This Creates A Ghostly Tail As Points Move
								// Done Drawing Points

  return true;
}













