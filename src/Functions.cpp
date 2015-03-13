/***************************************************************************
                          Functions.cpp  -  description
                             -------------------
    begin                : Sat Jul 6 2002
    copyright            : (C) 2002 by Bryan Bell
    email                : Bryan@localhost.localdomain
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */



// #include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <iostream.h>
#include <stdlib.h>
#include "../include/Functions.h"
#include <math.h>

vector3 normal_vector(vector3 Vector1,vector3 Vector2){
	vector3 normal;
	normal.x=Vector1.y*Vector2.z-Vector1.z*Vector2.y;//A
	normal.y=-(Vector1.x*Vector2.z-Vector1.z*Vector2.x);//B
	normal.z=Vector1.x*Vector2.y-Vector1.y*Vector2.x;//C
	return normal;
};
vector3 unit_normal_vector(vector3 Vector1,vector3 Vector2){
	vector3 normal=normal_vector(Vector1,Vector2);
	vector3 unit_normal;
	float mag=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
	unit_normal.x=normal.x/mag;
	unit_normal.y=normal.y/mag;
	unit_normal.z=normal.z/mag;
	return unit_normal;
};

plane FindClipPlane(vector3 Vector[3]){
	vector3 PlaneVector1;//vector in the plane;
	vector3 PlaneVector2;//vector in the plane;
	PlaneVector1.x=Vector[2].x-Vector[1].x;
	PlaneVector1.y=Vector[2].y-Vector[1].y;
	PlaneVector1.z=Vector[2].z-Vector[1].z;
	PlaneVector2.x=Vector[3].x-Vector[1].x;
	PlaneVector2.y=Vector[3].y-Vector[1].y;
	PlaneVector2.z=Vector[3].z-Vector[1].z;	
	vector3 normal;//normal vector to the plane;
	normal=normal_vector(PlaneVector1,PlaneVector2);
	/*normal.x=PlaneVector1.y*PlaneVector2.z-PlaneVector1.z*PlaneVector2.y;//A
	normal.y=-(PlaneVector1.x*PlaneVector2.z-PlaneVector1.z*PlaneVector2.x);//B
	normal.z=PlaneVector1.x*PlaneVector2.y-PlaneVector1.y*PlaneVector2.x;//C*/
	point Point;//Point in plane;
	Point.x=Vector[1].x;
	Point.y=Vector[1].y;
	Point.z=Vector[1].z;
	float D=-(Point.x*normal.x+Point.y*normal.y+Point.z*normal.z);
	
	
	plane Plane;
	Plane.A=normal.x;
	Plane.B=normal.y;
	Plane.C=normal.z;
	Plane.D=D;
	return Plane;
	
};





void UnitVector(vector3& vector){
	vector3& v=vector;
	if((v.x*v.x+v.y*v.y+v.z*v.z)>1){
		float mag=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);

		v.x=v.x/mag;
		v.y=v.y/mag;
		v.z=v.z/mag;
	}
};
void UnitVector(vector2& vector){
	vector2& v=vector;
	if((v.x*v.x+v.y*v.y)>1){
		float mag=sqrt(v.x*v.x+v.y*v.y);

		v.x=v.x/mag;
		v.y=v.y/mag;
		
	}
};


float find_min_distance_between_points_through_line(phy_vector node1,phy_vector node2,phy_vector Point){
	float a;
	if(node2.i-node1.i==0){
		a=pow(10,100);
	}else{
		a=(node2.k-node1.k)/(node2.k-node1.k); //y=a*x+b
	}
	float b=node1.k-a*node1.i;//b=y1-a*x1 rearraning y1=a*x1+b
	float x=(a*(Point.i+b)+Point.k)/(a*a+1); //creating a distance function and setting the derivative to zero we get the min x
	//float min_distance_x=Point.x-x;
	
	//float min_distance_y=Point.y-(a*x+b);
	float min_distance=sqrt(pow((Point.i-x),2)+pow(Point.k-(a*x+b),2));
	
	if((x<=node1.i&&x>=node2.i)||(x>=node1.i&&x<=node2.i)){
		return min_distance;
	}else{
		float d1=sqrt(pow((Point.i-node1.i),2)+pow((Point.k-node1.k),2));
		float d2=sqrt(pow((Point.i-node2.i),2)+pow((Point.k-node2.k),2));
		if(d1<d2){
			return d1;
		}else{
			return d2;
		}
		
			
	}
};





