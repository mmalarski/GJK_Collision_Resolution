#include "Camera.h"
#include "CubeManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Light.h"
#include "Shader.h"

#define WINDOW_WIDTH    1020
#define WINDOW_HEIGHT   860

struct GameLoop
{
    GLdouble previousTime;
    GLdouble currentTime;
    GLdouble elapsedTime;
    GLdouble deltaTime;
    const GLdouble SECONDS_PER_FRAME = 1 / 60;
};

void processInput(GLFWwindow* window, Camera& camera, Light& directionalLight, CubeManager& cubeManager, Cube& cube);

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
    Light pointLight({ 2.0f, 0.0f, 2.0f });
    CubeManager cubeManager(2, 3, 1.0f);
    Shader basicShader("res/shaders/basic.shader");
    Shader lightSourceShader("res/shaders/lightSource.shader");

    Cube cube1({ -1.0f, 2.2f, 0.0f });
    Cube cube2({ 1.0f, 2.2f, 0.2f  });
    GJKResolver gjkResolver;

    cube1
        //.setRotation(30.0f, glm::vec3(0.0f, 1.0f, 0.0f))
        .setScale(2.0f);

    /* Loop until the user closes the window */

    GameLoop gameLoop;
    GLuint64 frequency = glfwGetTimerFrequency();
    gameLoop.previousTime = glfwGetTimerValue() * 0.001;
    gameLoop.deltaTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        gameLoop.currentTime = glfwGetTimerValue() * 0.001;
        gameLoop.elapsedTime = gameLoop.currentTime - gameLoop.previousTime;
        gameLoop.previousTime = gameLoop.currentTime;
        gameLoop.deltaTime += gameLoop.elapsedTime;

        if (gameLoop.deltaTime >= gameLoop.SECONDS_PER_FRAME)
        {
            processInput(
                window, 
                camera, 
                pointLight,
                cubeManager,
                cube1);

            if (gjkResolver.areCubesColliding(cube1.simulateNextPosition(), cube2.simulateNextPosition()))
            {
                cube1.setColor({ 1.0f, 0.0f, 0.0f });
                cube2.setColor({ 1.0f, 0.0f, 0.0f });
            }
            else
            {
                cube1.resetColor();
                cube2.resetColor();
            
                cube1.applyNextMovementVectors();
                cube2.applyNextMovementVectors();
            }

            cubeManager
                .resolveCollisions((GLint64)gameLoop.elapsedTime);

            gameLoop.deltaTime -= gameLoop.SECONDS_PER_FRAME;
        }

        Shader::setViewAndProjection(camera.getViewMatrix(), glm::perspective(glm::radians(camera.getZoom()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.01f, 100.0f));
        Shader::setPointLightPosition(pointLight.getPosition());

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cubeManager.render(basicShader);
        pointLight.render(lightSourceShader);

        basicShader
            .use()
            .setUniform("view", Shader::getViewMatrix())
            .setUniform("projection", Shader::getProjectionMatrix())
            .setUniform("pointLightPosition", Shader::getPointLightPosition())
            .setUniform("u_Color", cube1.getColor())
            .setUniform("model", cube1.getModelMatrix());
        cube1.render();

        basicShader
            .use()
            .setUniform("u_Color", cube2.getColor())
            .setUniform("model", cube2.getModelMatrix());
        cube2.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera, Light& directionalLight, CubeManager& cubeManager, Cube& cube)
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

    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        cube.setNextMovementVector({ -0.001f, 0.0f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
        cube.setNextMovementVector({ 0.001f, 0.0f, 0.0f });
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        cube.setNextMovementVector({ 0.0f, 0.0f, 0.001f });
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        cube.setNextMovementVector({ 0.0f, 0.0f, -0.001f });

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        //cubeManager.setCubesForceVector(glm::vec3(0.0f, 0.05f, 0.0f));
        cubeManager.launchCubes();

    GLdouble mousePositionX, mousePositionY;
    glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
    camera.setMousePosition(mousePositionX, mousePositionY);
}