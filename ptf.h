

#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>


//#include <gtk/gtkgl.h>



//#define GLEW_STATIC
//#include <GL/glew.h>

#include <epoxy/gl.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

//#include <gtk/gtkgl.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

typedef struct _PtfVisuApp                         PtfVisuApp;

typedef struct _PtfVisuWindow                      PtfVisuWindow;



#ifndef __vector_h
#define __vector_h

typedef struct{
        float x;
        float y;
        float z;
}vector;

#endif


#ifndef __colors_h
#define __colors_h

typedef struct{
        float r, g, b, a;
}colors;

#endif




#ifndef __tile_h
#define __tile_h

typedef struct{
        int f;           // g + h
        int g;           // cost from the starting point to here
        int h;           // estimated movement cost till final square
        void* parent;    // parent tile
        colors color;    // color of tile
        colors outline;  // outline color of the tile
        gboolean fill;       // fill tile?
        gboolean dot;        // dot indicating path taken?
        int x, y;        // position
        gboolean walkable;   // code of tile ie: is it walkable? 0 is it not walkable? 1
        int density;     // difficulty level to traverse this tile
                
        // numbers correspond to keypad 1 is bottom left, 9 is top right, etc
        void* t1;
        void* t2;
        void* t3;
        void* t4;
        void* t6;
        void* t7;
        void* t8;
        void* t9;
        gboolean inOpenList;   // true if it belongs to open list, false otherwise
        gboolean inClosedList; // true if it belongs to closed list, false otherwise
        
        float height[9];
        vector normal[9];
}tile;

#endif




//typedef struct _tile                               tile;

//typedef struct _vector                             vector;

//typedef struct _colors                             colors;