void readstr(FILE *f,char *string)							// Reads A String From File (f)
{
	  do										// Do This
      {
		    fgets(string, 255, f);							// Gets A String Of 255 Chars Max From f (File)
    } while ((string[0] == '/') || (string[0] == '\n'));				// Until End Of Line Is Reached
    return;										// Return
}

void SetFogCoord(float depth, float height,float fogdensity)
{
	// This function takes the depth of the fog, as well as the height
	// of the current vertex.  If the height is greater than the depth, there
	// is no fog applied to it (0), but if it's below the depth, then we
	// calculate the fog value that should be applied to it.  Since the higher
	// the number passed into glFogCoordfEXT() produces more fog, we need to
	// subtract the depth from the height, then negate that value to switch
	// the ratio from 0 to the depth around.  Otherwise it would have more
	// fog on the top of the fog volume than the bottom of it.

	float fogY = 0;
	//fogdensity=0.7;
	// Check if the height of this vertex is greater than the depth (needs no fog)
	if(height > depth)
		fogY = 0;
	// Otherwise, calculate the fog depth for the current vertex
	else
		fogY = -(height - depth)*fogdensity;

	// Assign the fog coordinate for this vertex using our extension function pointer
	glFogCoordfEXT(fogY);
}
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }

}
bool  GetRGB(SDL_Surface *surface,int x,int y, Uint8 *r,Uint8 *g, Uint8 *b){
  SDL_LockSurface (surface);
	//Uint32 *pixels;
	//pixels = (Uint32 *) surface->pixels;
	//	Uint32 pixel = pixels[0];

Uint32 pixel=getpixel(surface,x,y);
   		SDL_UnlockSurface (surface);
	//	*g = pixel >> 8;
	//	*b = pixel >> 0;
	//	*r = pixel >> 16;    j
//int t;
//t=(int)*g;    j
//cout<<t<<endl;
  SDL_GetRGB(pixel, surface->format,r, g, b);
  return true;
};
int getHeight(SDL_Surface *surface,int x,int y){
      Uint8 r,g,b;
      GetRGB(surface,x,y,&r,&g,&b);
    return sqrt(r*r+b*b+g*g);
};
 void SetVertexColor(SDL_Surface* surface, int x, int y)		// This Sets The Color Value For A Particular Index
{								// Depending On The Height Index
  	
	 Uint8 r,g,b;
	
	
    GetRGB(surface,x,y,&r,&g,&b);

 // float fColor = -0.15f + getHeight(surface,x,y) / 256.0f;

	// Assign This Blue Shade To The Current Vertex
  float red,green,blue;
  //cout<<(int)b<<endl;
  red=r;
  green=g;
  blue=b;
  red=red/256;
  blue=blue/256;
  green=green/256;
 // cout<<blue<<endl;
  glColor3f(red, green, blue );
}

  bool RenderTerrian(char* file_Map,char* file_Color){
   	SDL_Surface* surface=SDL_LoadBMP(file_Map);
  	
SDL_Surface* color_surface=SDL_LoadBMP(file_Color);
//cout<<color_surface<<endl;
int Size_X=surface->w;
   int Size_Y=surface->h;
	  int  MAP_SIZE=Size_Y;
	int X = 0, Y = 0;						// Create some variables to walk the array with.
	int x, y, z;							// Create some variables for readability
	float fColor = 0.0f;					// Create a variable to hold our color of the polygon

	 int STEP_SIZE=3;

	glBegin( GL_QUADS );					// Render Quads

	// Next we actually need to draw the terrain from the height map.
	// To do that, we just walk the array of height data and pluck out
	// some heights to plot our points.  If we could see this happening,
	// it would draw the columns first (Y), then draw the rows.
	// Notice that we have a STEP_SIZE.  This determines how defined our
	// height map is.  The higher the STEP_SIZE, the more blocky the terrain
	// looks, while the lower it gets, the more rounded it becomes.
	// If we set STEP_SIZE = 1 it would create a vertex for every pixel in the height map.
	// I chose 16 as a decent size.  Anything too much less gets to be insane and slow.
	// Of course, you can increase the number when you get lighting in.
	// Then vertex lighting would cover up the blocky shape.  Instead of lighting,
	// we just put a color value associated with every poly to simplify the tutorial.
	// The higher the polygon, the brighter the color is.

	for ( X = 0; X < MAP_SIZE; X += STEP_SIZE )
		for ( Y = 0; Y < MAP_SIZE; Y += STEP_SIZE )
		{
			// Get the (X, Y, Z) value for the bottom left vertex
			x = X;
			y = getHeight(surface, X, Y );
			z = Y;

			// Set the color value of the current vertice
			SetVertexColor(color_surface, x, z);

			glVertex3i(x, y, z);			// Send this vertex to OpenGL to be rendered (integer points are faster)

			// Get the (X, Y, Z) value for the top left vertex
			x = X;
			y = getHeight(surface, X, Y + STEP_SIZE );
			z = Y + STEP_SIZE ;							
			
			// Set the color value of the current vertex
			SetVertexColor(color_surface, x, z);

			glVertex3i(x, y, z);			// Send this vertex to OpenGL to be rendered

			// Get the (X, Y, Z) value for the top right vertex		
			x = X + STEP_SIZE;
			y =getHeight(surface, X + STEP_SIZE, Y + STEP_SIZE );
			z = Y + STEP_SIZE ;

			// Set the color value of the current vertex
			SetVertexColor(color_surface, x, z);
			
			glVertex3i(x, y, z);			// Send this vertex to OpenGL to be rendered

			// Get the (X, Y, Z) value for the bottom right vertex
			x = X + STEP_SIZE;
			y = getHeight(surface, X + STEP_SIZE, Y );
			z = Y;

			// Set the color value of the current vertice
			SetVertexColor(color_surface, x, z);

			glVertex3i(x, y, z);			// Send this vertex to OpenGL to be rendered
		}
	glEnd();
				
   SDL_FreeSurface(surface);
   SDL_FreeSurface(color_surface);
 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);			// Reset The Color


 };

