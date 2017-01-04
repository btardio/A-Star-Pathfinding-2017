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
 *   
 *
 */

#include "ptf.h"
#include "ptf_window.h"
#include "ptf_error.h"

#include <GL/gl.h>
#include <GL/glext.h>






#define CD 1


G_DEFINE_TYPE(PtfVisuWindow, ptf_visu_window, GTK_TYPE_APPLICATION_WINDOW)


/* the vertex data is constant */
/*
static const struct vertex_info vertex_data[] = {
  { {  0.0f,  0.500f, 0.0f }, { 1.f, 0.f, 0.f } },
  { {  0.5f, -0.366f, 0.0f }, { 0.f, 1.f, 0.f } },
  { { -0.5f, -0.366f, 0.0f }, { 0.f, 0.f, 1.f } },
};
*/


static void
rotation_about_y ( gsl_matrix_float* m, gfloat d )
{
  
  gfloat c = cos ( d );
  gfloat s = sin ( d );
  
  gsl_matrix_float_set_identity ( m );
  
  gsl_matrix_float_set ( m, 0, 0, c );
  gsl_matrix_float_set ( m, 0, 2, s );

  gsl_matrix_float_set ( m, 2, 0, -s );
  gsl_matrix_float_set ( m, 2, 2, c );
  
}


gboolean
ptf_visu_window_key_press_event ( GtkWidget *widget, GdkEventKey *event )
{
  PtfVisuWindow* win;
  win = PTF_VISU_WINDOW(widget);
  
/*
  if ( win->area != NULL )
  {
    cds_area_drawing_area_key_press_event ( win->area, event );
  }
*/
    
  
    
    
  return GDK_EVENT_PROPAGATE;
}



gboolean
ptf_visu_window_key_release_event ( GtkWidget *widget, GdkEventKey *event )
{
  PtfVisuWindow* win;
  win = PTF_VISU_WINDOW(widget);
  
  /*
  if ( win->area != NULL )
  {
    ptf_visu_drawing_area_key_release_event ( win->area, event );
  }
  */
  
  return GDK_EVENT_PROPAGATE;
}




static void
draw_triangle (PtfVisuWindow* win)
{
/*
  g_message("draw_triangle");
  
  if (win->prog == 0 || win->vertexArrayObject == 0)
  {
    g_message("win->prog = 0 or win->vertexArrayObject = 0");
    return;
  }

  // load our program
  glUseProgram (win->prog);

  // update the "mvp" matrix we use in the shader
  glUniformMatrix4fv (win->mvp_location, 1, GL_FALSE, &(win->mvp[0]));

  // use the buffers in the VAO
  glBindVertexArray (win->vertexArrayObject);

  // draw the three vertices as a triangle
  glDrawArrays (GL_TRIANGLES, 0, 3);

  // we finished using the buffers and program
  glBindVertexArray (0);
  glUseProgram (0);
  
  */
}


