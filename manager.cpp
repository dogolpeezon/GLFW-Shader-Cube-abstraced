#include "include.h"
#include "manager.h"
#include "shader.h"
#include <vector>
glm::vec2 SCREEN_SIZE(800, 600);
int width, height;
GLuint programID, VertexArrayID, MatrixID, vertexbufferID, colorbufferID;
glm::mat4 projection, view, model, modelView, rotate;

Manager::Manager( bool bRun ): bRun( bRun ),
pWindow( glfwGetCurrentContext() ){}
Manager::~Manager(){}

void Manager::loop(){
    //std::cout << "In loop.." << '\n';
    GLuint programID = LoadShaders( "shader.vs", "shader.fs" );

	static const GLfloat vertexData[] = {
        // Face 0
		 0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,     0.5f, -0.5f, 0.5f,
		 0.5f, -0.5f, 0.5f,   -0.5f, 0.5f, 0.5f,    -0.5f, -0.5f, 0.5f,
        // Face 1
		 0.5f, 0.5f, 0.5f,    0.5f, -0.5f, 0.5f,     0.5f, 0.5f, -0.5f,
		 0.5f, 0.5f, -0.5f,   0.5f, -0.5f, 0.5f,     0.5f, -0.5f, -0.5f,
        // Face 2
		 0.5f, 0.5f, 0.5f,    0.5f, 0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,    0.5f, 0.5f, -0.5f,    -0.5f, 0.5f, -0.5f,
        // Face 3
		 0.5f, 0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   -0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   -0.5f, -0.5f, -0.5f,
        // Face 4
		-0.5f, 0.5f, 0.5f,   -0.5f, 0.5f, -0.5f,    -0.5, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,  -0.5f, 0.5f, -0.5f,	-0.5f, -0.5f, -0.5f,
        // Face 5
		 0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,     0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f
	};
	static const GLfloat colorData[] = {
        // Face 0
		1.0f,  1.0f,  0.0f,   	0.0f,  1.0f,  0.0f,		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,		0.0f,  1.0f,  0.0f,		0.0f,  0.0f,  0.0f,
        // Face 1
		1.0f,  1.0f,  0.0f,		1.0f,  0.0f,  0.0f,		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,		1.0f,  0.0f,  0.0f,		1.0f,  0.0f,  1.0f,
        // Face 2
		1.0f,  1.0f,  0.0f,		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,		1.0f,  1.0f,  1.0f,		0.0f,  1.0f,  1.0f,
        // Face 3
		1.0f,  1.0f,  1.0f,		1.0f,  0.0f,  1.0f,		1.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  1.0f,		1.0f,  0.0f,  1.0f,		0.0f,  1.0f,  1.0f,
        // Face 4
	    0.0f,  1.0f,  0.0f,		0.0f,  1.0f,  1.0f,		0.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f,		0.0f,  1.0f,  1.0f,		0.0f,  1.0f,  1.0f,
        // Face 5
		0.0f,  0.0f,  1.0f,		0.0f,  0.0f,  0.0f,		1.0f,  0.0f,  1.0f,
		1.0f,  0.0f,  1.0f,		0.0f,  0.0f,  0.0f,		0.0f,  0.0f,  1.0f
	};

    glGenVertexArrays( 1, &VertexArrayID );
    glBindVertexArray( VertexArrayID );

	glGenBuffers( 1, &vertexbufferID );
	glBindBuffer( GL_ARRAY_BUFFER, vertexbufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertexData ),
        vertexData, GL_STATIC_DRAW );

	glGenBuffers( 1, &colorbufferID );
	glBindBuffer( GL_ARRAY_BUFFER, colorbufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof( colorData ),
        colorData, GL_STATIC_DRAW );

    glfwGetFramebufferSize(pWindow, &width, &height);
    glViewport( 0, 0, width, height );
    float aspect = ( float )width / ( float )height;
    projection = glm::perspective( 45.0f, aspect,
        0.1f, 10.0f );
    view = glm::translate( view, glm::vec3( 0.0f , 0.0f, -2.0f ) );
    model = glm::rotate( model, 0.01f, glm::vec3( 0.0f, -1.0f, -1.0f ) );
    modelView = model * view;

    while ( bRun ) {
        bRun = !glfwWindowShouldClose( pWindow );
        update( pWindow );
        //double cSec = glfwGetTime();
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        model = glm::rotate( model, 0.01f, glm::vec3( 0.0f, -1.0f, -1.0f ) );
        //view = glm::translate( view, glm::vec3(0.0f , 0.0f, 0.0f) );
        GLuint modelLoc = glGetUniformLocation( programID, "model" );
        GLuint viewLoc = glGetUniformLocation( programID, "view" );
        GLuint projLoc = glGetUniformLocation( programID, "projection" );

        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ));
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ));
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ));

        glUseProgram( programID );

        glEnableVertexAttribArray(0);
        glBindBuffer( GL_ARRAY_BUFFER, vertexbufferID ) ;
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0,
            (void*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer( GL_ARRAY_BUFFER, colorbufferID );
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,
            (void*)0);

        glDrawArrays( GL_TRIANGLES, 0, 12*3 );

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers( pWindow );
        if( GLFW_PRESS == glfwGetKey( pWindow, GLFW_KEY_ESCAPE ) ){
            glfwSetWindowShouldClose( pWindow, 1 );
        }
        glfwPollEvents();
    }
}

Manager &Manager::getManager(){
    //std::cout << "In getManager.." << '\n';
    static Manager *oManager = NULL;
    if( oManager == NULL ){
        glfwSetErrorCallback( glfwErrorCallback );

        if( !glfwInit() )
            throw std::runtime_error("glfwInit failed..");
        glfwWindowHint( GLFW_SAMPLES, 4 );
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

        GLFWwindow *pWindow = glfwCreateWindow( (int)SCREEN_SIZE.x,
            (int)SCREEN_SIZE.y,
             "NULL",
             NULL, NULL );
        if( !pWindow )
            throw std::runtime_error( "glfwCreateWindow failed..");

        glfwSetWindowUserPointer( pWindow, oManager );
        glfwSetFramebufferSizeCallback( pWindow, glfwWinSizeCallback );
        glfwMakeContextCurrent( pWindow );
        glfwSwapInterval(1);

        glewExperimental = GL_TRUE;
        if( glewInit() != GLEW_OK )
            throw std::runtime_error( "glewInit failed.." );

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
    glfwGetWindowUserPointer( pWindow );
    SCREEN_SIZE = glm::vec2( width, height );
    std::cout << "Width.."<< width << "\theight.." << height << '\n';
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
