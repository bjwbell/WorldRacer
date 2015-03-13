#include "../include/HUD.h"
hud::hud(){
	Speed_Display.SetSpeed(0);
}
void hud::Render(){
	glDisable(GL_FOG);
	Display_Speed(Speed);
	Display_Num_Laps(Num_Laps_Completed,Num_Laps);
	Display_Map(Player_Position,AI_Position);
	glEnable(GL_FOG);
};
void hud::SetPlayerSpeed(float speed){
	Speed=speed;
};
void hud::SetPosition(vector2 player_position,vector2 ai_position){
	Player_Position=player_position;
	AI_Position=ai_position;
};
void hud::SetNumLapsCompleted(int num_laps){
	Num_Laps_Completed=num_laps;
};
void hud::SetTotalNumLaps(int num_laps){
	Num_Laps=num_laps;
};

void hud::SetTrack(track* var_Track){
	Track=var_Track;
	string Map_Path=Track->directory+"/Map.tga";
	map.LoadTexture((char*)Map_Path.c_str());

};
void hud::Init(screen_dimension var_Screen_Dimension){
	Display_Text.BuildFont();
	Screen_Dimension=var_Screen_Dimension;
	AI_icon.LoadTexture("data/AI_Icon.tga");
	player_icon.LoadTexture("data/Player_Icon.tga");	
	//string Map_Path=Track->directory+"/Map.tga";
	//map.LoadTexture((char*)Map_Path.c_str());
	
	Speed_Display.Init();
}
void hud::Display_Speed(float speed){
	Speed_Display.SetSpeed(speed);
	Speed_Display.Display_Speed();
};
void hud::Display_Num_Laps(int num_laps_completed,int num_laps){
    
	
	glColor3f(1,1,1);
	Display_Text.glPrint(0,0,"Lap %1.0d/%1.0d",num_laps_completed,num_laps);	
};
void hud::Display_Map(vector2 player_position,vector2 AI_position){
	
	//load the map as a texture then change to an ortho view and display on the screen.
	//load player_icon and AI_icon and display over the map.
    /* Disable depth testing */
 
	glDisable( GL_DEPTH_TEST );

    /* Select The Projection Matrix */
    glMatrixMode( GL_PROJECTION );
    /* Store The Projection Matrix */
    glPushMatrix( );

    /* Reset The Projection Matrix */
    glLoadIdentity( );
    /* Set Up An Ortho Screen */
    glOrtho( 0, Screen_Dimension.width, 0, Screen_Dimension.height, -1, 1 );
 //glOrtho( 0, 640, 0, 480, -1, 1 );

    /* Select The Modelview Matrix */
    glMatrixMode( GL_MODELVIEW );
    /* Stor the Modelview Matrix */
    glPushMatrix( );
    /* Reset The Modelview Matrix */
    glLoadIdentity( );
       glEnable(GL_BLEND);             // Turn Blending On
	                   // Full Brightness, 50% Alpha ( NEW )
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
      glColor4f(1.0f,1.0f,1.0f,0.6f); 
	/* Position The Text (0,0 - Bottom Left) */
    glTranslated( 640-64, 480-64, 0 );
	glBindTexture( GL_TEXTURE_2D, map.GetTexture() );

	      glBegin( GL_QUADS );
	        /* Texture Coord (Bottom Left) */
	    glTexCoord2f( 0, 1 );
		/* Vertex Coord (Bottom Left) */
		glVertex2i( 0, 0 );

		/* Texture Coord (Bottom Right) */
		glTexCoord2f( 1, 1 );
		/* Vertex Coord (Bottom Right) */
		glVertex2i( 64, 0 );

		/* Texture Coord (Top Right) */
		glTexCoord2f( 1, 0 );
		/* Vertex Coord (Top Right) */
		glVertex2i( 64, 64 );

		/* Texture Coord (Top Left) */
		glTexCoord2f(0, 0);
		/* Vertex Coord (Top Left) */
		glVertex2i( 0, 64 );
	      glEnd( );

	
	glLoadIdentity();
	glTranslated( player_position.x/80-122/2+Screen_Dimension.width-4,-player_position.y/80+122/2+Screen_Dimension.height-64 , 0 );
	glBindTexture( GL_TEXTURE_2D, player_icon.GetTexture() );
 glColor4f(1.0f,1.0f,1.0f,1.0f); 
	      glBegin( GL_QUADS );
	       
	    glTexCoord2f( 0, 0 );
		
		glVertex2i( 0, 0 );

		
		glTexCoord2f( 1, 0 );
		
		glVertex2i( 4, 0 );

		
		glTexCoord2f( 1, 1 );
		
		glVertex2i( 4, 4 );

		
		glTexCoord2f(0, 1);
		
		glVertex2i( 0, 4 );
	      glEnd( );


	glLoadIdentity();
	glTranslated( AI_position.x/80-122/2+640-4,-AI_position.y/80+122/2+480-64 , 0 );
	glBindTexture( GL_TEXTURE_2D, AI_icon.GetTexture() );

	      glBegin( GL_QUADS );
	        
	    glTexCoord2f( 0, 0 );
		
		glVertex2i( 0, 0 );

		glTexCoord2f( 1, 0 );
	
		glVertex2i( 4, 0 );

	
		glTexCoord2f( 1, 1 );
	
		glVertex2i( 4, 4 );


		glTexCoord2f(0, 1);
	
		glVertex2i( 0, 4 );
	      glEnd( );
glDisable(GL_BLEND);             // Turn Blending off
 glColor4f(1.0f,1.0f,1.0f,1);      
 glMatrixMode( GL_PROJECTION );
   
    glPopMatrix( );

 
    glMatrixMode( GL_MODELVIEW );

    glPopMatrix( );

  
    glEnable( GL_DEPTH_TEST );	

	
};