phy_vector CreateNormal(phy_vector vector1,phy_vector vector2){
      phy_vector Normal;
      Normal.j=1;
      if(vector1.i!=0){
        Normal.i=-vector1.j/vector1.i;

      }else{
        Normal.i=1;
        Normal.j=-vector1.i/vector1.j;
      }
      if(vector1.i!=0&&vector2.k!=0){
          //cout<<"Test2"<<endl;
          Normal.k=vector1.j*vector2.i/(vector1.i*vector2.k)-vector2.j/vector2.k;
      }
      if(vector2.i=0&&vector2.k!=0&&vector1.j!=0){
        Normal.k=vector2.j*vector1.i/(vector1.j*vector2.k)-vector2.i/vector2.k;
      }
      if(vector2.k=0){
        cout<<"Error in normal vector creation"<<endl;
      };
     // if(vector2.i=0&&vector2.k==0){
      //};
      float Magnitude=sqrt(Normal.i*Normal.i+Normal.j*Normal.j+Normal.k*Normal.k);
      Normal.i=Normal.i/Magnitude;
      Normal.j=Normal.j/Magnitude;
      Normal.k=Normal.k/Magnitude;
      return Normal;
};
phy_vector NormalVector(phy_vector v1,phy_vector v2){
	phy_vector Vn;
	Vn.i=(v1.j*v2.k-v1.k*v2.j);
	Vn.j=-(v1.i*v2.k-v1.k*v2.i);
	Vn.k=(v1.i*v2.j-v1.j*v2.i);
	return Vn;
};
phy_vector FindPlaneSlope(point Point1,phy_vector Vector1,phy_vector Vector2){
	phy_vector slope;
	phy_vector normal;
	normal=CreateNormal(Vector1,Vector2);
	
	slope.i=-normal.i/normal.j;
	slope.k=-normal.k/normal.j;
	return slope;
	//float =normal.i*point.x+normal.j*point.y+normal.k*point.k;
};
phy_vector FindPlaneGradiant(point Point1,phy_vector Vector1,phy_vector Vector2){
	phy_vector gradiant;
	phy_vector normal;
	normal=CreateNormal(Vector1,Vector2);
	gradiant.j=0;
	gradiant.i=-normal.i/normal.j;//only x and z componets because the gradiant lives in the domain 
	gradiant.k=-normal.k/normal.j;// taken from the eqation a*x+b*y+c*z=k function for z, z=k/c-a/c*-b/c*y derivative -a/c*J+-b/c*K 
	return gradiant;
};

