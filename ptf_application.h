#ifndef __PTF_VISU_APPLICATION_H
#define __PTF_VISU_APPLICATION_H

#include "ptf.h"

G_BEGIN_DECLS

#define PTF_VISU_TYPE_APP (ptf_visu_app_get_type ())
G_DECLARE_FINAL_TYPE(PtfVisuApp, ptf_visu_app, PTF_VISU, APP, GtkApplication)

GType             ptf_visu_app_get_type    ( void );
PtfVisuApp       *ptf_visu_app_new         ( void );
static void       ptf_visu_app_startup     ( GApplication *app );
void              ptf_visu_app_shutdown    ( GApplication *app );
static void       ptf_visu_app_open        ( GApplication *app, GFile **files, gint n_files, const gchar *hint );

G_END_DECLS


struct _PtfVisuApp
{
  GtkApplication parent_instance;
  PtfVisuWindow* win;
};

struct _PtfVisuAppClass
{
  GtkApplicationClass parent_class_instance;
};



#endif // __PTF_VISU_APPLICATION_H