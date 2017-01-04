
#include "ptf.h"
#include "ptf_application.h"

/*
int main ( void ) {
  
  printf("Hello World\n");
  
  
}
*/

int main(int argc, char **argv) {  

  g_setenv ("GSETTINGS_SCHEMA_DIR", ".", FALSE);  
    
  return g_application_run (G_APPLICATION (ptf_visu_app_new ()), argc, argv);
 
}