float FindDirectionalDerivative(phy_vector Gradiant,phy_vector Direction){
	if(Direction.j!=0||Direction.i==0&&Direction.k==0){
		cout<<"Error in finding Directional Derivative "<<endl;
		return 0;
	}
	float mag=sqrt(Direction.i*Direction.i+Direction.k*Direction.k);
	phy_vector unit_vector;
	unit_vector.i=Direction.i/mag;
	unit_vector.k=Direction.i/mag;
	unit_vector.j=0;
	return Dot_Product(Gradiant,unit_vector);
};


float Dot_Product(phy_vector v1,phy_vector v2){
	return v1.i*v2.i+v1.j*v2.j+v1.k*v2.k;
};






/*phy_vector FindSlope(point Point1,phy_vector Vector1,phy_vector Vector2){
	phy_vector slope;
	phy_vector normal;
	normal=CreateNormal(Vector1,Vector2);
	
	slope.i=-normal.i/normal.j;
	slope.k=-normal.k/normal.j;
	return slope;
	//float =normal.i*point.x+normal.j*point.y+normal.k*point.k;
};*/
float FindForceInDirectionOfSlope(phy_vector Slope,float m){
	float g=9.8;
	//Ff=mg*cos(theta)*u;
	//Ff=mg*1/sqrt(1+slope*slope)*u
	//Fx=mg*sine(theta)
	//sine(theta)=slope/sqrt(1+slope^2);
	
	float slope=sqrt(Slope.i*Slope.i+Slope.k*Slope.k);
	
	float Fx=-m*g*(slope/sqrt(1+slope*slope));//negative to flip the coord system
	
	return Fx;
	
};

float FindForceNormalToSlope(phy_vector Slope,float m){

	float g=9.8;
	//n=m*g*cos(theta)=m*g*1/sqrt(1+slope^2);
	float slope=sqrt(Slope.i*Slope.i+Slope.k*Slope.k);
	
	float n=m*g*(1/sqrt(1+slope*slope));
	return n;
};
/*float FindForceInDirectionOfSlope(phy_vector Slope,float m,float u){
	float F=FindForceInDirectionOfSlope(Slope,m);
	float n=FindForceNormalToSlope(Slope,m);
	if(n*u>F){//if the Friction is greater then the force then return 0
		return 0;
	}else{
		return F-n*u;
	}
};*/
phy_vector FindForceXYZ(phy_vector Slope,float m){
	phy_vector Force;
	//cout<<"Trst"<<endl;
	float F=FindForceInDirectionOfSlope(Slope,m);
	
	if(Slope.i==0&&Slope.k==0){
		
		Force.i=0;
		Force.k=0;
		Force.j=0;
	}else{
	Force.k=F*Slope.k/(2*sqrt(Slope.k*Slope.k+Slope.i*Slope.i));
	Force.i=F*Slope.i/(2*sqrt(Slope.k*Slope.k+Slope.i*Slope.i));
	Force.j=1/sqrt(2)*F;
	}
	return Force;
};

