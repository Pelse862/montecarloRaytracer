#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Scene.h"

using namespace std;

int main() {
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  

  //some tests 
  float points[] = {

    //floor 36
    0.0f,  -6.0f,  -5.0f,
    10.0f, -6.0f,  -5.0f,
    0.0f, 6.0f,  -5.0f,

    10.0f, -6.0f,  -5.0f,
    10.0f,  6.0f,  -5.0f,
    0.0f, 6.0f,  -5.0f,

    0.0f,  -6.0f,  -5.0f,
    0.0f, 6.0f,  -5.0f,
    -3.0f, 0.0f, -5.0f,

    10.0f,  6.0f,  -5.0f,
    13.0f, 0.0f, -5.0f,
    10.0f,  6.0f,  -5.0f,

    //roof 36
    0.0f,  -6.0f,  5.0f,
    10.0f, -6.0f,  5.0f,
    0.0f, 6.0f,  5.0f,

    10.0f, -6.0f,  5.0f,
    10.0f,  6.0f,  5.0f,
    0.0f, 6.0f,  5.0f,

    0.0f,  -6.0f,  5.0f,
    0.0f, 6.0f,  5.0f,
    -3.0f, 0.0f, 5.0f,

    10.0f,  6.0f,  5.0f,
    13.0f, 0.0f, 5.0f,
    10.0f,  6.0f,  5.0f,

    //opposing side left 18

    10.0f, 6.0f, 5.0f,
    10.0f, 6.0f, -5.0f,
    13.0f, 0.0f, -5.0f,
   
    13.0f, 0.0f, -5.0f,
    13.0f, 0.0f, 5.0f,
    10.0f, 6.0f, 5.0f,

    //opposing side right 18

    10.0f, -6.0f, -5.0f,
    10.0f, -6.0f, 5.0f,
    13.0f, 0.0f, -5.0f,

    10.0f, -6.0f, 5.0f,
    13.0f, 0.0f, 5.0f,
    13.0f, 0.0f, -5.0f,



  };

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 90 * sizeof(float), points, GL_STATIC_DRAW);
  
  
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


  //shaders 
  const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "void main () {"
    "  gl_Position = vec4 (vp, 1.0);"
    "}";
  const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";

  //linking
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);


  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling 
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);

  }
  glfwTerminate();

	return 0;
}