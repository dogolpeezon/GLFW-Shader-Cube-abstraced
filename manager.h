#ifndef _manager_h_
#define _manager_h_

#include "include.h"

class Manager{
private:
    bool bRun;
    GLFWwindow *pWindow;
    void update( GLFWwindow *pWindow );
    static void glfwWinSizeCallback( GLFWwindow *pWindow, int width, int height );
    static void glfwErrorCallback( int error, const char *description );

    Manager( bool bRun );
    ~Manager();
public:
    void loop();
    static Manager &getManager();
    static void desManager();
};
#endif
