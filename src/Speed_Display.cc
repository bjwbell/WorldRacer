#include "../include/Speed_Display.h"
 void speed_display::Init(){
//	Display_Text.Init();
	Display_Text.BuildFont();
	speed=0;
}
void speed_display::SetSpeed(float Speed){
speed=Speed;
}
void speed_display::Display_Speed(){
	

	glColor3f(1,1,1);
	Display_Text.glPrint(200,0,"Speed %7.2f mph",speed);	
};
