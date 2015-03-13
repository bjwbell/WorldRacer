#include "../include/track_selection.h"
void track_selection::Init(screen_dimension var_screen){
	TextDisplay.BuildFont();
	End_Selecting=false;
	screen=var_screen;
	num_tracks=2;
	selected_track=0;
};
int track_selection::Get_Selected_Track(){
	if(End_Selecting==true){
		End_Selecting=false;
		return selected_track;
	}else{
		return -1;
	};
};

void track_selection::Render(){
	
	glClearColor(0,0,0,0);
	glColor4f(1,1,1,1);
	TextDisplay.glPrint(screen.width/2-14*10/2,screen.height-15,"Select a track");
	
		string Directory;
	char* Xstring;
	int c=1;
	int t2=1;
	for(int i=0;i<=num_tracks;i++){
		if(selected_track==i){
			glColor3f(0,0,1);	
		}
		Xstring=ecvt(i+1,c,&c,&t2);
		
		char* dest=(char*)malloc(7*sizeof(char));
		strcpy(dest,"Track ");
		dest=strcat(dest, Xstring);
		TextDisplay.glPrint(screen.width/2-6*10/2,screen.height/2-i*20,dest);	
		glColor3f(1,1,1);		
	}
	glColor3f(1,1,1);
	
	/*if(selected_track==0){
		glColor3f(0,0,1);	
	}
	TextDisplay.glPrint(screen.width/2-6*10/2,screen.height/2+20,"Track1");
	
	glColor3f(1,1,1);
	if(selected_track==1){
		glColor3f(0,0,1);		
	}
	TextDisplay.glPrint(screen.width/2-6*10/2,screen.height/2-20,"Track2");	
	glColor3f(1,1,1);*/
};
void track_selection::key_input(SDL_Event Event){
	

		if(Event.type==SDL_KEYUP){
			
			if(Event.key.keysym.sym==SDLK_UP){
				if(selected_track>0){
					selected_track--;
				}
			}
		
			if(Event.key.keysym.sym==SDLK_DOWN){
				if(selected_track<num_tracks){
					selected_track++;
				};
			
			}
			
			
		}

	
	


		
	
	if(Event.key.keysym.sym==SDLK_RETURN){

		if(Event.type=SDL_KEYUP){
			End_Selecting=true;
			

		}
		
	};	
		
	
};
