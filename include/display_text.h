    #ifndef Graphics
       #define Graphics
          #include <SDL/SDL.h>
          #include <GL/gl.h>
          #include <GL/glu.h>
          #include <GL/glext.h>
          #include <GL/glx.h>
		  #define GL_COMBINE_ARB						0x8570
          #define GL_RGB_SCALE_ARB					0x8573
          #include "../include/Texture.h"
    #endif


/*GLuint  base;  //Base Display List For The Font Set 
texture FontTexture;
GLvoid KillFont( GLvoid );
GLvoid BuildFont( GLvoid );
GLvoid glPrint( float x,float y,const char *fmt, ... );*/

class display_text{
	public:
	
	void BuildFont( GLvoid );
	GLvoid glPrint( float x,float y,const char *fmt, ... );
	~display_text();
	
	private:
		

		GLuint  base;                  /* Base Display List For The Font           */
		
		GLuint  loop;                  /* Generic Loop Variable                    */
		texture Texture;
		
	
	};
