#include "../include/player.h"
//void player::SetParent(game* Parent){
//	parent=Parent;
//};
void player::SetPosition(phy_vector position){
	Player_Position=position;
};
phy_vector player::GetPosition(){
	return Player_Position;
};
void player::SetVelocity(phy_vector velocity){
		Player_Velocity=velocity;
};
phy_vector player::GetVelocity(){
		return Player_Velocity;
};
void player::SetRotation(float rotation){
	Player_Rotation=rotation;
};
float player::GetRotation(){
	return Player_Rotation;
};

void player::SetAcceleration(phy_vector acceleration){
	Acceleration=acceleration;
};


phy_vector player::GetAcceleration(){
	return Acceleration;
};
bool player::UpdatePositionVelocity(float t){
	Player_Velocity.i=Player_Velocity.i+Acceleration.i*t;
	Player_Velocity.j=Player_Velocity.j+Acceleration.j*t;
	Player_Velocity.k=Player_Velocity.k+Acceleration.k*t;
	Player_Position.i=Player_Position.i+Player_Velocity.i*t;
	Player_Position.k=Player_Position.k+Player_Velocity.k*t;
	Player_Position.j=Player_Position.j+Player_Velocity.j*t;
	return true;
};

void player::SetPlayerForce(phy_vector Force){
	player_force=Force;
};
bool player::UpdateAccelerationPosition(float t){
		if(Terrain==NULL){
		cout<<"Terrain not set for player"<<endl;
		return false;
	}

//	static bool not_first_time;

	
	phy_vector Force=FindForceOnPlayer();
	phy_vector Accer;

	Force.i=Force.i/4000+player_force.i;
	Force.j=Force.j/4000+player_force.j;
	Force.k=Force.k/4000+player_force.k;
	Accer=Force;//set equal since mass==1
	

	
	
	

		

	
	//player_force.j=player_force.j;

	//Accer=player_force;
	
		
		SetAcceleration(Accer);
		
	
       float Height=Terrain->Height(GetPosition().i,GetPosition().k)+4;
		
		phy_vector Player_Position=GetPosition();
		Player_Position.j=Height;
		if(GetPosition().j<Player_Position.j){
			SetPosition(Player_Position);	
		}
		if(GetPosition().j>Player_Position.j+.5){	
			Accer.j=-.00001;//apply gravity
			SetAcceleration(Accer);
		}
		UpdatePositionVelocity(t);
	return true;
};









bool player::SetTerrain(terrain *Terrain1){
		if(Terrain1!=NULL){
			Terrain=Terrain1;
			return true;
		}else{
			cout<<"Error trying to set NULL terrian for player"<<endl;
			return false;
		};
};
phy_vector player::FindForceOnPlayer(){
		if(Terrain==NULL){
		cout<<"Terrain not set for player"<<endl;
		//return false;
	}



	


	 



	double m=1;
	point Point=GetPoint();
	phy_vector vector1,vector2;
	phy_vector Slope;
	FindPlaneVectors(vector1,vector2);

	Slope=FindPlaneSlope(Point,vector1,vector2);
		
	phy_vector Force=FindForceXYZ(Slope,m);	


	
	return Force;

}

point player::GetPoint(){
	point Point;
	Point.x=GetPosition().i;
	Point.y=GetPosition().j;
	Point.z=GetPosition().k;
	return Point;
};

void player::FindPlaneVectors(phy_vector &vector1,phy_vector &vector2){

	point Point=GetPoint();


	float Height1=Terrain->Height(Point.x,Point.z);
	float Height2=Terrain->Height(Point.x+1,Point.z);
	float Height3=Terrain->Height(Point.x+1,Point.z+1);
	float delta_height=Height2-Height1;
	float delta_k=1;
	float delta_i=1;
	vector1.i=delta_i;
	vector2.i=delta_i;
	vector1.k=delta_k;
	vector2.k=delta_k;
	vector1.j=delta_height;
	delta_height=Height3-Height2;
	
	vector2.j=delta_height;
};