void
render(GtkGLArea *area, GdkGLContext *context, gpointer data){
  
  PtfVisuWindow* win = data;
  
  //g_message("render");

  glClearColor (0.5, 0.5, 0.5, 1.0);
  //glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  if (win->pft_program_id == 0 || win->pft_vertex_array_object == 0)
    return;

  /* load our program */
  glUseProgram ( win->pft_program_id );

  /* update the "mvp" matrix we use in the shader */
  //glUniformMatrix4fv ( win->pft_mwcp_location_id, 1, GL_FALSE, win->pft_mwcp_array );
  glUniformMatrix4fv ( win->pft_gsl_rotate_matrix_id, 1, GL_FALSE, win->pft_gsl_rotate_matrix->data );

  glUniformMatrix4fv ( win->pft_gsl_scale_matrix_id, 1, GL_FALSE, win->pft_gsl_scale_matrix->data );
  
  glUniformMatrix4fv ( win->pft_gsl_translate_matrix_id, 1, GL_FALSE, win->pft_gsl_translate_matrix->data );
  
  // *** Draw Tiles ***
  
  /* use the buffers in the VAO */
  glBindVertexArray ( win->pft_tile_array_object );
  
  /* draw the three vertices as a triangle */
  glDrawArrays (GL_TRIANGLES, 0, win->mapHeight * win->mapWidth * 6);

  /* we finished using the buffers and program */
  glBindVertexArray (0);
  
  // *** Draw Tile Lines ***
  
  /* use the buffers in the VAO */
  glBindVertexArray ( win->pft_tile_line_array_object );
  
  /* draw the three vertices as a triangle */
  glDrawArrays (GL_LINES, 0, win->mapHeight * win->mapWidth * 8);

  /* we finished using the buffers and program */
  glBindVertexArray (0);
  
  
  // *** Draw misc debug ***
  
  /* use the buffers in the VAO */
  glBindVertexArray ( win->pft_vertex_array_object );
  
  /* draw the three vertices as a triangle */
  glDrawArrays (GL_TRIANGLES, 0, 6);

  /* we finished using the buffers and program */
  glBindVertexArray (0);
  



  
  
  glUseProgram (0);

  
  return;
  
  /*
  PtfVisuWindow* win = data;
  
  g_message("render");
  
  glClearColor (0.5, 0.5, 0.5, 1.0);
  glClear (GL_COLOR_BUFFER_BIT);
  
  draw_triangle ( win );
  
  glFlush ();
  
  return TRUE;
  
  */
  
  
  
  //PtfVisuWindow* win = data;

  
  /*
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1.0f, 0.5f, 0.5f);


 
  //glTranslatef(-(float)win->mapWidth / 2.0f, -(float)win->mapHeight / 2.0f, -(win->mapWidth + win->mapHeight));
  
  if( !win->createFractal ){
          int tileName;
          glInitNames();
  
          if( win->start == NULL ){
                  
                  //gluLookAt(win->mapWidth / 2 - win->zoom, 
                  //          win->mapHeight / 2 - win->zoom, 
                  //          win->zoom - 2, 
                  //          win->mapWidth / 2, win->mapHeight / 2,
                  //          0, 
                  //          0,
                  //          0,
                  //          1);
                  
                  //gluLookAt((float)win->mapWidth / 0.75f, (float)win->mapHeight / 0.75f, (win->mapWidth + win->mapHeight) / 3, 0,0,0, 0,0,1);
          }
          else if (win->pathFound){
                  //gluLookAt((float)win->end->x - win->zoom, (float)win->end->y - win->zoom, win->zoom - 2, 
                  //          (float)win->end->x, (float)win->end->y, 0, 
                  //          0,0,1);
          }
          else{
                  //gluLookAt((float)win->start->x - win->zoom, (float)win->start->y - win->zoom, win->zoom - 2, (float)win->start->x,(float)win->start->y,0, 0,0,1);
          }
          glPushMatrix();
          //glRotatef(0, 0, 1, 90.0f);
          for(int i = 0; i < win->mapHeight; i++){
                  for( int j = 0; j < win->mapWidth; j++){
                          tileName = (i * win->mapHeight) + j;
                          glPushName(tileName);
                          //glPushName((int)&win->map[i][j]);
                          glColor3f(win->map[i][j].color.r, 
                                          win->map[i][j].color.g,
                                          win->map[i][j].color.b); 
                          glBegin(GL_TRIANGLES);
                          glNormal3f(0.0f, 0.0f, -1.0f);
                          glVertex3i(win->map[i][j].x , win->map[i][j].y, 0);
                          glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y, 0);
                          glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y + 1, 0);
                          
                          glVertex3i(win->map[i][j].x , win->map[i][j].y, 0);
                          glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y + 1, 0);
                          glVertex3i(win->map[i][j].x,  win->map[i][j].y + 1, 0);
                          glEnd();
                          
                          glPopName();
                          
                          if( win->showOutline){
                                  glColor4f(win->map[i][j].outline.r, win->map[i][j].outline.g, 
                                                  win->map[i][j].outline.b, win->map[i][j].outline.a);
                                  glBegin(GL_LINE_STRIP);
                          
                                  glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.1f, 0);
                                  glVertex3f(win->map[i][j].x + 0.9f, win->map[i][j].y + 0.1f, 0);
                                  glVertex3f(win->map[i][j].x + 0.9f, win->map[i][j].y + 0.9f, 0);
                                  glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.9f, 0);
                                  glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.1f, 0);
                          
                                  glEnd();
                          }
                          
                          
                          if(win->map[i][j].dot){
                                  glPushName(tileName);
                                  glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
                                  glBegin(GL_TRIANGLES);
                                  glNormal3f(0.0f, 0.0f, 1.0f);
                                  glVertex3f(win->map[i][j].x + 0.25f , win->map[i][j].y + 0.25f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.25f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
                          
                                  glVertex3f(win->map[i][j].x + 0.25f, win->map[i][j].y + 0.25f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.25f,  win->map[i][j].y + 0.75f, 0.1f);
                                  
                                  glEnd();
                                  glPopName();
                                  
                          }
                          glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                          
          
                          
                  }
          }
          
  
  
  
  
  
          glPopMatrix();
  
  }
  else{
          int tileName;
          glInitNames();
  
          if( win->start == NULL ){
                  glLoadIdentity();
                  //gluLookAt((float)win->mapWidth / 0.75f, (float)win->mapHeight / 0.75f, (win->mapWidth + win->mapHeight) / 3, 0,0,0, 0,0,1);
                  //gluLookAt(win->mapWidth / 2 - win->zoom, win->mapHeight / 2 - win->zoom, win->zoom - 2, win->mapWidth / 2,win->mapHeight / 2,0, 0,0,1);
          }
          else if (win->pathFound){                    
                  glLoadIdentity();
                  win->l.light_position[0] = (float)win->end->x;
                  win->l.light_position[1] = (float)win->end->y;
                  win->l.light_position[2] = 1.0f;
                  win->l.light_position[3] = 1.0f;
                  glLightfv(GL_LIGHT0, GL_POSITION, win->l.light_position);
                  //gluLookAt((float)win->end->x - win->zoom, (float)win->end->y - win->zoom, win->zoom - 2, (float)win->end->x,(float)win->end->y,0, 0,0,1);
          }
          else{
                  glLoadIdentity();
                  win->l.light_position[0] = (float)win->start->x;
                  win->l.light_position[1] = (float)win->start->y;
                  win->l.light_position[2] = 1.0f;
                  win->l.light_position[3] = 1.0f;
                  glLightfv(GL_LIGHT0, GL_POSITION, win->l.light_position);
                  //glEnable(GL_LIGHT0);
                  //gluLookAt((float)win->start->x - win->zoom, (float)win->start->y - win->zoom, win->zoom - 2, (float)win->start->x,(float)win->start->y,0, 0,0,1);
          }
          glPushMatrix();
          //glRotatef(0, 0, 1, 90.0f);
          for(int i = 0; i < win->mapHeight; i++){
                  for( int j = 0; j < win->mapWidth; j++){
                          tileName = (i * win->mapHeight) + j;
                          glPushName(tileName);
                          //glPushName((int)&win->map[i][j]);
                          glColor3f(win->map[i][j].color.r, 
                                          win->map[i][j].color.g,
                                          win->map[i][j].color.b); 
                          glBegin(GL_TRIANGLES);
                          //glNormal3f(0.0f, 0.0f, 1.0f);
                          
                          
                          */
                          
/*
                          glVertex3i(win->map[i][j].x , win->map[i][j].y, 0);
                          glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y, 0);
                          glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y + 1, 0);
                          
                          glVertex3i(win->map[i][j].x , win->map[i][j].y, 0);
                          glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y + 1, 0);
                          glVertex3i(win->map[i][j].x,  win->map[i][j].y + 1, 0);
*/
/*
                          // 
                          glNormal3f(win->map[i][j].normal[0].x, win->map[i][j].normal[0].y, win->map[i][j].normal[0].z);
                          glVertex3f(win->map[i][j].x, win->map[i][j].y, win->map[i][j].height[0] / CD);
                          glNormal3f(win->map[i][j].normal[1].x, win->map[i][j].normal[1].y, win->map[i][j].normal[1].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y, win->map[i][j].height[1] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[1].x, win->map[i][j].normal[1].y, win->map[i][j].normal[1].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y, win->map[i][j].height[1] / CD);
                          glNormal3f(win->map[i][j].normal[2].x, win->map[i][j].normal[2].y, win->map[i][j].normal[2].z);
                          glVertex3f(win->map[i][j].x + 1.0f, win->map[i][j].y, win->map[i][j].height[2] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[2].x, win->map[i][j].normal[2].y, win->map[i][j].normal[2].z);
                          glVertex3f(win->map[i][j].x + 1.0f, win->map[i][j].y, win->map[i][j].height[2] / CD);
                          glNormal3f(win->map[i][j].normal[5].x, win->map[i][j].normal[5].y, win->map[i][j].normal[5].z);
                          glVertex3f(win->map[i][j].x + 1.0f, win->map[i][j].y + 0.5f, win->map[i][j].height[5] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[5].x, win->map[i][j].normal[5].y, win->map[i][j].normal[5].z);
                          glVertex3f(win->map[i][j].x + 1.0f, win->map[i][j].y + 0.5f, win->map[i][j].height[5] / CD);
                          glNormal3f(win->map[i][j].normal[8].x, win->map[i][j].normal[8].y, win->map[i][j].normal[8].z);
                          glVertex3f(win->map[i][j].x + 1.0f, win->map[i][j].y + 1.0f, win->map[i][j].height[8] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[8].x, win->map[i][j].normal[8].y, win->map[i][j].normal[8].z);
                          glVertex3f(win->map[i][j].x + 1.0f, win->map[i][j].y + 1.0f, win->map[i][j].height[8] / CD);
                          glNormal3f(win->map[i][j].normal[7].x, win->map[i][j].normal[7].y, win->map[i][j].normal[7].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 1.0f, win->map[i][j].height[7] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[7].x, win->map[i][j].normal[7].y, win->map[i][j].normal[7].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 1.0f, win->map[i][j].height[7] / CD);
                          glNormal3f(win->map[i][j].normal[6].x, win->map[i][j].normal[6].y, win->map[i][j].normal[6].z);
                          glVertex3f(win->map[i][j].x, win->map[i][j].y + 1.0f, win->map[i][j].height[6] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[6].x, win->map[i][j].normal[6].y, win->map[i][j].normal[6].z);
                          glVertex3f(win->map[i][j].x, win->map[i][j].y + 1.0f, win->map[i][j].height[6] / CD);
                          glNormal3f(win->map[i][j].normal[3].x, win->map[i][j].normal[3].y, win->map[i][j].normal[3].z);
                          glVertex3f(win->map[i][j].x, win->map[i][j].y + 0.5f, win->map[i][j].height[3] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glNormal3f(win->map[i][j].normal[3].x, win->map[i][j].normal[3].y, win->map[i][j].normal[3].z);
                          glVertex3f(win->map[i][j].x, win->map[i][j].y + 0.5f, win->map[i][j].height[3] / CD);
                          glNormal3f(win->map[i][j].normal[0].x, win->map[i][j].normal[0].y, win->map[i][j].normal[0].z);
                          glVertex3f(win->map[i][j].x, win->map[i][j].y, win->map[i][j].height[0] / CD);
                          glNormal3f(win->map[i][j].normal[4].x, win->map[i][j].normal[4].y, win->map[i][j].normal[4].z);
                          glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.5f, win->map[i][j].height[4] / CD);
                          
                          glEnd();
                          
                          glPopName();
                          glDisable(GL_LIGHTING);
                          if(win->showOutline){
                          
                                  glColor4f(win->map[i][j].outline.r, win->map[i][j].outline.g, 
                                                  win->map[i][j].outline.b, win->map[i][j].outline.a);
                                  glBegin(GL_LINE_STRIP);
                          
                          
                          //glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.1f, 0);
                          //glVertex3f(win->map[i][j].x + 0.9f, win->map[i][j].y + 0.1f, 0);
                          //glVertex3f(win->map[i][j].x + 0.9f, win->map[i][j].y + 0.9f, 0);
                          //glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.9f, 0);
                          //glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.1f, 0);
                          
                          
                                  glVertex3f(win->map[i][j].x + 0.01f, win->map[i][j].y + 0.01f, win->map[i][j].height[0] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.01f, win->map[i][j].height[1] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.99f, win->map[i][j].y + 0.01f, win->map[i][j].height[2] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.99f, win->map[i][j].y + 0.5f, win->map[i][j].height[5] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.99f, win->map[i][j].y + 0.99f, win->map[i][j].height[8] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.5f, win->map[i][j].y + 0.99f, win->map[i][j].height[7] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.01f, win->map[i][j].y + 0.99f, win->map[i][j].height[6] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.01f, win->map[i][j].y + 0.5f, win->map[i][j].height[3] + 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.01f, win->map[i][j].y + 0.01f, win->map[i][j].height[0] + 0.1f);
                                  
                                  glEnd();
                          }
                          
                          glEnable(GL_LIGHTING);
*/
                          /*
                          if(win->map[i][j].dot){
                                  glPushName(tileName);
                                  glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
                                  glBegin(GL_TRIANGLES);
                                  glNormal3f(0.0f, 0.0f, -1.0f);
                                  glVertex3f(win->map[i][j].x + 0.25f , win->map[i][j].y + 0.25f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.25f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
                          
                                  glVertex3f(win->map[i][j].x + 0.25f, win->map[i][j].y + 0.25f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
                                  glVertex3f(win->map[i][j].x + 0.25f,  win->map[i][j].y + 0.75f, 0.1f);
                                  
                                  glEnd();
                                  glPopName();
                                  
                          }*/
/*
                          glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                          
          
                          
                  }
          
          }
          
  
  
  
  
  glPopMatrix();
  
  }
  
  */

}










