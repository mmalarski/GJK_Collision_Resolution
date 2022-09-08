#include "Camera.h"
#include "CubeManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Light.h"
#include "Shader.h"

#define WINDOW_WIDTH    1020
#define WINDOW_HEIGHT   860

void processInput(GLFWwindow* window, Camera& camera, Light& directionalLight);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "GLEW not initialised! - " << err << std::endl;
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glfwSetCursorPos(window, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    Camera camera(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    Light directionalLightPosition({ 2.0f, 0.0f, 2.0f });
    Cube cube({ 0.0f, 3.0f, 0.0f });
    CubeManager cubeManager(10, 3.0f, 2.0f, 1.0f);
    Shader basicShader("res/shaders/basic.shader");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, camera, directionalLightPosition);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        basicShader
            .use()
            .setUniform("model", cube.getModelMatrix())
            .setUniform("view", camera.getViewMatrix())
            .setUniform("projection", glm::perspective(glm::radians(camera.getZoom()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.01f, 100.0f))
            .setUniform("u_Color", cube.getColor())
            .setUniform("directionalLight", directionalLightPosition.getPosition());
        
        cube.render();

        cubeManager.render(basicShader);

        directionalLightPosition.render(basicShader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera, Light& directionalLight)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(UP);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKeyboard(DOWN);

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        directionalLight.move({ 0.0f, 0.0f, -0.01f });
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        directionalLight.move({ 0.0f, 0.0f, 0.01f });
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        directionalLight.move({ -0.01f, 0.0f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        directionalLight.move({ 0.01f, 0.0f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        directionalLight.move({ 0.0f, 0.01f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        directionalLight.move({ 0.0f, -0.01f, 0.0f });

    GLdouble mousePositionX, mousePositionY;
    glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
    camera.setMousePosition(mousePositionX, mousePositionY);
}
