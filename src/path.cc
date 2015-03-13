#include "../include/path.h"









bool path::PathFile(char* file){
    current_node=0;
	num_nodes=0;
	path_file=file;
	Path.clear();
	return ReadPath(); 
	
};

vector<phy_vector> path::GetPath(){
	return Path;
};

/*bool path::Set_Terrain(terrain* par_terrain){
	if(par_terrain!=NULL){		Terrain=par_terrain;
		return true;
	}else{
		return false;
	}
};*/

phy_vector path::GetPosition(){
	if(-1==current_node){
		cout<<"Path not set so returning 0,0 for position"<<endl;
		phy_vector z;
		z.i=0;
		z.j=0;
		z.k=0;
		return z;
	}else{
		return Path[current_node];
	}
};



bool path::GotoNextPosition(){
	
	if(num_nodes>current_node+1){
		current_node++;
		return true;
	}else{
		current_node=0;
		cout<<"Can't go to next position in path"<<endl;
		return false;
	}
}

int path::GetCurrentNodeNumber(){
	return current_node;
};
int path::GetNumNodes(){
	return num_nodes;
};
phy_vector path::GetPosition(int node_num){
	return Path[node_num];
};
bool path::ReadPath(){
	
	
	 if(path_file==NULL||path_file==""){
		 return false;
	 }else{
										
	float	x,y;									
	FILE	*filein;									// Filename To Open
	char	oneline[255];								// Holds One Line Of Text (255 Chars Max)
	phy_vector Vector;
	filein = fopen(path_file, "rt");							// Opens The File For Reading Text In Translated Mode
    if(!filein) {
        printf("failed to open file: %s\n", path_file);
        exit(0);
    }
														
	readstr(filein,oneline);							
	
	
	
	float t;
	while(sscanf(oneline, "EndFile %f",&t)==0)								
	{
							
			num_nodes++;
			sscanf(oneline, "%f %f", &x, &y);
			
			Vector.i=x;
			Vector.k=y;
			Path.push_back(Vector);
			readstr(filein,oneline);// Reads In The Next Line Of Text	
	}
	if(num_nodes==0){
		Vector.i=0;
		Vector.k=0;
		Path.push_back(Vector);
		cout<<"Error No nodes in path file"<<endl;
	};
	fclose(filein);	


			return true;
	 }
};
path::path(){
		current_node=0;
		num_nodes=0;
	};