static void
on_finalize ( GtkGLArea* area, gpointer data ) {
  
  PtfVisuWindow* win = data;
  
  g_message ( "un_realize" );
  
  glDeleteVertexArrays ( 1, &win->vertexArrayObject );
  glDeleteProgram (win->prog);
  
  
  
  
}

static void
on_realize ( GtkGLArea *area, gpointer data ) {
  
  PtfVisuWindow* win = data;

  GError *error = NULL; // error value used throughout init, shows up in GL window 
                        // ie: gtk_gl_area_set_error (area, error); don't forget to g_error_free (error);

  g_message ( "realize" );

  // Make this context current
  gtk_gl_area_make_current (area);
  if (gtk_gl_area_get_error (area) != NULL)
    return;
  
  
  
  // 0. Prep MWCP Matrices
  // ^^^^^^^^^^^^^^^^^^^^^
  
/*
  win->pft_mwcp_array = malloc ( sizeof ( GLfloat ) * 16 );
  
  win->pft_mwcp_array[0] = 1.0f; win->pft_mwcp_array[1] = 0.0f; win->pft_mwcp_array[2] = 0.0f; win->pft_mwcp_array[3] = 0.0f;
  win->pft_mwcp_array[4] = 0.0f; win->pft_mwcp_array[5] = 1.0f; win->pft_mwcp_array[6] = 0.0f; win->pft_mwcp_array[7] = 0.0f;
  win->pft_mwcp_array[8] = 0.0f; win->pft_mwcp_array[9] = 0.0f; win->pft_mwcp_array[10] = 1.0f; win->pft_mwcp_array[11] = 0.0f;
  win->pft_mwcp_array[12] = 0.0f; win->pft_mwcp_array[13] = 0.0f; win->pft_mwcp_array[14] = 0.0f; win->pft_mwcp_array[15] = 1.0f;
*/
  

  //********************************
  // rotate, scale, translate matrix
  //********************************
  
  // create rotate matrix

  win->pft_gsl_rotate_matrix = gsl_matrix_float_alloc (4, 4);
  gsl_matrix_float_set_identity ( win->pft_gsl_rotate_matrix );
  gsl_matrix_float_set ( win->pft_gsl_rotate_matrix, 1, 0, 0.1f );
  win->rotate_degree = 0.0f;
  rotation_about_y ( win->pft_gsl_rotate_matrix, win->rotate_degree );
  
  // this is associated with win->pft_mwcp_location_id; 
  // this var initialized later: win->pft_mwcp_location_id = glGetUniformLocation (win->pft_program_id, "MVP");
  
  
  
  // scaling matrix
  win->pft_gsl_scale_matrix = gsl_matrix_float_alloc ( 4, 4 );
  gsl_matrix_float_set_identity ( win->pft_gsl_scale_matrix );
  gsl_matrix_float_set ( win->pft_gsl_scale_matrix, 0, 0, 0.3f );
  gsl_matrix_float_set ( win->pft_gsl_scale_matrix, 1, 1, 0.3f );
  gsl_matrix_float_set ( win->pft_gsl_scale_matrix, 2, 2, 0.3f );
  
  
  // translate matrix
  win->pft_gsl_translate_matrix = gsl_matrix_float_alloc ( 4, 4 );
  gsl_matrix_float_set_identity ( win->pft_gsl_translate_matrix );
  gsl_matrix_float_set ( win->pft_gsl_translate_matrix, 3, 0, -0.75f ); // x
  gsl_matrix_float_set ( win->pft_gsl_translate_matrix, 3, 1, -0.75f ); // y
  gsl_matrix_float_set ( win->pft_gsl_translate_matrix, 3, 2, 0.0f ); // z
  
  
  
  // 1. Prep Vertices
  // ^^^^^^^^^^^^^^^^
  
  win->pft_position_id = 0;
  win->pft_color_id = 1;
  win->pft_normal_id = 2;
  
  
  // ********************
  // Create the map tiles
  // ********************

  int width = 5;
  int height = 5;

  win->currentMode = EDIT_WALKABLE_MODE;
  
  
  win->mapWidth = width;
  win->mapHeight = height;
  
  //win->map = new tile*[height];
  win->map = malloc ( sizeof(tile*) * height );
  win->numBlocks = width * height;

  for( int i = 0; i < height; i++){
    //win->map[i] = new tile[width];
    win->map[i] = malloc ( sizeof( tile ) * width );
  }
  for( int i = 0; i < height; i++){
          //map[i] = new tile[width];
          for( int j = 0; j < width; j++){
                  
                  //win->map[i][j] = (tile*) malloc ( sizeof ( tile ) );
            
                  // all tiles start out 
                  win->map[i][j].walkable = TRUE;   // walkable
                  win->map[i][j].color.r = 0.0f;
                  win->map[i][j].color.g = 1.0f;
                  win->map[i][j].color.b = 0.0f;                               
                  win->map[i][j].color.a = 1.0f;
                  //map[i][j].fill = false;
                  win->map[i][j].density = 0;    // difficulty of 0

                  win->map[i][j].outline.r = 0.0f;
                  win->map[i][j].outline.g = 0.0f;
                  win->map[i][j].outline.b = 0.0f;                             
                  win->map[i][j].outline.a = 1.0f;
                  
                  win->map[i][j].x = j;
                  win->map[i][j].y = i;
                  
                  win->map[i][j].inOpenList = FALSE;
                  win->map[i][j].inClosedList = FALSE;
                  
                  // assign pointers to surrounding nodes
                  win->map[i][j].t1 = ( i-1 >= 0 && j-1 >= 0 ? &win->map[i-1][j-1] : NULL);
                  win->map[i][j].t2 = ( i-1 >= 0 ? &win->map[i-1][j] : NULL);
                  win->map[i][j].t3 = ( i-1 >= 0 && j+1 < width ? &win->map[i-1][j+1] : NULL);
                  win->map[i][j].t4 = ( j-1 >= 0 ? &win->map[i][j-1] : NULL);
                  win->map[i][j].t6 = ( j+1 < width ? &win->map[i][j+1] : NULL);
                  win->map[i][j].t7 = ( i+1 < height && j-1 >= 0 ? &win->map[i+1][j-1] : NULL);
                  win->map[i][j].t8 = ( i+1 < height ? &win->map[i+1][j] : NULL);
                  win->map[i][j].t9 = ( i+1 < height && j+1 < width ? &win->map[i+1][j+1] : NULL);
                  
                  win->map[i][j].f = 0;
                  
                  win->map[i][j].dot = FALSE;
                  
                  for( int w = 0; w < 9; w++){
                          win->map[i][j].normal[w].x = 0.0f;
                          win->map[i][j].normal[w].y = 0.0f;
                          win->map[i][j].normal[w].z = 1.0f;
                  }
          }
          
  }


  // **********************
  // load tiles into buffer
  // **********************
  
  win->pft_tile_vertices = malloc ( sizeof ( vertex ) * (width * height * 6) );
  
  win->pft_tile_line_vertices = malloc ( sizeof ( vertex ) * ( width * height * 8 ) );
  
  // start of path and end of path dot
  win->pft_tile_dot_vertices = malloc ( sizeof ( vertex ) * 2 * 6 );
  
              
              
              
      
              
  // would it be better to have static squares that transform in glsl based on a transform matrix
  // probably....
  // ie: 1 buffer that holds 1 square and drawn repeatedly with a transform
  // would produce better performance, allowing larger number of tiles in a scene
  // but it's a demo program... manipulate the buffer
  
              
  
  //glVertex3f(win->map[i][j].x + 0.25f , win->map[i][j].y + 0.25f, 0.1f);
  win->pft_tile_dot_vertices[0].x = win->map[0][0].x - 2.0f + 0.25f;
  
  //glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.25f, 0.1f);
  win->pft_tile_dot_vertices[0 + 1].x = win->map[0][0].x - 1.0f + 0.75f;
  
  //glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
  win->pft_tile_dot_vertices[0 + 2].x = win->map[0][0].x - 1.0f + 0.75f;
  
  //glVertex3f(win->map[i][j].x + 0.25f, win->map[i][j].y + 0.25f, 0.1f);
  win->pft_tile_dot_vertices[0 + 3].x = win->map[0][0].x - 2.0f + 0.25f;
  
  //glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
  win->pft_tile_dot_vertices[0 + 4].x = win->map[0][0].x - 1.0f + 0.75f;
  
  //glVertex3f(win->map[i][j].x + 0.25f,  win->map[i][j].y + 0.75f, 0.1f);
  win->pft_tile_dot_vertices[0 + 5].x = win->map[0][0].x - 2.0f + 0.25f;
  
  
  for(int i = 0; i < win->mapHeight; i++){
    for( int j = 0; j < win->mapWidth; j++){
      //tileName = (i * win->mapHeight) + j;
      //glPushName(tileName);
      //glPushName((int)&win->map[i][j]);
      
      // 2x2 map
      // i = 0 j = 0  index = 0
      // i = 0 j = 1  index = 6
      // i = 1 j = 0  index = 12
      // i = 1 j = 1  index = 18
      
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].x = win->map[i][j].x;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].y = win->map[i][j].y;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].z = 0;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].r = win->map[i][j].color.r;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].g = win->map[i][j].color.g;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].b = win->map[i][j].color.b;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6].a = win->map[i][j].color.a;
      
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].x = win->map[i][j].x + 1.0f;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].y = win->map[i][j].y;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].z = 0;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].r = win->map[i][j].color.r;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].g = win->map[i][j].color.g;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].b = win->map[i][j].color.b;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 1].a = win->map[i][j].color.a;
      
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].x = win->map[i][j].x + 1.0f;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].y = win->map[i][j].y + 1.0f;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].z = 0;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].r = win->map[i][j].color.r;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].g = win->map[i][j].color.g;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].b = win->map[i][j].color.b;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 2].a = win->map[i][j].color.a;
      
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].x = win->map[i][j].x;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].y = win->map[i][j].y;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].z = 0;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].r = win->map[i][j].color.r;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].g = win->map[i][j].color.g;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].b = win->map[i][j].color.b;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 3].a = win->map[i][j].color.a;
      
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].x = win->map[i][j].x + 1.0f;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].y = win->map[i][j].y + 1.0f;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].z = 0;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].r = win->map[i][j].color.r;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].g = win->map[i][j].color.g;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].b = win->map[i][j].color.b;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 4].a = win->map[i][j].color.a;
      
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].x = win->map[i][j].x;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].y = win->map[i][j].y + 1.0f;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].z = 0;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].r = win->map[i][j].color.r;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].g = win->map[i][j].color.g;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].b = win->map[i][j].color.b;
      win->pft_tile_vertices[(i * win->mapHeight + j) * 6 + 5].a = win->map[i][j].color.a;
      
      // *** tile line vertices ***
      
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].x = win->map[i][j].x + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].y = win->map[i][j].y + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8].a = win->map[i][j].outline.a;
      
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].x = win->map[i][j].x + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].y = win->map[i][j].y + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 1].a = win->map[i][j].outline.a;

      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].x = win->map[i][j].x + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].y = win->map[i][j].y + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 2].a = win->map[i][j].outline.a;      
      
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].x = win->map[i][j].x + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].y = win->map[i][j].y + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 3].a = win->map[i][j].outline.a;

      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].x = win->map[i][j].x + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].y = win->map[i][j].y + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 4].a = win->map[i][j].outline.a;
      
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].x = win->map[i][j].x + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].y = win->map[i][j].y + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 5].a = win->map[i][j].outline.a;

      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].x = win->map[i][j].x + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].y = win->map[i][j].y + 0.9f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 6].a = win->map[i][j].outline.a;
      
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].x = win->map[i][j].x + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].y = win->map[i][j].y + 0.1f;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].z = 0;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].r = win->map[i][j].outline.r;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].g = win->map[i][j].outline.g;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].b = win->map[i][j].outline.b;
      win->pft_tile_line_vertices[(i * win->mapHeight + j) * 8 + 7].a = win->map[i][j].outline.a;
      
      
      