phy_vector Find_Velocity(phy_vector V,float m,float u,float t){
	if(m==0){
		//cout<<"Error in Find_Velocity m=0"<<endl;
		//cout<<"Returning 0"<<endl;
		phy_vector t;t.i=0;t.k=0;t.j=0;
		
		return t;		
	}
	if(V.i<0.0000001&&V.i>-0.00000001&&V.k<0.0000001&&V.k>-0.00000001&&V.j<0.0000001&&V.j>-0.00000001){
		phy_vector t;t.i=0;t.k=0;t.j=0;
		//cout<<"Returning 0"<<endl;
		return t;
	}
	float force=9.8*m*u;
	//float delta_v=acc*t;

	float cos_theta=V.i/sqrt((V.i*V.i+V.k*V.k));
	float sin_theta=V.k/sqrt((V.i*V.i+V.k*V.k));
	if(cos_theta>1.1||cos_theta<-1.1||sin_theta>1.1||sin_theta<-1.1){
		cout<<"Round of error in Find_Force_Friction"<<endl;
		cout<<"V i "<<V.i<<endl;
		phy_vector t;t.i=0;t.k=0;t.j=V.j;

		return t;
	}
	phy_vector f;
	
	f.i=(force*cos_theta*t);
	f.k=(force*sin_theta*t);
	phy_vector a;
	a.i=f.i/m;
	a.k=f.k/m;
	phy_vector delta_v;
	delta_v.i=a.i*t;
	delta_v.k=a.k*t;
	if(V.i<0){
		V.i=V.i-delta_v.i;
		if(V.i>0){
			V.i=0;
		}
	}else{
		V.i=V.i-delta_v.i;
		if(V.i<0){
			V.i=0;
		}
	}
	if(V.k<0){
		V.k=V.k-delta_v.k;
		if(V.k>0){
			V.k=0;
		}	
	}else{
		V.k=V.k-delta_v.k;
		if(V.k<0){
			V.k=0;
		}	
	}

	return V;
	
};


