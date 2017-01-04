/*
 *    Resume Pathfinding Visualization
 *    Copyright (C) 2016 Brandon C Tardio
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *    
 *    Contact: BTardio@gmail.com
 *             818 424 6838
 *
 */

#ifndef __PTF_VISU_WINDOW_H
#define __PTF_VISU_WINDOW_H

#include "ptf.h"


// modes to handle user input
#define EDIT_WALKABLE_MODE 1
#define EDIT_DENSITY_MODE 2
#define EDIT_START_END_MODE 3
#define RUN_MODE 0


G_BEGIN_DECLS

#define CDS_AREA_TYPE_WINDOW (ptf_visu_window_get_type ())

G_DECLARE_FINAL_TYPE(PtfVisuWindow, ptf_visu_window, PTF_VISU, WINDOW, GtkApplicationWindow)

GType                   ptf_visu_window_get_type             (void);
PtfVisuWindow          *ptf_visu_window_new                  (GApplication *app);
void                    ptf_visu_window_open                 (PtfVisuWindow *win, GFile *file);
void                    ptf_visu_window_destroy              (PtfVisuWindow *win);
void                    ptf_visu_window_dispose              ( GObject* obj );
void                    ptf_visu_window_finalize             ( GObject* obj );

G_END_DECLS


enum { X_AXIS, Y_AXIS, Z_AXIS, N_AXES };


// lighting stuff
typedef struct{
        float light_ambient[4];
        float light_diffuse[4];
        float light_specular[4];
        float light_position[4];

}aLight;

typedef struct{
        float mat_ambient[4];
        float mat_diffuse[4];
        float mat_specular[4];
        float high_shininess;
}aMaterial;

/* position and color information for each vertex */
/*
struct vertex_info {
  float position[3];
  float color[3];
};
*/


typedef struct {
  
  
}bLight;

typedef struct {
  
  
}bMaterial;


typedef struct {
  
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat w;
  
  GLfloat r;
  GLfloat g;
  GLfloat b;
  GLfloat a;
  
  // normals
  GLfloat nx;
  GLfloat ny;
  GLfloat nz;
  GLfloat nw;
    
} vertex;



struct _PtfVisuWindow
{


  
  
  GtkApplicationWindow parent_instance;
    
  GtkBox* box1;
  
  GtkGLArea* glarea;

  
  aMaterial m;
  aLight l;
  aLight ll;
  
  
  
  gboolean createFractal;
  gboolean pathFound;
  gboolean showOutline;
  
  GLsizei globalwidth, globalheight;
  
  gfloat zoom; // zoom factor controlled by o and p
  
  tile **map;
  int numBlocks;
  int mapWidth;
  int mapHeight;

  

  tile* start;  // = NULL;
  tile* end;    // = NULL;

  gboolean waitingForEnd;

  int currentMode;
  
  
  //GLuint VertexArrayID;
  
  
  
  /* the vertex data is constant */
/*
  struct vertex_info ground_grid_info[] = {
    { {  -1.0f, 0.0f,  0.0f }, { 1.f, 0.f, 0.f } },
    { {   0.0f, 1.0f,  0.0f }, { 0.f, 1.f, 0.f } },
    { {   0.0f, 0.0f, -1.0f }, { 0.f, 0.f, 1.f } },
  };
*/

  GLfloat* vertex_data;
  GLuint* vertex_buffer;
  

  
  guint vertexArrayObject;
  guint prog;
  
  
  
  
  
  guint tick_id;
  gint64 first_frame_time;
  
  /* decomposed rotations */
  double rotation_angles[N_AXES];

  /* model-view-projection matrix */
  float mvp[16];

  /* GL objects */
  //guint vao;
  //guint program;
  guint mvp_location;
  guint position_index;
  guint color_index;
  
  
  
  // VAO's & VBO's
  
  guint pft_vertex_array_object;
  guint pft_vertex_buffer_object;
  
  guint pft_tile_array_object;
  guint pft_tile_buffer_object;

  guint pft_tile_line_array_object;
  guint pft_tile_line_buffer_object;

  guint pft_tile_dot_array_object;
  guint pft_tile_dot_buffer_object;  
  
  //guint pft_vertex_color_buffer_object;
  
  //GLfloat* triangle_vertices;
  //GLfloat* triangle_colors;
  
  guint pft_position_id;
  guint pft_color_id;
  guint pft_normal_id;
  
  guint pft_vertex_shader_id;
  guint pft_fragment_shader_id;
  
  GBytes *pft_vertex_shader_src;
  gpointer *pft_vertex_shader_src_ptr;
  GBytes *pft_fragment_shader_src;
  gpointer *pft_fragment_shader_src_ptr;
  
  guint pft_program_id;
  

  
  // mvp = combined model -> world -> camera -> projection
  //guint pft_modelm_location_id;
  //guint pft_worldm_location_id;
  //guint pft_cameram_location_id;
  //guint pft_projectionm_location_id;
  
  
  guint pft_position_location_id;
  guint pft_color_location_id;
  
  GLfloat* pft_mwcp_array;
  
  // rotation matrix
  gsl_matrix_float* pft_gsl_rotate_matrix;
  guint pft_gsl_rotate_matrix_id;
  
  // scaling matrix
  gsl_matrix_float* pft_gsl_scale_matrix;
  guint pft_gsl_scale_matrix_id;
  
  // translate matrix
  gsl_matrix_float* pft_gsl_translate_matrix;
  guint pft_gsl_translate_matrix_id;
  
  gint64 frametime;
  gfloat rotate_degree;
  
  guint timerid;
  
  vertex* pft_vertices;
  
  vertex* pft_tile_vertices;
  
  vertex* pft_tile_line_vertices;
  
  vertex* pft_tile_dot_vertices;
  
};

struct _PtfVisuWindowClass
{
  
  GtkApplicationWindowClass parent_class_instance;
  
};






#endif // __PTF_VISU_WINDOW_H