/*      glColor3f(win->map[i][j].color.r, 
                      win->map[i][j].color.g,
                      win->map[i][j].color.b); 
      glBegin(GL_TRIANGLES);
      glNormal3f(0.0f, 0.0f, -1.0f);
      glVertex3i(win->map[i][j].x , win->map[i][j].y, 0);
      glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y, 0);
      glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y + 1, 0);
      
      glVertex3i(win->map[i][j].x , win->map[i][j].y, 0);
      glVertex3i(win->map[i][j].x + 1,  win->map[i][j].y + 1, 0);
      glVertex3i(win->map[i][j].x,  win->map[i][j].y + 1, 0);
      glEnd();
*/      
      //glPopName();
      /*
      if( win->showOutline){
              glColor4f(win->map[i][j].outline.r, win->map[i][j].outline.g, 
                              win->map[i][j].outline.b, win->map[i][j].outline.a);
              glBegin(GL_LINE_STRIP);
      
              glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.1f, 0);
              glVertex3f(win->map[i][j].x + 0.9f, win->map[i][j].y + 0.1f, 0);
              glVertex3f(win->map[i][j].x + 0.9f, win->map[i][j].y + 0.9f, 0);
              glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.9f, 0);
              glVertex3f(win->map[i][j].x + 0.1f, win->map[i][j].y + 0.1f, 0);
      
              glEnd();
      }
      
      
      if(win->map[i][j].dot){
              glPushName(tileName);
              glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
              glBegin(GL_TRIANGLES);
              glNormal3f(0.0f, 0.0f, 1.0f);
              glVertex3f(win->map[i][j].x + 0.25f , win->map[i][j].y + 0.25f, 0.1f);
              glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.25f, 0.1f);
              glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
      
              glVertex3f(win->map[i][j].x + 0.25f, win->map[i][j].y + 0.25f, 0.1f);
              glVertex3f(win->map[i][j].x + 0.75f,  win->map[i][j].y + 0.75f, 0.1f);
              glVertex3f(win->map[i][j].x + 0.25f,  win->map[i][j].y + 0.75f, 0.1f);
              
              glEnd();
              glPopName();
              
      }
      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
      */

            
    }
  }
  
  
  //**********************
  //Create VAO's and VBO's
  //**********************
  
  // *** Create Tile VAO & VBO ***
  
  glGenVertexArrays (1, &win->pft_tile_array_object);
  glBindVertexArray (win->pft_tile_array_object);

  // single buffer to hold triangles
  glGenBuffers (1, &win->pft_tile_buffer_object);
  glBindBuffer (GL_ARRAY_BUFFER, win->pft_tile_buffer_object);
  glBufferData (GL_ARRAY_BUFFER, sizeof ( vertex ) * (width * height * 6), win->pft_tile_vertices, GL_STREAM_DRAW);

  /* enable and set the position attribute */
  // instructs gl to expect 6 position vertices 

  glEnableVertexAttribArray (win->pft_position_id);
  glVertexAttribPointer (win->pft_position_id, 
                         3,        // size // attribute size defines a single attribute, not a cumulative size of all attributes
                         GL_FLOAT, // type
                         GL_FALSE, // normalized
                         sizeof ( vertex ),   //0,        // stride
                         (GLvoid *) 0   //(void*) 0 // offset
                        );
  
  // enable and set the color attribute
  // instructs gl to expect 6 color vertices
  
  glEnableVertexAttribArray (win->pft_color_id);
  glVertexAttribPointer (win->pft_color_id, 
                         4,        // attribute size defines a single attribute, not a cumulative size of all attributes
                         GL_FLOAT, 
                         GL_FALSE,
                         sizeof ( vertex ),   //0,
                         (GLvoid *) ( sizeof ( GLfloat ) * 4 )  //(void*) 0
                        );

  glEnableVertexAttribArray (win->pft_normal_id);
  glVertexAttribPointer (win->pft_normal_id,
                         3,
                         GL_FLOAT,
                         GL_FALSE,
                         sizeof ( vertex ),
                         (GLvoid *) ( sizeof ( GLfloat ) * 8 )
                        );
  

  /* i dont understand the following lines so they are commented */
  /* reset the state; we will re-enable the VAO when needed */
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);

  /* i dont understand the following lines so they are commented */
  /* the VBO is referenced by the VAO */
  glDeleteBuffers (1, &win->pft_tile_buffer_object);
  
  
  // *** Create Tile Lines VAO & VBO ***
  
  glGenVertexArrays (1, &win->pft_tile_line_array_object);
  glBindVertexArray (win->pft_tile_line_array_object);

  // single buffer to hold triangles
  glGenBuffers (1, &win->pft_tile_line_buffer_object);
  glBindBuffer (GL_ARRAY_BUFFER, win->pft_tile_line_buffer_object);
  glBufferData (GL_ARRAY_BUFFER, sizeof ( vertex ) * (width * height * 8), win->pft_tile_line_vertices, GL_STREAM_DRAW);

  /* enable and set the position attribute */
  // instructs gl to expect 6 position vertices 

  glEnableVertexAttribArray (win->pft_position_id);
  glVertexAttribPointer (win->pft_position_id, 
                         3,        // size // attribute size defines a single attribute, not a cumulative size of all attributes
                         GL_FLOAT, // type
                         GL_FALSE, // normalized
                         sizeof ( vertex ),   //0,        // stride
                         (GLvoid *) 0   //(void*) 0 // offset
                        );
  
  // enable and set the color attribute
  // instructs gl to expect 6 color vertices
  
  glEnableVertexAttribArray (win->pft_color_id);
  glVertexAttribPointer (win->pft_color_id, 
                         4,        // attribute size defines a single attribute, not a cumulative size of all attributes
                         GL_FLOAT, 
                         GL_FALSE,
                         sizeof ( vertex ),   //0,
                         (GLvoid *) ( sizeof ( GLfloat ) * 4 )  //(void*) 0
                        );

  glEnableVertexAttribArray (win->pft_normal_id);
  glVertexAttribPointer (win->pft_normal_id,
                         3,
                         GL_FLOAT,
                         GL_FALSE,
                         sizeof ( vertex ),
                         (GLvoid *) ( sizeof ( GLfloat ) * 8 )
                        );
  

  /* i dont understand the following lines so they are commented */
  /* reset the state; we will re-enable the VAO when needed */
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);

  /* i dont understand the following lines so they are commented */
  /* the VBO is referenced by the VAO */
  glDeleteBuffers (1, &win->pft_tile_line_buffer_object);
  
  
