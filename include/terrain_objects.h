#include "../include/Bushes.h"
#include "../include/Track_Marker.h"
class terrain_objects{
	public:
		void Init(terrain* var_Terrain);
		bool CreateObjects(char* var_map_file);
		void Render();
		
		void SetTemplateObject(terrain_object* object);
	private:
		SDL_Surface* Objects_Map;
		int num_objects;
		terrain_object* Object;
		vector<terrain_object*>Objects;
		terrain_object* TemplateObject;
		char* map_file;
		terrain* Terrain;
};
