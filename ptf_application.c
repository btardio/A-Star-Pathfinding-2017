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

#include "ptf.h"
#include "ptf_application.h"
#include "ptf_window.h"


G_DEFINE_TYPE(PtfVisuApp, ptf_visu_app, GTK_TYPE_APPLICATION)


static void
ptf_visu_app_init (PtfVisuApp *app)
{


  
}



static void
ptf_visu_app_activate (GApplication *app)
{

  //CDS_AREA_APP(app)->win = window = cds_area_window_new ( app );
  PTF_VISU_APP(app)->win = ptf_visu_window_new ( app );

  gtk_window_present (GTK_WINDOW (PTF_VISU_APP(app)->win));

/*  
  if ( g_test_initialized() )
  {
    g_test_run();
    g_application_quit (app);
  }
*/
  
  //g_test_run ();
}

static void
ptf_visu_app_class_init (PtfVisuAppClass *block)
{
  
  G_APPLICATION_CLASS (block)->shutdown = ptf_visu_app_shutdown;
  G_APPLICATION_CLASS (block)->activate = ptf_visu_app_activate;
  G_APPLICATION_CLASS (block)->startup = ptf_visu_app_startup;
  G_APPLICATION_CLASS (block)->open = ptf_visu_app_open;
}

PtfVisuApp*
ptf_visu_app_new (void)
{
  return g_object_new (PTF_VISU_TYPE_APP,
                       "application-id", "org.gtk.path",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}


static void
ptf_visu_app_startup (GApplication *app)
{

  G_APPLICATION_CLASS (ptf_visu_app_parent_class)->startup (app);
  
}

void
ptf_visu_app_shutdown ( GApplication *app )
{
  
  G_APPLICATION_CLASS (ptf_visu_app_parent_class)->shutdown (app);
  
}

static void
ptf_visu_app_open (GApplication  *app,
                   GFile        **files,
                   gint           n_files,
                   const gchar   *hint)
{
  GList *windows;
  PtfVisuWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = PTF_VISU_WINDOW (windows->data);
  else
    win = ptf_visu_window_new ( app );

  for (i = 0; i < n_files; i++)
    ptf_visu_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}