bool player::Render(){
	
//glDepthRange(1,0);	
		glEnable(GL_TEXTURE_2D);
glEnable( GL_CULL_FACE );

 glPushMatrix() ;  
        
glTranslatef(this->GetPosition().i,this->GetPosition().j,this->GetPosition().k);
 vector3 par_position;
	par_position.x=this->GetPosition().i;
	par_position.y=this->GetPosition().j;
	par_position.z=this->GetPosition().k;
	this->SetPos(par_position);
	
	glRotatef(90-this->GetRotation(),0,1,0);
	
 glRotatef(-60,0,0,1);
//	glRotatef(180,1,0,0);
      glScalef(0.25, 0.25, 0.25);
	
		this->DrawModel(); 
glScalef(1, 1, 1);
 

glPopMatrix();

glDisable( GL_CULL_FACE );
//glDepthRange(0,1);
RenderShadow();
	return true;
};

void player::RenderShadow(){


// Clear Screen, Depth Buffer & Stencil Buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glMatrixMode( GL_MODELVIEW );
   // glLoadIdentity( );
	glPushMatrix();
phy_vector Pos=this->GetPosition();

	glLoadIdentity();									// Reset The Modelview Matrix

	glColorMask(0,0,0,0);								// Set Color Mask

														// Replace If Test Passes
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	Terrain->Render();										// Draw The Floor (Draws To The Stencil Buffer)
														// We Only Want To Mark It In The Stencil Buffer
	glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
	
		 
	glColorMask(1,1,1,1);								// Set Color Mask to true, true, true, true

	glPushMatrix();										// Push The Matrix Onto The Stack

		glTranslatef(0.0f,Terrain->Height(this->GetPosition().i,this->GetPosition().k), 0.0f);				// Position The Object
		glScalef(1,-1,1);
	if(-Terrain->Height(this->GetPosition().i,this->GetPosition().k)+Pos.j-2>5){//cheack to make sure the shadow doesn't go through the terrain
		glTranslatef(0.0f,-Terrain->Height(this->GetPosition().i,this->GetPosition().k)+Pos.j-2, 0.0f);				// Position The Object
	}else{
		glTranslatef(0.0f,5, 0.0f);				// Position The Object
	}

		float height=Player_Position.j;
		Player_Position.j=0;

	
		glDepthRange(1,0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
		glColor4f(0,0,0,1);
		
		
		
		
		glDisable(GL_TEXTURE_2D);
glEnable( GL_CULL_FACE );

 glPushMatrix() ;  
        
glTranslatef(this->GetPosition().i,this->GetPosition().j,this->GetPosition().k);
 vector3 par_position;
	par_position.x=this->GetPosition().i;
	par_position.y=this->GetPosition().j;
	par_position.z=this->GetPosition().k;
	this->SetPos(par_position);
	
	glRotatef(90-this->GetRotation(),0,1,0);
	glRotatef(-60,0,0,1);
	glRotatef(180,1,0,0);
      glScalef(0.25, 0.25, 0.25);
	
		this->DrawModel(); 
	glScalef(1, 1, 1);
 

	glPopMatrix();

	glDisable( GL_CULL_FACE );	
	glEnable(GL_TEXTURE_2D);
		//glRotatef(-180,0,0,0);
		glDisable(GL_BLEND);
		glDepthRange(0,1);
		//glEnable(GL_DEPTH_TEST);
		Player_Position.j=height;
		//this->DrawModel();									// Draw The Sphere (Reflection)
	glPopMatrix();										// Pop The Matrix Off The Stack
	glDisable(GL_CLIP_PLANE0);							// Disable Clip Plane For Drawing The Floor
	glDisable(GL_STENCIL_TEST);							// We Don't Need The Stencil Buffer Any More (Disable)
	
	


	
	
};




void player::RenderReflection(){


// Clear Screen, Depth Buffer & Stencil Buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glMatrixMode( GL_MODELVIEW );
   // glLoadIdentity( );
	glPushMatrix();

	phy_vector Pos=this->GetPosition();
	trans=Terrain->GetReflectionTransparency(Pos.i,Pos.k);
	
	vector3 Vectors[3];
	 Vectors[1].x=Pos.i; Vectors[1].y=Terrain->Height(Pos.i,Pos.k-1);Vectors[1].z=Pos.k-1;
	 
	
	
	Vectors[2].x=Pos.i-1;Vectors[2].y=Terrain->Height(Pos.i-1,Pos.k+1);Vectors[2].z=Pos.k+1;
	
	
	Vectors[3].x=Pos.i+1;Vectors[3].y=Terrain->Height(Pos.i+1,Pos.k+1);Vectors[3].z=Pos.k+1;
	

	 
	 plane Plane=FindClipPlane(Vectors);
	 
	 double eqr[] = {Plane.A,Plane.B, Plane.C, Plane.D};			// Plane Equation To Use For The Reflected Objects

	glLoadIdentity();									// Reset The Modelview Matrix

	glColorMask(0,0,0,0);								// Set Color Mask
	//glEnable(GL_STENCIL_TEST);							// Enable Stencil Buffer For "marking" The Floor
	//glStencilFunc(GL_ALWAYS, 1, 1);						// Always Passes, 1 Bit Plane, 1 As Mask
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);			// We Set The Stencil Buffer To 1 Where We Draw Any Polygon
														// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
														// Replace If Test Passes
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	Terrain->Render();										// Draw The Floor (Draws To The Stencil Buffer)
														// We Only Want To Mark It In The Stencil Buffer
	glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
	
		 
	glColorMask(1,1,1,1);								// Set Color Mask to true, true, true, true
	//glStencilFunc(GL_EQUAL, 1, 1);						// We Draw Only Where The Stencil Is 1
														// (I.E. Where The Floor Was Drawn)
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Don't Change The Stencil Buffer
	//glEnable(GL_CLIP_PLANE0);broken for now needs 	// Enable Clip Plane For Removing Artifacts
							 //to be fixed				// (When The Object Crosses The Floor)
	//glClipPlane(GL_CLIP_PLANE0, eqr);					// Equation For Reflected Objects*/
	glPushMatrix();										// Push The Matrix Onto The Stack

		glTranslatef(0.0f,Terrain->Height(this->GetPosition().i,this->GetPosition().k), 0.0f);				// Position The Object
		glScalef(1,-1,1);
	
		glTranslatef(0.0f,-Terrain->Height(this->GetPosition().i,this->GetPosition().k)+Pos.j-2, 0.0f);				// Position The Object
		

				float height=Player_Position.j;
		Player_Position.j=0;

	
		glDepthRange(1,0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1,1,1,trans);
		
		
		
		
		glEnable(GL_TEXTURE_2D);
glEnable( GL_CULL_FACE );

 glPushMatrix() ;  
        
glTranslatef(this->GetPosition().i,this->GetPosition().j,this->GetPosition().k);
 vector3 par_position;
	par_position.x=this->GetPosition().i;
	par_position.y=this->GetPosition().j;
	par_position.z=this->GetPosition().k;
	this->SetPos(par_position);
	
	glRotatef(90-this->GetRotation(),0,1,0);
 glRotatef(-60,0,0,1);
glRotatef(180,1,0,0);
      glScalef(0.25, 0.25, 0.25);
	
		this->DrawModel(); 
glScalef(1, 1, 1);
 

glPopMatrix();

glDisable( GL_CULL_FACE );	

		//glRotatef(-180,0,0,0);
		glDisable(GL_BLEND);
		glDepthRange(0,1);
		//glEnable(GL_DEPTH_TEST);
		Player_Position.j=height;
		//this->DrawModel();									// Draw The Sphere (Reflection)
	glPopMatrix();										// Pop The Matrix Off The Stack
	glDisable(GL_CLIP_PLANE0);							// Disable Clip Plane For Drawing The Floor
	glDisable(GL_STENCIL_TEST);							// We Don't Need The Stencil Buffer Any More (Disable)
	
	


	
	
};