#define N_VERTICES 6  
  
  win->pft_vertices = malloc ( sizeof ( vertex ) * N_VERTICES );
  
  win->pft_vertices[0].x = 0.0f; win->pft_vertices[0].y = 0.0f; win->pft_vertices[0].z = 0.0f; win->pft_vertices[0].w = 1.0f;
  win->pft_vertices[1].x = 0.0f; win->pft_vertices[1].y = 0.5f; win->pft_vertices[1].z = 0.0f; win->pft_vertices[1].w = 1.0f;
  win->pft_vertices[2].x = 0.5f; win->pft_vertices[2].y = 0.0f; win->pft_vertices[2].z = 0.0f; win->pft_vertices[2].w = 1.0f;
  
  win->pft_vertices[3].x = 1.0f; win->pft_vertices[3].y = 0.5f; win->pft_vertices[3].z = 0.0f; win->pft_vertices[3].w = 1.0f;
  win->pft_vertices[4].x = 0.5f; win->pft_vertices[4].y = 1.0f; win->pft_vertices[4].z = 0.0f; win->pft_vertices[4].w = 1.0f;
  win->pft_vertices[5].x = 1.0f; win->pft_vertices[5].y = 1.0f; win->pft_vertices[5].z = 0.0f; win->pft_vertices[5].w = 1.0f;
  
  
  win->pft_vertices[0].r = 0.0f; win->pft_vertices[0].g = 0.0f; win->pft_vertices[0].b = 1.0f; win->pft_vertices[0].a = 1.0f;
  win->pft_vertices[1].r = 1.0f; win->pft_vertices[1].g = 0.0f; win->pft_vertices[1].b = 0.0f; win->pft_vertices[1].a = 1.0f;
  win->pft_vertices[2].r = 0.0f; win->pft_vertices[2].g = 1.0f; win->pft_vertices[2].b = 0.0f; win->pft_vertices[2].a = 1.0f;
  
  win->pft_vertices[3].r = 0.0f; win->pft_vertices[3].g = 0.0f; win->pft_vertices[3].b = 1.0f; win->pft_vertices[3].a = 1.0f;
  win->pft_vertices[4].r = 1.0f; win->pft_vertices[4].g = 0.0f; win->pft_vertices[4].b = 0.0f; win->pft_vertices[4].a = 1.0f;
  win->pft_vertices[5].r = 0.0f; win->pft_vertices[5].g = 1.0f; win->pft_vertices[5].b = 0.0f; win->pft_vertices[5].a = 1.0f;
  
  
  win->pft_vertices[0].nx = 0.0f; win->pft_vertices[0].ny = 0.0f; win->pft_vertices[0].z = 0.0f; win->pft_vertices[0].w = 1.0f;
  win->pft_vertices[1].nx = 0.0f; win->pft_vertices[1].ny = 0.5f; win->pft_vertices[1].z = 0.0f; win->pft_vertices[1].w = 1.0f;
  win->pft_vertices[2].nx = 0.5f; win->pft_vertices[2].ny = 0.0f; win->pft_vertices[2].z = 0.0f; win->pft_vertices[2].w = 1.0f;
  
  win->pft_vertices[3].nx = 1.0f; win->pft_vertices[3].ny = 0.5f; win->pft_vertices[3].nz = 0.0f; win->pft_vertices[3].nw = 1.0f;
  win->pft_vertices[4].nx = 0.5f; win->pft_vertices[4].ny = 1.0f; win->pft_vertices[4].nz = 0.0f; win->pft_vertices[4].nw = 1.0f;
  win->pft_vertices[5].nx = 1.0f; win->pft_vertices[5].ny = 1.0f; win->pft_vertices[5].nz = 0.0f; win->pft_vertices[5].nw = 1.0f;
  
  // my understanding: vertex array object holds multiple vertex buffer objects
  // vertex buffer objects store the vertices data which creates geometry
  // each vertex buffer object could be considered a mesh
  glGenVertexArrays (1, &win->pft_vertex_array_object);
  glBindVertexArray (win->pft_vertex_array_object);


  // single buffer to hold triangles
  glGenBuffers (1, &win->pft_vertex_buffer_object);
  glBindBuffer (GL_ARRAY_BUFFER, win->pft_vertex_buffer_object);
  glBufferData (GL_ARRAY_BUFFER, sizeof ( vertex ) * N_VERTICES, win->pft_vertices, GL_STREAM_DRAW);


  /* enable and set the position attribute */
  // instructs gl to expect 6 position vertices
  


  glEnableVertexAttribArray (win->pft_position_id);
  glVertexAttribPointer (win->pft_position_id, 
                         3,        // size // attribute size defines a single attribute, not a cumulative size of all attributes
                         GL_FLOAT, // type
                         GL_FALSE, // normalized
                         sizeof ( vertex ),   //0,        // stride
                         (GLvoid *) 0   //(void*) 0 // offset
                        );
  
  // enable and set the color attribute
  // instructs gl to expect 6 color vertices
  

  glEnableVertexAttribArray (win->pft_color_id);
  glVertexAttribPointer (win->pft_color_id, 
                         4,        // attribute size defines a single attribute, not a cumulative size of all attributes
                         GL_FLOAT, 
                         GL_FALSE,
                         sizeof ( vertex ),   //0,
                         (GLvoid *) ( sizeof ( GLfloat ) * 4 )  //(void*) 0
                        );

  glEnableVertexAttribArray (win->pft_normal_id);
  glVertexAttribPointer (win->pft_normal_id,
                         3,
                         GL_FLOAT,
                         GL_FALSE,
                         sizeof ( vertex ),
                         (GLvoid *) ( sizeof ( GLfloat ) * 8 )
                        );
  

  /* i dont understand the following lines so they are commented */
  /* reset the state; we will re-enable the VAO when needed */
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  glBindVertexArray (0);

  /* i dont understand the following lines so they are commented */
  /* the VBO is referenced by the VAO */
  glDeleteBuffers (1, &win->pft_vertex_buffer_object);
  //glDeleteBuffers (1, &win->pft_vertex_color_buffer_object);

  
  int status;
  
  // 2. Prep Vertex Shaders
  
  // retrieve the src from the file that is a g_resource, within the ptf.gresource.xml file
  win->pft_vertex_shader_src = g_resources_lookup_data ("/org/gtk/path/ptf-vertex.glsl", 0, NULL);
  
  win->pft_vertex_shader_src_ptr = ( gpointer ) g_bytes_get_data (win->pft_vertex_shader_src, NULL);
  
  // create a vertex shader and store the id in win->pft_vertex_shader_id
  win->pft_vertex_shader_id = glCreateShader ( GL_VERTEX_SHADER );
  
  // replaces the source code in a shader object, stores source code in object with vertex shader id
  glShaderSource (win->pft_vertex_shader_id, 1, ( const char** ) &win->pft_vertex_shader_src_ptr, NULL);
  
  // compiles the source of shader object
  glCompileShader (win->pft_vertex_shader_id);

  // release the g_resources_lookup_data
  g_bytes_unref ( win->pft_vertex_shader_src );
  
  // test for failure in vertex shader
  
  // ask for status of the vertex shader
  glGetShaderiv (win->pft_vertex_shader_id, GL_COMPILE_STATUS, &status);
  
  // if vertex shader is error
  if (status == GL_FALSE)
  {
    int log_len;
    
    // ask for log length
    glGetShaderiv (win->pft_vertex_shader_id, GL_INFO_LOG_LENGTH, &log_len);

    char *buffer = g_malloc (log_len + 1);
 
    // ask for log
    glGetShaderInfoLog (win->pft_vertex_shader_id, log_len, NULL, buffer);
    
    // set an error
    g_set_error (&error, 
                 GLAREA_ERROR,
                 GLAREA_ERROR_SHADER_COMPILATION,
                 "Compilation failure in vertex shader.",
                 buffer);
    
    // free the error buffer
    g_free (buffer);

    // delete the shader
    glDeleteShader (win->pft_vertex_shader_id);
    
    // set the shader id to 0
    win->pft_vertex_shader_id = 0;

    // set the error on area gtkglarea widget
    gtk_gl_area_set_error (area, error);
    
    // free the error
    g_error_free (error);
    
    
    
    
    
    
    
    
    // return from function
    return;
    
  }

  
  // 3. Prep Fragment Shader
  // ^^^^^^^^^^^^^^^^^^^^^^^
  
  // retrieve the src from the file that is a g_resource, within the ptf.gresource.xml file
  win->pft_fragment_shader_src = g_resources_lookup_data ("/org/gtk/path/ptf-fragment.glsl", 0, NULL);
  
  win->pft_fragment_shader_src_ptr = ( gpointer ) g_bytes_get_data (win->pft_fragment_shader_src, NULL);
  
  // create a fragment shader and store the id in win->pft_fragment_shader_id
  win->pft_fragment_shader_id = glCreateShader ( GL_FRAGMENT_SHADER );
  
  // replaces the source code in a shader object, stores source code in object with fragment shader id
  glShaderSource (win->pft_fragment_shader_id, 1, ( const char** ) &win->pft_fragment_shader_src_ptr, NULL);
  
  // compiles the source of shader object
  glCompileShader (win->pft_fragment_shader_id);

  // release the g_resources_lookup_data
  g_bytes_unref ( win->pft_fragment_shader_src );
  
  // test for failure in fragment shader
  
  // ask for status of the fragment shader
  glGetShaderiv (win->pft_fragment_shader_id, GL_COMPILE_STATUS, &status);
  
  // if fragment shader is error
  if (status == GL_FALSE)
  {
    int log_len;
    
    // ask for log length
    glGetShaderiv (win->pft_fragment_shader_id, GL_INFO_LOG_LENGTH, &log_len);

    char *buffer = g_malloc (log_len + 1);
 
    // ask for log
    glGetShaderInfoLog (win->pft_fragment_shader_id, log_len, NULL, buffer);
    
    // set an error
    g_set_error (&error, 
                 GLAREA_ERROR,
                 GLAREA_ERROR_SHADER_COMPILATION,
                 "Compilation failure in fragment shader.",
                 buffer);
    
    // free the error buffer
    g_free (buffer);

    // delete the shader
    glDeleteShader (win->pft_fragment_shader_id);
    
    // set the shader id to 0
    win->pft_fragment_shader_id = 0;

    // set the error on area gtkglarea widget
    gtk_gl_area_set_error (area, error);
    
    // free the error
    g_error_free (error);
    
    // return from function
    return;
    
  }
  
  // create the program, link it, check it
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  
  // create the program
  win->pft_program_id = glCreateProgram ();
  
  // attach the vertex shader
  glAttachShader ( win->pft_program_id, win->pft_vertex_shader_id );
  
  // attach the fragment shader
  glAttachShader ( win->pft_program_id, win->pft_fragment_shader_id );
  
  // link the program
  glLinkProgram ( win->pft_program_id );
  
  // check the program
  
  // get linking status
  glGetProgramiv ( win->pft_program_id, GL_LINK_STATUS, &status);
  
  if (status == GL_FALSE)
  {
    int log_len = 0;
    glGetProgramiv (win->pft_program_id, GL_INFO_LOG_LENGTH, &log_len);

    char *buffer = g_malloc (log_len + 1);
    glGetProgramInfoLog (win->pft_program_id, log_len, NULL, buffer);

    g_set_error (&error, GLAREA_ERROR, GLAREA_ERROR_SHADER_LINK,
                  "Linking failure in program: %s", buffer);

    g_free (buffer);

    glDeleteProgram (win->pft_program_id);
    win->pft_program_id = 0;

    // set the error on area gtkglarea widget
    gtk_gl_area_set_error (area, error);
    
    // free the error
    g_error_free (error);
    
    // return from function
    return;

  }

  
  // collect data for dynamic changes
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  // model view projection
  // this is one of the items that makes up the three? matrixes for a scene, model view, world view, projection view - i think
  // fyi: http://www.codinglabs.net/article_world_view_projection_matrix.aspx
  // todo: need to sort this out - should shader have 3 uniform matrices ? probably and then the math is done by the shader language gpl
  
  /* get the location of the "mvp" uniform */
  win->pft_gsl_rotate_matrix_id = glGetUniformLocation (win->pft_program_id, "rotate");
  win->pft_gsl_scale_matrix_id = glGetUniformLocation (win->pft_program_id, "scale");
  win->pft_gsl_translate_matrix_id = glGetUniformLocation (win->pft_program_id, "translate");
  
  /* get the location of the "position" and "color" attributes */
  win->pft_position_location_id = glGetAttribLocation (win->pft_program_id, "position");
  win->pft_color_location_id = glGetAttribLocation (win->pft_program_id, "color");

  /* the individual shaders can be detached and destroyed */
  glDetachShader (win->pft_program_id, win->pft_vertex_shader_id);
  glDetachShader (win->pft_program_id, win->pft_fragment_shader_id);

  if (win->pft_vertex_shader_id != 0)
  {
    glDeleteShader (win->pft_vertex_shader_id);
  }
  
  if (win->pft_fragment_shader_id != 0)
  {
    glDeleteShader (win->pft_fragment_shader_id);
  }
  
  
  
  
  
  
  


  
  
  
  
  // set render state
  // ^^^^^^^^^^^^^^^^

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);
    
  
  
  
  
  
  
  
  
  /*
  
  PtfVisuWindow* win = data;
  g_message ( "realize" );
  //GdkGLContext* context;
  
  gtk_gl_area_make_current (area);
  
  if (gtk_gl_area_get_error (area) != NULL)
    return;
  
  */
  // You can also use gtk_gl_area_set_error() in order
  // to show eventual initialization errors on the
  // GtkGLArea widget itself
  
  /*
  GError *error = NULL;
  
  //glewInit();
  //glViewport(0, 0, 100, 100);
  
  init_buffers (win->position_index, win->color_index, &win->vertexArrayObject);
  if (error != NULL)
    {
      gtk_gl_area_set_error (area, error);
      g_error_free (error);
      return;
    }

  init_shaders (&win->prog, &win->mvp_location, &win->position_index, &win->color_index, &error);
  if (error != NULL)
    {
      gtk_gl_area_set_error (area, error);
      g_error_free (error);
      return;
    }
  
  
  return;
  
  
  //context = gtk_gl_area_get_context ( area );
  
  
  //GdkGLContext *gtk_gl_area_get_context (GtkGLArea *area);
  
  
  
  glEnable(GL_LINE_SMOOTH);

  win->showOutline = TRUE;
  win->createFractal = FALSE;
  
  // read in size of map
  int width = 11;
  int height = 11;
  win->zoom = 10;
  //sscanf(cArgs, "%d %d", &width, &height);
  srand ( time(NULL) );
  win->start = NULL;
  win->end = NULL;
  win->waitingForEnd = FALSE;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  //srand( time(NULL));
  //glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.2f, 0.0f, 0.5f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  glEnable(GL_NORMALIZE);

  win->l.light_ambient[0] = 0.1f;
  win->l.light_ambient[1] = 0.1f;
  win->l.light_ambient[2] = 0.1f;
  win->l.light_ambient[3] = 1.0f;
  
  win->l.light_specular[0] = 0.1f;
  win->l.light_specular[1] = 0.1f;
  win->l.light_specular[2] = 0.1f;
  win->l.light_specular[3] = 1.0f;
  
  win->l.light_diffuse[0] = 1.0f;
  win->l.light_diffuse[1] = 0.5f;
  win->l.light_diffuse[2] = 0.5f;
  win->l.light_diffuse[3] = 1.0f;
  
  win->l.light_position[0] = 0.0f;
  win->l.light_position[1] = 0.0f;
  win->l.light_position[2] = 1.0f;
  win->l.light_position[3] = 1.0f;
  
  glLightfv(GL_LIGHT0, GL_AMBIENT,  win->l.light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  win->l.light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, win->l.light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, win->l.light_position);
  
  glEnable(GL_LIGHT0);
  
  win->ll.light_ambient[0] = 0.1f;
  win->ll.light_ambient[1] = 0.1f;
  win->ll.light_ambient[2] = 0.1f;
  win->ll.light_ambient[3] = 1.0f;
  
  win->ll.light_specular[0] = 0.0f;
  win->ll.light_specular[1] = 0.0f;
  win->ll.light_specular[2] = 0.0f;
  win->ll.light_specular[3] = 1.0f;
  
  win->ll.light_diffuse[0] = 0.5f;
  win->ll.light_diffuse[1] = 1.0f;
  win->ll.light_diffuse[2] = 0.5f;
  win->ll.light_diffuse[3] = 1.0f;
  
  win->ll.light_position[0] = 0.0f;
  win->ll.light_position[1] = 0.0f;
  win->ll.light_position[2] = 5.0f;
  win->ll.light_position[3] = 1.0f;
  
//      glLightfv(GL_LIGHT1, GL_AMBIENT,  ll.light_ambient);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE,  ll.light_diffuse);
//   glLightfv(GL_LIGHT1, GL_SPECULAR, ll.light_specular);
//   glLightfv(GL_LIGHT1, GL_POSITION, ll.light_position); 
  //glEnable(GL_LIGHT1);
          
  win->m.mat_ambient[0] = 0.5f;
  win->m.mat_ambient[1] = 0.5f;
  win->m.mat_ambient[2] = 0.5f;
  win->m.mat_ambient[3] = 1.0f;
  
  win->m.mat_diffuse[0] = 0.5f;
  win->m.mat_diffuse[1] = 0.5f;
  win->m.mat_diffuse[2] = 0.5f;
  win->m.mat_diffuse[3] = 1.5f;
  
  win->m.mat_specular[0] = 0.5f;
  win->m.mat_specular[1] = 0.5f;
  win->m.mat_specular[2] = 0.5f;
  win->m.mat_specular[3] = 1.0f;
  
  win->m.high_shininess = 100.01f;
  
  glMaterialfv(GL_FRONT, GL_AMBIENT, win->m.mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, win->m.mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, win->m.mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, win->m.high_shininess);

  // font stuff
  //BuildFont();
  
  win->currentMode = EDIT_WALKABLE_MODE;
  
  
  win->mapWidth = width;
  win->mapHeight = height;
  
  //win->map = new tile*[height];
  win->map = malloc ( sizeof(tile*) * height );
  win->numBlocks = width * height;

  for( int i = 0; i < height; i++){
    //win->map[i] = new tile[width];
    win->map[i] = malloc ( sizeof( tile ) * width );
  }
  for( int i = 0; i < height; i++){
          //map[i] = new tile[width];
          for( int j = 0; j < width; j++){
                  
                  //win->map[i][j] = (tile*) malloc ( sizeof ( tile ) );
            
                  // all tiles start out 
                  win->map[i][j].walkable = TRUE;   // walkable
                  win->map[i][j].color.r = 0.0f;
                  win->map[i][j].color.g = 1.0f;
                  win->map[i][j].color.b = 0.0f;                               
                  win->map[i][j].color.a = 1.0f;
                  //map[i][j].fill = false;
                  win->map[i][j].density = 0;    // difficulty of 0

                  win->map[i][j].outline.r = 0.0f;
                  win->map[i][j].outline.g = 0.0f;
                  win->map[i][j].outline.b = 0.0f;                             
                  win->map[i][j].outline.a = 1.0f;
                  
                  win->map[i][j].x = j;
                  win->map[i][j].y = i;
                  
                  win->map[i][j].inOpenList = FALSE;
                  win->map[i][j].inClosedList = FALSE;
                  
                  // assign pointers to surrounding nodes
                  win->map[i][j].t1 = ( i-1 >= 0 && j-1 >= 0 ? &win->map[i-1][j-1] : NULL);
                  win->map[i][j].t2 = ( i-1 >= 0 ? &win->map[i-1][j] : NULL);
                  win->map[i][j].t3 = ( i-1 >= 0 && j+1 < width ? &win->map[i-1][j+1] : NULL);
                  win->map[i][j].t4 = ( j-1 >= 0 ? &win->map[i][j-1] : NULL);
                  win->map[i][j].t6 = ( j+1 < width ? &win->map[i][j+1] : NULL);
                  win->map[i][j].t7 = ( i+1 < height && j-1 >= 0 ? &win->map[i+1][j-1] : NULL);
                  win->map[i][j].t8 = ( i+1 < height ? &win->map[i+1][j] : NULL);
                  win->map[i][j].t9 = ( i+1 < height && j+1 < width ? &win->map[i+1][j+1] : NULL);
                  
                  win->map[i][j].f = 0;
                  
                  win->map[i][j].dot = FALSE;
                  
                  for( int w = 0; w < 9; w++){
                          win->map[i][j].normal[w].x = 0.0f;
                          win->map[i][j].normal[w].y = 0.0f;
                          win->map[i][j].normal[w].z = 1.0f;
                  }
          }
          
  }

           */               
