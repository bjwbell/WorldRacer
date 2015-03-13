
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


class terrain_reflection_map{
	public:
		terrain_reflection_map();
		float GetReflectionTransparency(int x,int y);
		void SetMapFile(char* file);
		void BuildReflectionMap();
	private:
		char* map_file;
		float* map_reflection;
		int MAP_SIZE;
	
	
	
	
};
