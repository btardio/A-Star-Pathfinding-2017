#version 330 core

// Input vertex data, different for all executions of this shader.
//layout(location = 0) in vec3 vertexPosition_modelspace;
//layout(location = 1) in vec4 vertexColor;
//layout(location = 2) in vec3 vertexNormal;

in vec3 vertexPosition_modelspace;
in vec4 vertexColor;
in vec3 vertexNormal;

// Output data ; will be interpolated for each fragment.
out vec4 fragmentColor;
out vec3 fragmentNormal;
// Values that stay constant for the whole mesh.
uniform mat4 rotate;
uniform mat4 scale;
uniform mat4 translate;

void main(){    

        // Output position of the vertex, in clip space : MVP * position
        gl_Position = ( translate * ( scale * vec4(vertexPosition_modelspace,1) ) );

        //gl_Position = MVP * vec4(gl_Vertex, 1);
        
        // The color of each vertex will be interpolated
        // to produce the color of each fragment
        fragmentColor = vertexColor;
        fragmentNormal = vertexNormal;
}




/*

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){    

        // Output position of the vertex, in clip space : MVP * position
        gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

        // The color of each vertex will be interpolated
        // to produce the color of each fragment
        fragmentColor = vertexColor;
}


*/



/*
#version 130

in vec3 position;
in vec3 color;

uniform mat4 mvp;

smooth out vec4 vertexColor;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  vertexColor = vec4(color, 1.0);
}
*/




/*
#version 330 core
//#version 130

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

///out vec3 fragmentColor;

void main(){

  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
  ///fragmentColor = vertexColor;
}

*/

//in vec3 position;
//in vec3 color;

//uniform mat4 mvp;

//smooth out vec4 vertexColor;

//void main() {
//  gl_Position = mvp * vec4(position, 1.0);
//  vertexColor = vec4(color, 1.0);
  
//}