AI_player::AI_player(){
	trans=0;
	
	max_speed=0.55;
	speed_mult=.45;
	first_time_called=true;
	//	parent=0;
};

void AI_player::SetSpeedMultiplyer(float new_speed_multiplyer){
	speed_mult=new_speed_multiplyer;
};

bool AI_player::Update(float t){
	//speed_divider=3;
	//Path.PathFile("Path.txt");
		phy_vector Path_Position=Path.GetPosition();
	
	//cout<<Path_Position.i<<endl;
	phy_vector Player_Position=this->GetPosition();
	
	phy_vector Direction_To_Move;
	Direction_To_Move.i=Path_Position.i-Player_Position.i;
	Direction_To_Move.k=Path_Position.k-Player_Position.k;	
	float mag=sqrt(pow(Direction_To_Move.i,2)+pow(Direction_To_Move.k,2));
	if(mag==0){
		//Path.GotoNextPosition();
	}else{
	Direction_To_Move.i=Direction_To_Move.i/mag;//Make the movement vector a unit vector;
	Direction_To_Move.k=Direction_To_Move.k/mag;
	bool moved=false;
	if(Direction_To_Move.i<=0){
		if((Player_Position.i+Direction_To_Move.i*t*speed_mult)<=Path_Position.i){
			Player_Position.i=Path_Position.i;
			if(moved==false){
				Path.GotoNextPosition();
				moved=true;
			}
		}else{
			Player_Position.i=Player_Position.i+Direction_To_Move.i*t*speed_mult;
			
		}
	}else{
		if((Player_Position.i+Direction_To_Move.i*t*speed_mult)>=Path_Position.i){
			Player_Position.i=Path_Position.i;
			if(moved==false){
				Path.GotoNextPosition();
				moved=true;
			}
		}else{
			Player_Position.i=Player_Position.i+Direction_To_Move.i*t*speed_mult;
		}
	}

	if(Direction_To_Move.k<=0){
		if((Player_Position.k+Direction_To_Move.k*t*speed_mult)<=Path_Position.k){
			Player_Position.k=Path_Position.k;
			if(moved==false){
				Path.GotoNextPosition();
				moved=true;
			}
		}else{
			Player_Position.k=Player_Position.k+Direction_To_Move.k*t*speed_mult;
			
		}
	}else{
		if((Player_Position.k+Direction_To_Move.k*t*speed_mult)>=Path_Position.k){
			Player_Position.k=Path_Position.k;
			if(moved==false){
				Path.GotoNextPosition();
				moved=true;
			}
		}else{
			Player_Position.k=Player_Position.k+Direction_To_Move.k*t*speed_mult;
		}
	}	
	
}
	Player_Position.j=Terrain->Height(Player_Position.i,Player_Position.k)+4;
	if(Direction_To_Move.i==0){
		if(Direction_To_Move.k==0){
		}else{
			if(Direction_To_Move.k>0){
				this->SetRotation(90);
			}else{
				this->SetRotation(-90);
			}
		}
	}else{
		if(Direction_To_Move.k==0){
			if(Direction_To_Move.i>0){
				this->SetRotation(0);
			}else{
				this->SetRotation(180);
			}
		}else{
			if(Direction_To_Move.i>0){
				float angle=atan(Direction_To_Move.k/Direction_To_Move.i)+3.14/2;
				angle=angle*180/3.141592;
				this->SetRotation(angle);
			}else{
				float angle=atan(Direction_To_Move.k/Direction_To_Move.i)+3.141592+3.14/2;
				angle=angle*180/3.141592;
				this->SetRotation(angle);				
			}
		}
	}
	
	this->SetPosition(Player_Position);

return true;
};
void AI_player::SetNewAISpeed(Human_player* Player){
	
	FindClosestNodesToHumanPlayer(Player);
	//int current_node_num=Path.GetCurrentNodeNumber();
};