/*      for(int w = 0; w < height; w++){
          for( int q = 0; q < width; q++){
                  if( map[w][q].tileCode != 0){
                          int zero = 4 - 4;
                          int breakme = 4/zero;
                  }
          }
  }
*/
  
  //return TRUE;
  
  
  g_message ( "compiled successfully, if error, runtime error" );
  
}





static void
resize ( GtkGLArea *area, int width, int height, gpointer data ) {

  
  PtfVisuWindow* win = data;
  
  return;
  
  if ( width < 100 ) { width = 100; }
  if ( height < 100 ) { height = 100; }
  
  g_message ( "resize h: %d w: %d", width, height );

  if (height==0)                                                                          // Prevent A Divide By Zero By
  {
          height=1;                                                                               // Making Height Equal One
  }

  glViewport(0,0,width,height);                                           // Reset The Current Viewport

  glMatrixMode(GL_PROJECTION);                                            // Select The Projection Matrix
  glLoadIdentity();                                                                       // Reset The Projection Matrix

  win->globalwidth = width;
  win->globalheight = height;
  
  // Calculate The Aspect Ratio Of The Window
  
  // TODO removed glu, need to put back the same or include header/library again
  //gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);
//      gluPerspective(60.0, 1.0, 0.0001, 1000.0);
  glMatrixMode(GL_MODELVIEW);                                                     // Select The Modelview Matrix
  //glLoadIdentity();                                                                     // Reset The Modelview Matrix

 
  
}
  
  

