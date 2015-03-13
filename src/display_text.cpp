#include "../include/display_text.h"
display_text::~display_text(){

glDeleteLists( base, 256 ); // Delete All 256 Display Lists  
};

GLvoid display_text::BuildFont( GLvoid )
{
    GLuint loop; // Loop variable              
    float cx;    // Holds Our X Character Coord 
    float cy;    // Holds Our Y Character Coord 

    // Creating 256 Display List  
    base  = glGenLists( 256 );
    // Select Our Font Texture  
   Texture.LoadTexture("data/font.tga");
	glBindTexture( GL_TEXTURE_2D, Texture.GetTexture() );

    // Loop Through All 256 Lists  
    for ( loop = 0; loop < 256; loop++ )
        {
	    /* NOTE:
	       BMPs are stored with the top-leftmost pixel being the
	      last byte and the bottom-rightmost pixel being the first
	      byte. So an image that is displayed as
	         1 0
	         0 0
	      is represented data-wise like
	         0 0
	         0 1
	      And because SDL_LoadBMP loads the raw data without
	      translating to how it is thought of when viewed we need
	      to start at the bottom-right corner of the data and work
	      backwards to get everything properly. So the below code has
	      been modified to reflect this. Examine how this is done and
	      how the original tutorial is done to grasp the differences.
	     
	      As a side note BMPs are also stored as BGR instead of RGB
	      and that is why we load the texture using GL_BGR. It's
	      bass-ackwards I know but whattaya gonna do?
	     */

	    // X Position Of Current Character  
	    
		cx = 1 - ( float )( loop % 16 ) / 16.0f;
	    // Y Position Of Current Character  
	    cy = 1 - ( float )( loop / 16 ) / 16.0f;

            // Start Building A List  
	    glNewList( base + ( 255 - loop ), GL_COMPILE );
	      // Use A Quad For Each Character  
	      glBegin( GL_QUADS );
	        // Texture Coord (Bottom Left)  
	        glTexCoord2f( cx - 0.0625, cy );
		// Vertex Coord (Bottom Left)  
		glVertex2i( 0, 0 );

		// Texture Coord (Bottom Right)  
		glTexCoord2f( cx, cy );
		// Vertex Coord (Bottom Right)  
		glVertex2i( 16, 0 );

		// Texture Coord (Top Right)  
		glTexCoord2f( cx, cy - 0.0625f );
		// Vertex Coord (Top Right)  
		glVertex2i( 16, 16 );

		// Texture Coord (Top Left)  
		glTexCoord2f( cx - 0.0625f, cy - 0.0625f);
		// Vertex Coord (Top Left)  
		glVertex2i( 0, 16 );
	      glEnd( );

	      // Move To The Left Of The Character  
	      glTranslated( 11, 0, 0 );
	    glEndList( );
        }

}

// Print our GL text to the screen  
GLvoid display_text::glPrint( float x ,float y,const char *fmt, ... ){
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	char text[256]; // Holds our string 
    va_list ap;     // Pointer to our list of elements 

    // If there's no text, do nothing 
    if ( fmt == NULL )
	return;

    // Parses The String For Variables 
    va_start( ap, fmt );
      // Converts Symbols To Actual Numbers 
      vsprintf( text, fmt, ap );
    va_end( ap );

    
	int set = 1;

    // Select our texture 
    glBindTexture( GL_TEXTURE_2D,Texture.GetTexture() );

    // Disable depth testing 
    glDisable( GL_DEPTH_TEST );

    // Select The Projection Matrix 
    glMatrixMode( GL_PROJECTION );
    // Store The Projection Matrix 
    glPushMatrix( );

    // Reset The Projection Matrix 
    glLoadIdentity( );
    // Set Up An Ortho Screen 
    glOrtho( 0, 640, 0, 480, -1, 1 );

    // Select The Modelview Matrix 
    glMatrixMode( GL_MODELVIEW );
    // Stor the Modelview Matrix 
    glPushMatrix( );
    // Reset The Modelview Matrix 
    glLoadIdentity( );
	 //glColor4f(1.0f,1.0f,1.0f,1);    
	glEnable(GL_BLEND);
	//glBlendFunc(GL_ALPHA,GL_ONE );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // Position The Text (0,0 - Bottom Left) 
    glTranslated( x, y, 0 );

    // Choose The Font Set (0 or 1) 
    glListBase( base - 32 + ( 128 * set ) );

    // Write The Text To The Screen 
    glCallLists( strlen( text ), GL_BYTE,text );

    // Select The Projection Matrix 
    glMatrixMode( GL_PROJECTION );
    // Restore The Old Projection Matrix 
    glPopMatrix( );
	glDisable(GL_BLEND);
    //Select the Modelview Matrix 
    glMatrixMode( GL_MODELVIEW );
    // Restore the Old Projection Matrix 
    glPopMatrix( );

    //Re-enable Depth Testing 
    glEnable( GL_DEPTH_TEST );
	glPopAttrib();
}
