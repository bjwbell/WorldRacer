     #ifndef Graphics
       #define Graphics
          #include <SDL/SDL.h>
          #include <GL/gl.h>
          #include <GL/glu.h>
          #include <GL/glext.h>
          #define GL_COMBINE_ARB						0x8570
          #define GL_RGB_SCALE_ARB					0x8573
          #include "Texture.h"
    #endif
	      #ifndef Functions
    #define Functions
    #include "Functions.h"
  #endif
class quad{
		public:
			VERTEX getVertex1();
			VERTEX getVertex2();
			VERTEX getVertex3();
			VERTEX getVertex4();
			VERTEX getVertex(int num);
			bool setVertex1(float x, float y, float z);
			bool setVertex2(float x, float y, float z);
			bool setVertex3(float x, float y, float z);
			bool setVertex4(float x, float y, float z);
			bool setVertex(int num,float x, float y, float k);
	bool setTexture(char* file_name);
			GLuint getTexture();
		bool setX(int X);
		int getX();
		private:
			VERTEX vertex[4];
			texture Texture1;
			int x;
	};