gboolean
timer (gpointer data)
{
  
  PtfVisuWindow* win = data;


  if ( win->rotate_degree >= 360.0 ) { win->rotate_degree = 0.0f; }

  win->rotate_degree += 0.1f;

  rotation_about_y ( win->pft_gsl_rotate_matrix, win->rotate_degree );
  
//  gtk_widget_queue_draw ( GTK_WIDGET ( widget ) );
  
//  win->rotate_degree += 1.0f;
  
//  rotation_about_y ( win->pft_gsl_mwcp_array, win->rotate_degree );


  
  gtk_widget_queue_draw ( GTK_WIDGET ( win->glarea ) );

  return G_SOURCE_CONTINUE;
}

gboolean
tick_timer (GtkWidget *widget, GdkFrameClock *frame_clock, gpointer data)
{
    
  PtfVisuWindow* win = data;
  
  gint64 tick_time = gdk_frame_clock_get_frame_time (frame_clock);
    
  if ( win->frametime == 0 ){ 
    win->frametime = tick_time; 
    return G_SOURCE_CONTINUE;
  }
  
  if ( tick_time - win->frametime >= 100000 ){
    
    if ( win->rotate_degree >= 360.0 ) { win->rotate_degree = 0.0f; }
  
    win->rotate_degree += 0.1f;
  
    rotation_about_y ( win->pft_gsl_rotate_matrix, win->rotate_degree );
    
    gtk_widget_queue_draw ( GTK_WIDGET ( widget ) );
    
    win->frametime = tick_time;
    
  }
    
  return G_SOURCE_CONTINUE;
}

