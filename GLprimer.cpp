/*
* A C++ framework for OpenGL programming in TNM046 for MT1 2014.
*
* This is a small, limited framework, designed to be easy to use
* for students in an introductory computer graphics course in
* the first year of a M Sc curriculum. It uses custom code
* for some things that are better solved by external libraries
* like GLEW and GLM, but the emphasis is on simplicity and
* readability, not generality.
* For the window management, GLFW 3.0 is used for convenience.
* The framework should work in Windows, MacOS X and Linux.
* Some Windows-specific stuff for extension loading is still
* here. GLEW could have been used instead, but for clarity
* and minimal dependence on other code, we rolled our own extension
* loading for the things we need. That code is short-circuited on
* platforms other than Windows. This code is dependent only on
* the GLFW and OpenGL libraries. OpenGL 3.3 or higher is required.
*
* Author: Stefan Gustavson (stegu@itn.liu.se) 2013-2014
* This code is in the public domain.
*/
// Link statically with GLEW
//#define GLEW_STATIC
#define _USE_MATH_DEFINES
// Headers

// File and console I/O for logging and error reporting

#include <windows.h>
#include <GL/glew.h>
#include <iostream>
#include <math.h>

// GLFW 3.x, to handle the OpenGL window

#include <GL/glfw3.h>
#include "Utilities.hpp"
#include "Shader.hpp"
#include "TriangleSoup.hpp"
#include "Rotator.hpp "

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
 * main(argc, argv) - the standard C++ entry point for the program
 */


int main(int argc, char *argv[]) {

	Shader myShader;
	TriangleSoup myShape;

	float time;

	GLfloat Model[16] = {};
	GLfloat Ry[16] = {};
	GLfloat Rz[16] = {};
	GLfloat P[16] = {};
	GLfloat T[16] = {};
	GLfloat S[16] = {};
	GLfloat RxMouse[16] = {};
	GLfloat RyMouse[16] = {};


	GLint location_time;
	GLint location_Model;
	GLint location_uniProj;
	GLint location_uniView;

	MouseRotator myMouseRotator;


    using namespace std;

	int width, height;
    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
	GLFWwindow *window;    // GLFW struct to hold information about the window


    // Initialise GLFW
    glfwInit();

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Make sure we are getting a GL context of at least version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Exclude old legacy cruft from the context. We don't need it, and we don't want it.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a square window (aspect 1:1) to fill half the screen height
    window = glfwCreateWindow(vidmode->height/2, vidmode->height/2, "GLprimer", NULL, NULL);
    if (!window)
    {
        cout << "Unable to open window. Terminating." << endl;
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }

	

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required, or things will simply not work)
    glfwMakeContextCurrent(window);

	
	
	// Initialise GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Set up projection
	glm::mat4 view = glm::lookAt(
		glm::vec3(-2.2f, 100.2f, 100.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);
	
	// Set up perspective
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	//shaders----------------
	myShader.createShader("vertex.glsl", "fragment.glsl");
	
	Utilities::loadExtensions();


    // Show some useful information on the GL context
    cout << "GL vendor:       " << glGetString(GL_VENDOR) << endl;
    cout << "GL renderer:     " << glGetString(GL_RENDERER) << endl;
    cout << "GL version:      " << glGetString(GL_VERSION) << endl;
    cout << "Desktop size:    " << vidmode->width << "x" << vidmode->height << " pixels" << endl;
    
	location_Model = glGetUniformLocation(myShader.programID, "Model");
	location_uniProj = glGetUniformLocation(myShader.programID, "proj");
	location_uniView = glGetUniformLocation(myShader.programID, "view");

	location_time = glGetUniformLocation(myShader.programID, "time");
	if (location_time == -1) { // If the variable is not found , -1 is returned
		cout << " Unable to locate variable 'time' in shader !" << endl;
	}

	myMouseRotator.init(window);
	myShape.createTriangle();

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
		Utilities::displayFPS(window);
		// Get window size. It may start out different from the requested
		// size, and will change if the user resizes the window.
		glfwGetWindowSize(window, &width, &height);
		// Set viewport. This is the pixel rectangle we want to draw into.
		glViewport(0, 0, width, height); // The entire window
		
		// Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		myMouseRotator.poll(window);

        /* ---- Rendering code should go here ---- */
		// Draw our triangle with 3 vertices .
		myShape.render();

		// Activate the vertex array object we want to draw (we may have several )
		time = (float)glfwGetTime(); // Number of seconds since the program was started
		//glUniform1f(location_time, time);


		Utilities::mat4rotz(RyMouse, myMouseRotator.phi); //musrotation yled
		Utilities::mat4rotx(RxMouse, -myMouseRotator.theta);  //musrotation xled
		Utilities::mat4mult(RxMouse, RyMouse, Model);

		Utilities::mat4rotx(Rz, M_PI / 2);
		Utilities::mat4identity(S);
		Utilities::mat4scale(S, 0.1);
		Utilities::mat4translate(T, 0,0,0);
		Utilities::mat4mult(S, T, T);
		Utilities::mat4mult(S, Model, Model);


		glUniformMatrix4fv(location_Model, 1, GL_FALSE, Model); // Copy the value
		glUniformMatrix4fv(location_uniView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(location_uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		glUseProgram(myShader.programID);
		
		// Swap buffers, i.e. display the image and prepare for next frame.
        glfwSwapBuffers(window);

		// Poll events (read keyboard and mouse input)
		glfwPollEvents();

        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
          glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }

    // Close the OpenGL window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


