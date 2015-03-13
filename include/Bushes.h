#include "../include/Bush.h"
class bushes{
	public:
		void Init(terrain* var_Terrain);
		bool CreateBushes(char* var_map_file);
		void Render();
		void SetRadius(float var_Radius);
	private:
		SDL_Surface* Bush_Map;
		int num_bushes;
		float Radius;
		vector<bush*>Bushes;
		char* map_file;
		terrain* Terrain;
};