phy_vector Apply_Friction(phy_vector V,float m,float u,float time){
	if(m==0){
		//cout<<"Error in Find_Velocity m=0"<<endl;
		//cout<<"Returning 0"<<endl;
		phy_vector t;t.i=0;t.k=0;t.j=0;
		
		return t;		
	}
	if(V.i<0.0000001&&V.i>-0.00000001&&V.k<0.0000001&&V.k>-0.00000001&&V.j<0.0000001&&V.j>-0.00000001){
		phy_vector t;t.i=0;t.k=0;t.j=0;
		//cout<<"Returning a zero"<<endl;
		return t;
	}
	
if((V.i*V.i+V.k*V.k)==0){
		phy_vector t;t.i=0;t.k=0;t.j=0;
		//cout<<"Returning a zero"<<endl;
		return t;
	}
if((V.i*V.i+V.j*V.j)==0){
		phy_vector t;t.i=0;t.k=0;t.j=0;
		//cout<<"Returning a zero"<<endl;
		return t;
	}

	float cos_theta=V.i/sqrt((V.i*V.i+V.k*V.k));
	float sin_theta=V.k/sqrt((V.i*V.i+V.k*V.k));
	if(cos_theta>1.1||cos_theta<-1.1||sin_theta>1.1||sin_theta<-1.1){
		//cout<<"Round of error in Find_Force_Friction"<<endl;
		//cout<<"V i "<<V.i<<endl;
		phy_vector t;t.i=0;t.k=0;t.j=V.j;

		return t;
	}
	phy_vector force_friction;
	float force;
	force=9.8*m*u;
	force_friction.i=cos_theta*force;
	force_friction.k=sin_theta*force;
	phy_vector acceleration;
	acceleration.i=force_friction.i/m;
	acceleration.k=force_friction.k/m;
	phy_vector delta_v;
	delta_v.i=acceleration.i*time;
	delta_v.k=acceleration.k*time;
	if(V.i<0){
		V.i=V.i-delta_v.i;
		if(V.i>0){
			V.i=0;
		}
	}else{
		V.i=V.i-delta_v.i;
		if(V.i<0){
			V.i=0;
		}
	}
	if(V.k<0){
		V.k=V.k-delta_v.k;
		if(V.k>0){
			V.k=0;
		}	
	}else{
		V.k=V.k-delta_v.k;
		if(V.k<0){
			V.k=0;
		}	
	}

	
	if((V.i*V.i+V.j*V.j)==0){
		phy_vector t;t.i=0;t.k=0;t.j=0;
		//cout<<"Returning a zero"<<endl;
		return t;
	}
	cos_theta=V.i/sqrt((V.i*V.i+V.j*V.j));
	sin_theta=V.j/sqrt((V.i*V.i+V.j*V.j));
	
	if(cos_theta>1.1||cos_theta<-1.1||sin_theta>1.1||sin_theta<-1.1){
		cout<<"Round of error in Find_Force_Friction"<<endl;
		cout<<"V i "<<V.i<<endl;
		phy_vector t;t.i=0;t.k=0;t.j=V.j;

		return t;
	}
	//phy_vector force_friction;
	force=9.8*m*u;
	force_friction.i=cos_theta*force;
	force_friction.j=sin_theta*force;
	
	acceleration.i=force_friction.i/m;
	acceleration.j=force_friction.j/m;
	
	delta_v.i=acceleration.i*time;
	delta_v.j=acceleration.j*time;
	if(V.j<0){
		V.j=V.j-delta_v.j;
		if(V.j>0){
			V.j=0;
		}
	}else{
		V.j=V.j-delta_v.j;
		if(V.j<0){
			V.j=0;
		}
	}
	
	return V;
	
	
};










void CreateSkyBox(float x, float y, float z, float width, float height, float length,texture Texture1,texture Texture2,texture Texture3,texture Texture4,texture Texture5,texture Texture6)
{
	// Turn on texture mapping if it's not already
	glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
glActiveTextureARB(GL_TEXTURE0_ARB);
	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, Texture1.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// This centers the sky box around (x, y, z)
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the BACK Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z);

	glEnd();

	// Bind the FRONT texture of the sky map to the FRONT side of the box
	glBindTexture(GL_TEXTURE_2D, Texture2.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the FRONT Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z + length);
	glEnd();

	// Bind the BOTTOM texture of the sky map to the BOTTOM side of the box
	glBindTexture(GL_TEXTURE_2D, Texture3.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the BOTTOM Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();

	// Bind the TOP texture of the sky map to the TOP side of the box
	glBindTexture(GL_TEXTURE_2D, Texture4.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the TOP Side
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);

	glEnd();

	// Bind the LEFT texture of the sky map to the LEFT side of the box
	glBindTexture(GL_TEXTURE_2D, Texture5.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the LEFT Side
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);

	glEnd();

	// Bind the RIGHT texture of the sky map to the RIGHT side of the box
	glBindTexture(GL_TEXTURE_2D, Texture6.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);

		// Assign the texture coordinates and vertices for the RIGHT Side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,	z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,	z);
	glEnd();
}
void RenderSky(texture* Sky, float x,float y ,float z,float width,float length){

		glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
glActiveTextureARB(GL_TEXTURE0_ARB);
	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, Sky->GetTexture());
	
		// Start drawing the side as a QUAD
	glBegin(GL_QUADS);
		
		
		// Assign the texture coordinates and vertices for the TOP Side
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y , z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y , z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y ,	z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y ,	z);

	glEnd();
}