void AI_player::SetTrack(track* var_Track){
	Track=var_Track;
	string Path_Path=Track->directory+"/Path.txt";
	
	Path.PathFile((char*)Path_Path.c_str());
};
bool AI_player::SetPath(path var_path){
	
		Path=var_path;	
		return true;	

};
int AI_player::GetClosestNodeToHumanPlayer(Human_player *Player){
	phy_vector Position=Player->GetPosition();
	phy_vector node1,node2;
	int num_nodes=Path.GetNumNodes();
	vector<phy_vector> Nodes=Path.GetPath();
	float distance[num_nodes-2];
//if(first_time_called==true){	
	for(int i=0;i<num_nodes;i++){
		
		node1=Nodes[i];
		node2=Nodes[i+1];
		distance[i]=find_min_distance_between_points_through_line(node1,node2,Position);
	}

	int smallest_distance_node=0;
	float smallest_distance=0;
	
//if(first_time_called==true){	
	first_time_called=false;
	for(int i=0;i+1<num_nodes;i++){
		//cout<<"i "<<i<<endl;
		if(0==i){
			smallest_distance_node=0;
			smallest_distance=distance[0];
		}else{
			if(distance[i]<smallest_distance){
				smallest_distance_node=i;
				smallest_distance=distance[i];			
			}
		}
	}

	node_num=smallest_distance_node;

node_num=smallest_distance_node;
return smallest_distance_node;
}

