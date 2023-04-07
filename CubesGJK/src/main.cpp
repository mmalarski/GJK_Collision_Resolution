#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Light.h"
#include "Shader.h"

#define WINDOW_WIDTH    1020
#define WINDOW_HEIGHT   860

void processInput(GLFWwindow* window, Camera& camera, Light& directionalLight, Cube& cube);
void update(Cube& cube, Light& pointLight);
void render(GLFWwindow* window, Camera& camera, Shader& basicShader, Shader& lightSourceShader, Cube& cube, Cube& cube2, Light& pointLight);
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
    glClearColor(0.88f, 0.88f, 0.88f, 1.0f);
    glfwSetCursorPos(window, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    
    Camera camera(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    Light pointLight({ 0.0f, 0.0f, 1.0f });
    Cube cube({ -0.6f, 0.0f, 0.0f });
    Cube cube2({ 0.6f, 0.0f, 0.0f });
    Shader basicShader("res/shaders/basic.shader");
    Shader lightSourceShader("res/shaders/lightSource.shader");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(
            window, 
            camera, 
            pointLight, 
            cube);
        
        update(
            cube,
            pointLight
        );
        
        render(
            window, 
            camera, 
            basicShader, 
            lightSourceShader, 
            cube, 
            cube2, 
            pointLight);
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera, Light& pointLight, Cube& cube)
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
        pointLight.moveWithVector({ 0.0f, 0.0f, -0.01f });
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        pointLight.moveWithVector({ 0.0f, 0.0f, 0.01f });
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        pointLight.moveWithVector({ -0.01f, 0.0f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        pointLight.moveWithVector({ 0.01f, 0.0f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        pointLight.moveWithVector({ 0.0f, 0.01f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        pointLight.moveWithVector({ 0.0f, -0.01f, 0.0f });

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        cube.moveWithVector(glm::vec3({0.0f, 0.0f, -0.001f}));
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        cube.moveWithVector(glm::vec3({ 0.0f, 0.0f, 0.001f }));
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        cube.moveWithVector(glm::vec3({ -0.001f, 0.0f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
        cube.moveWithVector(glm::vec3({ 0.001f, 0.0f, 0.0f }));

    GLdouble mousePositionX, mousePositionY;
    glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
    camera.setMousePosition(mousePositionX, mousePositionY);
}

void update(Cube& cube, Light& pointLight)
{
    cube.resolveMovement();
    pointLight.resolveMovement();
}

void render(GLFWwindow* window, Camera& camera, Shader& basicShader, Shader& lightSourceShader, Cube& cube, Cube& cube2, Light& pointLight)
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader::setViewAndProjection(camera.getViewMatrix(), glm::perspective(glm::radians(camera.getZoom()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.01f, 100.0f));

    basicShader
        .use()
        .setUniform("model", cube.getModelMatrix())
        .setUniform("view", Shader::getViewMatrix())
        .setUniform("projection", Shader::getProjectionMatrix())
        .setUniform("u_Color", cube.getColor())
        .setUniform("directionalLight", pointLight.getPosition());

    cube.render();
    pointLight.render(lightSourceShader);

    basicShader
        .use()
        .setUniform("model", cube2.getModelMatrix())
        .setUniform("u_Color", cube2.getColor());

    cube2.render();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}