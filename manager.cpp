#include <vector>
#include "include.h"
#include "manager.h"
#include "shader.h"
#include "camera.h"

void mouse_callback( GLFWwindow* window, double xpos, double ypos );
void scroll_callback( GLFWwindow* window, double xoffset, double yoffset );
void processInput( GLFWwindow *window);

// settings
int width, height;
GLuint programID, VertexArrayID, MatrixID, vertexbufferID, colorbufferID;
glm::mat4 projection, view, model, modelView, rotate;
glm::vec2 SCREEN_SIZE(800, 600);
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 780;
// camera
Camera camera( glm::vec3(0.0f, 0.0f, 55.0f) );
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Consturctor for Mananger calls bool bRun.
Manager::Manager( bool bRun ): bRun( bRun ),
pWindow( glfwGetCurrentContext() ){}
// Destructor
Manager::~Manager(){std::cout << "~Manager" << '\n';}
// Game loop
void Manager::loop(){
    // Load shader
    GLuint programID = LoadShaders( "shaders/shader.vs", "shaders/shader.fs" );
    // Verices and colors for cube
	static const GLfloat vertexData[] = {
        // Face 0
		 -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    - 0.5f, -0.5f, -0.5f,
		 0.5f, 0.5f, -0.5f,   -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f,
        // Face 1
		 -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f,     0.5f, -0.5f, 0.5f,
		 0.5f, -0.5f, -0.5f,   0.5f, -0.5f, 0.5f,     0.5f, 0.5f, -0.5f,
        // Face 2
		 0.5f, -0.5f, 0.5f,    0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, -0.5f,
        // Face 3
		 0.5f, 0.5f, 0.5f,   -0.5f, 0.5f, -0.5f,   -0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,   -0.5f, 0.5f, 0.5f,   -0.5f, -0.5f, -0.5f,
        // Face 4
		-0.5f, 0.5f, 0.5f,   -0.5f, -0.5f, -0.5f,    -0.5, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, 0.5f,	0.5f, -0.5f, 0.5f,
        // Face 5
		 -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f,     -0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f
	};
	static const GLfloat colorData[] = {
        // Face 0
		0.0f,  1.0f,  0.0f,   	1.0f,  1.0f,  0.0f,		0.0f,  0.0f,  0.0f,
		1.0f,  1.0f,  0.0f,		0.0f,  0.0f,  0.0f,		1.0f,  0.0f,  0.0f,
        // Face 1
		0.0f,  0.0f,  0.0f,		1.0f,  0.0f,  0.0f,		1.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  0.0f,		1.0f,  0.0f,  1.0f,		1.0f,  1.0f,  0.0f,
        // Face 2
		1.0f,  0.0f,  1.0f,		1.0f,  1.0f,  0.0f,		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  0.0f,		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,
        // Face 3
		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,		0.0f,  1.0f,  1.0f,
		0.0f,  1.0f,  0.0f,		0.0f,  1.0f,  1.0f,		0.0f,  0.0f,  0.0f,
        // Face 4
	    0.0f,  1.0f,  1.0f,		0.0f,  0.0f,  0.0f,		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  0.0f,		0.0f,  0.0f,  1.0f,		1.0f,  0.0f,  1.0f,
        // Face 5
		0.0f,  0.0f,  1.0f,		1.0f,  0.0f,  1.0f,		0.0f,  1.0f,  1.0f,
		1.0f,  0.0f,  1.0f,		0.0f,  1.0f,  1.0f,		1.0f,  1.0f,  1.0f
	};

    // Make and bind VAO
    glGenVertexArrays( 1, &VertexArrayID );
    glBindVertexArray( VertexArrayID );

    // Make and bind VBO for vertices
	glGenBuffers( 1, &vertexbufferID );
	glBindBuffer( GL_ARRAY_BUFFER, vertexbufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ),
        vertexData, GL_STATIC_DRAW );

    // Make and bind VBO for colors
	glGenBuffers( 1, &colorbufferID );
	glBindBuffer( GL_ARRAY_BUFFER, colorbufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( colorData ),
        colorData, GL_STATIC_DRAW );

    //Set FBS for win resize
    glfwSetFramebufferSizeCallback( pWindow, glfwWinSizeCallback );
    model = glm::translate( model, glm::vec3(0.0f, 0.0f, 50.0f) );

    // Render loop
    while ( bRun ) {
        // Run window
        bRun = !glfwWindowShouldClose( pWindow );

        // set deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Update fps
        update( pWindow );
        // input
        processInput( pWindow );

        // Clear Color and Depth buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // configure transformation matrices
        glm::mat4 projection = glm::perspective( glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f );
        glm::mat4 view = camera.GetViewMatrix();

        // UniformLocation to send to shaders
        GLuint projLoc = glGetUniformLocation( programID, "projection" );
        GLuint viewLoc = glGetUniformLocation( programID, "view" );
        GLuint timeLoc = glGetUniformLocation( programID, "time" );

        // Uniform the matrices
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ));
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ));
        glUniform1f( timeLoc, currentFrame );

        // Run shader program
        glUseProgram( programID );

        // Transform cube
        //model = glm::translate( model, glm::vec3(0.0f, 0.0f, 1.0f) );
        //model = glm::rotate( model, 0.01f, glm::vec3( -1.0f, -1.0f, 0.0f ) );
        GLuint modelLoc = glGetUniformLocation( programID, "model" );
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ));

        // Vertex attrib 0
        glEnableVertexAttribArray(0);
        glBindBuffer( GL_ARRAY_BUFFER, vertexbufferID ) ;
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
        // Color attrib 1
        glEnableVertexAttribArray(1);
        glBindBuffer( GL_ARRAY_BUFFER, colorbufferID );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
        // Draw
        glDrawArrays( GL_TRIANGLES, 0, 12*3 );
        // Clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        // Buffer and event window close
        glfwSwapBuffers( pWindow );
        if( GLFW_PRESS == glfwGetKey( pWindow, GLFW_KEY_ESCAPE ) ){
            glfwSetWindowShouldClose( pWindow, 1 );
        }
        glfwPollEvents();
    }
}
// Overload th e address of Manager object with glfw functions
Manager &Manager::getManager(){
    static Manager *oManager = NULL;
    if( oManager == NULL ){
        glfwSetErrorCallback( glfwErrorCallback );

        if( !glfwInit() )
            throw std::runtime_error("glfwInit failed..");

            glfwWindowHint( GLFW_FLOATING, GLFW_TRUE );

        	glfwWindowHint( GLFW_RED_BITS, 8 );
        	glfwWindowHint( GLFW_GREEN_BITS, 8 );
        	glfwWindowHint( GLFW_BLUE_BITS, 8 );
        	glfwWindowHint( GLFW_ALPHA_BITS, 8 );
        	glfwWindowHint( GLFW_REFRESH_RATE, GLFW_DONT_CARE );

            glfwWindowHint( GLFW_SAMPLES, 4 );
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
            glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

            GLFWwindow *pWindow = glfwCreateWindow( (int)SCREEN_SIZE.x,
                (int)SCREEN_SIZE.y, "NULL", NULL, NULL );
            if( !pWindow )
                throw std::runtime_error( "glfwCreateWindow failed..");

            glfwMakeContextCurrent( pWindow );
            // Get FBS for win resize
            glfwGetFramebufferSize(pWindow, &width, &height);
            glfwSetCursorPosCallback( pWindow, mouse_callback );
            glfwSetScrollCallback( pWindow, scroll_callback );
            glfwSetInputMode( pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
            glfwSwapInterval(1);

            glewExperimental = GL_TRUE;
            if( glewInit() != GLEW_OK )
                throw std::runtime_error( "glewInit failed.." );

            // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            //     throw std::runtime_error( "gladLoadGLLoader failed..");
        	// }

            std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
            std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
            std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n' << '\n';
            std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

            glEnable( GL_DEPTH_TEST );
            glShadeModel( GL_SMOOTH );
            glDepthFunc( GL_LESS );
            glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );

            oManager = new Manager( true );
    }
    return *oManager;
}
void Manager::glfwWinSizeCallback( GLFWwindow *pWindow, int width, int height ){
    glViewport( 0, 0, width, height );
    //glfwGetWindowUserPointer( pWindow );
    SCREEN_SIZE = glm::vec2( width, height );
    std::cout << "Width.."<< width << "\theight.." << height << '\n';
}
void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}
void Manager::glfwErrorCallback( int error, const char *description ){
    std::cout << "Error: " << description << '\n';
    fputs( description, stderr );
}
void Manager::update( GLFWwindow *pWindow ){
    static double pSec = glfwGetTime();
    static int frameCount;
    double cSec = glfwGetTime();
    double eSec = cSec - pSec;
    if( eSec > 0.25 ){
        pSec = cSec;
        double fps = ( double )frameCount / eSec;
        char tmp[128];
        sprintf( tmp, "GLFW Window.. fps: %.2f", fps );
        glfwSetWindowTitle( pWindow, tmp );
        frameCount = 0;
    }
    frameCount++;
}
void Manager::desManager(){
    //std::cout << "In desManager.." << '\n';
    glDeleteBuffers( 1, &vertexbufferID );
    glDeleteBuffers( 1, &colorbufferID );
    glDeleteProgram( programID );
    glDeleteVertexArrays( 1, &VertexArrayID );
    Manager *oManager = &getManager();
    delete oManager;
    GLFWwindow *pWindow = glfwGetCurrentContext();
    glfwDestroyWindow( pWindow );
    glfwTerminate();
}