void AI_player::FindClosestNodesToHumanPlayer(Human_player* Player){
	
	//float speed_mult=0.45;
	int close_node=GetClosestNodeToHumanPlayer(Player);
	if(Path.GetCurrentNodeNumber()==(close_node+1)){//AI is next to player;
		//SetSpeedMultiplyer(10.45);
		SetSpeedMultiplyer(max_speed-0.1);
	
	}
	if(Path.GetCurrentNodeNumber()>close_node+1){//AI is infront of player;
		//SetSpeedMultiplyer(10.45);
		SetSpeedMultiplyer(max_speed-0.2);
	}
	
	if(Path.GetCurrentNodeNumber()<=close_node){//AI is behind player;
		//SetSpeedMultiplyer(10.45);
		SetSpeedMultiplyer(max_speed);
	}
};


void AI_player::SetConfig(const char* Config_File){
	config_file=Config_File;
									
	FILE	*filein;									// Filename To Open
	char	oneline[255];								// Holds One Line Of Text (255 Chars Max)
	
	filein = fopen(config_file, "rt");							// Opens The File For Reading Text In Translated Mode
    if(!filein) {
        printf("failed to open file: %s\n", config_file);
        return;
		//exit(0);
    }
														
	readstr(filein,oneline);							
	
	
	

	for(int i=1;i<=1;i++)							
	{
							
			switch(i){
			
				case 1:	sscanf(oneline, "MAX_SPEED %f", &max_speed);break;
							
			}
			
			readstr(filein,oneline);// Reads In The Next Line Of Text	
	}

	fclose(filein);	
};




void Human_player::SetConfig(const char* Config_File){
	config_file=Config_File;
									
	FILE	*filein;									// Filename To Open
	char	oneline[255];								// Holds One Line Of Text (255 Chars Max)
	
	filein = fopen(config_file, "rt");							// Opens The File For Reading Text In Translated Mode
    if(!filein) {
        printf("failed to open file: %s\n", config_file);
        return;
		//exit(0);
    }
														
	readstr(filein,oneline);							
	
	
	
	
	for(int i=1;i<=2;i++)							
	{
							
			switch(i){
			
				case 1:	sscanf(oneline, "MAX_HEIGHT %f", &max_height);break;
				case 2: sscanf(oneline,"MAX_SPEED %f",&max_speed);break;	
							
			}
			
			readstr(filein,oneline);// Reads In The Next Line Of Text	
	}

	fclose(filein);	
};

void Human_player::SetMaxHeight(float Max_Height){
	max_height=Max_Height;
};
bool Human_player::SetMaxSpeed(float Max_Speed){
	if(Max_Speed>=0){
		max_speed=Max_Speed;
		return true;
	}else{
		return false;
	};
}

