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
#include <vector>
     #ifndef Functions
    #define Functions
    #include "Functions.h"
  #endif

 #ifndef TERRAIN
    #define TERRAIN
    #include "../include/Terrain.h"
  #endif
class path{	
	public:
		bool PathFile(char* file);
		vector<phy_vector> GetPath();
		//bool Set_Terrain(terrain* par_terrain);
		phy_vector GetPosition();
		bool GotoNextPosition();
		int GetCurrentNodeNumber();
		phy_vector GetPosition(int node_number);
		int GetNumNodes();
		path();
	private:
		char* path_file;
		vector<phy_vector>Path;
		bool ReadPath();
		terrain* Terrain;
		int current_node;
		int num_nodes;
};
