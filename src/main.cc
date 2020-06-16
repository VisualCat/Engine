
#include <GLFW/glfw3.h>

void main() {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 600, "Joystick Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

}