bool Human_player::Update(float t){
	
	if(Terrain==NULL){
		cout<<"Terrain not set for player"<<endl;
		return false;
	}

//	static bool not_first_time;

	phy_vector force;
//	phy_vector Accer;
	force.i=0;
	force.j=0;
	force.k=0;
	

	 
	if (Left_Key_Pressed==true){
			SetRotation(GetRotation()-250*t/1000);
    }
    if (Right_Key_Pressed==true){
         SetRotation(GetRotation()+250*t/1000);
	}

       if (Up_Key_Pressed==true){
			  force.k=-.0005*cos(3.141592/180*GetRotation());
             force.i=.0005*sin(3.141592/180*GetRotation());
			phy_vector Direction;
			Direction.k=cos(3.141592/180*GetRotation());
			Direction.i=sin(3.141592/180*GetRotation());
			Direction.j=0;
			point Point=GetPoint();
			phy_vector v1,v2,gradiant;
			 FindPlaneVectors(v1,v2);
			 gradiant=FindPlaneGradiant(Point,v1,v2);	
			 float slope=FindDirectionalDerivative(gradiant,Direction);
			  
			 force.j=0.0005*sin(atan(slope));
		  // this->SetLegsAnimation("LEGS_RUN");
		
		 }

         if (Down_Key_Pressed==true){
		  force.i=-.0005*sin(3.141592/180*GetRotation());
           force.k=.0005*cos(3.141592/180*this->GetRotation());
			phy_vector Direction;
			Direction.k=cos(3.141592/180*GetRotation());
			Direction.i=sin(3.141592/180*GetRotation());
			Direction.j=0;
			point Point=GetPoint();
			phy_vector v1,v2,gradiant;
			 FindPlaneVectors(v1,v2);
			 gradiant=FindPlaneGradiant(Point,v1,v2);	
			 float slope=FindDirectionalDerivative(gradiant,Direction);
			  
			 force.j=-0.0005*sin(atan(slope));		  
			//this->SetLegsAnimation("LEGS_IDLE");
			 // this->SetLegsAnimation("LEGS_RUN");
			 //force.j=?
		}
		if(Down_Key_Pressed==false&&Up_Key_Pressed==false){
			
		}
		
			point Point=GetPoint();
			phy_vector v1,v2,gradiant;
			 FindPlaneVectors(v1,v2);
			 gradiant=FindPlaneGradiant(Point,v1,v2);	
		
	
	this->SetPlayerForce(force);

	this->UpdateAccelerationPosition(t);
			//if(Down_Key_Pressed==false&&Up_Key_Pressed==false){
					float Height=Terrain->Height(GetPosition().i,GetPosition().k)+4;
					//cout<<"Height "<<Height<<endl;
					phy_vector Position2=GetPosition();
					Position2.j=Height;
					if(GetPosition().j<=Position2.j){//only apply friction while on the ground
						
						phy_vector Velocity=Apply_Friction(this->GetVelocity(),1,0.00003,t);
						
						SetVelocity(Velocity);
							
					}
			

			//}
		
	       Height=Terrain->Height(GetPosition().i,GetPosition().k)+4;
		
		if((this->GetVelocity().i*this->GetVelocity().i+this->GetVelocity().j*this->GetVelocity().j+this->GetVelocity().k*this->GetVelocity().k)>max_speed*max_speed){
			float mag=sqrt(this->GetVelocity().i*this->GetVelocity().i+this->GetVelocity().j*this->GetVelocity().j+this->GetVelocity().k*this->GetVelocity().k);
			float scalar=max_speed/mag;
			phy_vector Vel;
			Vel.i=scalar*this->GetVelocity().i;//reduce the speed to the maximum speed
			Vel.j=scalar*this->GetVelocity().j;
			Vel.k=scalar*this->GetVelocity().k;
			this->SetVelocity(Vel);
		};
		phy_vector Player_Position=GetPosition();
		
		Player_Position.j=Height;
		if(GetPosition().j<Player_Position.j){
			if(Player_Position.j>=max_height){
					phy_vector Vel;
					Vel.i=0;//reduce the speed to the maximum speed
					Vel.j=0;
					Vel.k=0;
					this->SetVelocity(Vel);
			}
			SetPosition(Player_Position);	
		}
	
	return true;
};

void Human_player::Set_Key_Pressed(SDL_Event Event,bool KeyPressed){
	if(Event.key.keysym.sym==SDLK_UP){
		if(KeyPressed==false&&Down_Key_Pressed==false){
			FreezeAnimation();
		}
		if(KeyPressed==true){
			UnFreezeAnimation();
		}
		Up_Key_Pressed=KeyPressed;
	};
	if(Event.key.keysym.sym==SDLK_DOWN){
		if(KeyPressed==false&&Up_Key_Pressed==false){
			FreezeAnimation();
		}
		if(KeyPressed==true){
			UnFreezeAnimation();
		}	
		
		
		Down_Key_Pressed=KeyPressed;
	};
	if(Event.key.keysym.sym==SDLK_LEFT){
		Left_Key_Pressed=KeyPressed;
	};
	if(Event.key.keysym.sym==SDLK_RIGHT){
		Right_Key_Pressed=KeyPressed;
	};
	
};
Human_player::Human_player(){
	
	max_height=0;
	max_speed=0;
	trans=0;
};