/*
 * init function 
 */
static void
ptf_visu_window_init ( PtfVisuWindow *win )
{

  gtk_widget_init_template ( GTK_WIDGET ( win ) );
  
  /* reset the mvp matrix */
  //init_mvp (win->mvp);  
  
  win->frametime = 0;
  
  win->glarea = GTK_GL_AREA ( gtk_gl_area_new () );

  gtk_box_pack_end ( win->box1, GTK_WIDGET ( win->glarea ), TRUE, TRUE, 10 );
  
  gtk_widget_show ( GTK_WIDGET ( win->glarea ) );
  
  g_signal_connect ( win->glarea, "realize", G_CALLBACK ( on_realize ), win );
  
  g_signal_connect ( win->glarea, "unrealize", G_CALLBACK ( on_finalize ), win );
  
  g_signal_connect ( win->glarea, "resize", G_CALLBACK ( resize ), win );
  
  g_signal_connect ( win->glarea, "render", G_CALLBACK ( render ), win );
 
  win->timerid = g_timeout_add ( 10, timer, win );
  
  //gtk_widget_add_tick_callback ( GTK_WIDGET ( win->glarea ), tick_timer, win, NULL );
  
}

void
ptf_visu_window_get_preferred_width (GtkWidget *widget, gint *minimum_width, gint *natural_width)
{
  *minimum_width = *natural_width = 400;
}

void
ptf_visu_window_get_preferred_height (GtkWidget *widget, gint *minimum_height, gint *natural_height)
{
  *minimum_height = *natural_height = 400;
}


/*
 * creates private member variables for each template variable
 */
static void
ptf_visu_window_class_init ( PtfVisuWindowClass *block )
{

  GtkWidgetClass *widget_class;
  GObjectClass   *gobject_class;
  widget_class = GTK_WIDGET_CLASS(block);
  gobject_class = G_OBJECT_CLASS(block);
  
  widget_class->get_preferred_height = ptf_visu_window_get_preferred_height;
  widget_class->get_preferred_width = ptf_visu_window_get_preferred_width;
  
  //gtk_widget_class_set_template_from_resource ( GTK_WIDGET_CLASS ( block ), "/org/gtk/cdds/cdds.glade" );
  gtk_widget_class_set_template_from_resource ( GTK_WIDGET_CLASS ( block ), "/org/gtk/path/ptf.glade" );
  
  gtk_widget_class_bind_template_child ( GTK_WIDGET_CLASS ( block ), PtfVisuWindow, box1 );
  
  //gtk_widget_class_bind_template_child ( GTK_WIDGET_CLASS ( block ), PtfVisuWindow, paned1 );
  //gtk_widget_class_bind_template_child ( GTK_WIDGET_CLASS ( block ), PtfVisuWindow, paned2 );
  
  
  //gtk_widget_class_bind_template_callback ( GTK_WIDGET_CLASS ( block ), cds_area_dialog_activate_callback);
  
  //gtk_widget_class_bind_template_callback ( GTK_WIDGET_CLASS ( block ), on_realize );
  
  
  
  widget_class->key_press_event = ptf_visu_window_key_press_event;
  widget_class->key_release_event = ptf_visu_window_key_release_event;
  
  gobject_class->dispose = ptf_visu_window_dispose; /* opposite of init */
  gobject_class->finalize = ptf_visu_window_finalize; /* opposite of class_init */
  
  
}


PtfVisuWindow *
ptf_visu_window_new ( GApplication *app )
{
  PtfVisuWindow *w;
  
  w = g_object_new ( CDS_AREA_TYPE_WINDOW, "application", app, NULL );
    
  return w;
}

void
ptf_visu_window_open ( PtfVisuWindow *win, GFile *file )
{

  
  
}

void
ptf_visu_window_dispose ( GObject* obj )
{
  PtfVisuWindow* win;
  win = PTF_VISU_WINDOW ( obj );
  
  
  
  G_OBJECT_CLASS ( ptf_visu_window_parent_class )->dispose ( obj );
}


void
ptf_visu_window_finalize ( GObject* obj )
{
  PtfVisuWindow* win;
  win = PTF_VISU_WINDOW ( obj );
  
  // remove the timer before finalizing or it will fire on a non-widget class
  g_source_remove ( win->timerid );
  
  G_OBJECT_CLASS ( ptf_visu_window_parent_class )->finalize ( obj );
}

void
ptf_visu_window_destroy (PtfVisuWindow *win)
{

  gtk_widget_destroy ( GTK_WIDGET ( win ) );

}

