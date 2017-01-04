#version 330 core

// Interpolated values from the vertex shaders
in vec4 fragmentColor;
in vec3 fragmentNormal;

// Ouput data
out vec4 color;

void main(){

        // Output color = color specified in the vertex shader, 
        // interpolated between all 3 surrounding vertices
        color = fragmentColor;
        
}


/*
#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

// Ouput data
out vec3 color;

void main(){

        // Output color = color specified in the vertex shader, 
        // interpolated between all 3 surrounding vertices
        color = fragmentColor;

}
*/

/*
#version 130

smooth in vec4 vertexColor;

out vec4 outputColor;

void main() {
  outputColor = vertexColor;
}
*/



//#version 330 core
//#version 130

//smooth in vec4 vertexColor;

//out vec4 outputColor;

///in vec3 fragmentColor;

//out vec3 color;

//void main() {
  //outputColor = vertexColor;
//  color = vec3(1,0,0);
  
  ///color = fragmentColor;
//}