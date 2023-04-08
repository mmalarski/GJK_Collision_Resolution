#include "Camera.h"
#include "CubeManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GJKCollisionChecker.h"
#include <iostream>
#include "Light.h"
#include "LightManager.h"
#include "Line.h"
#include "LineManager.h"
#include "Shader.h"

#define WINDOW_WIDTH    1020
#define WINDOW_HEIGHT   860

struct GameLoop
{
    GLint64 previousTime;
    GLint64 currentTime;
    GLint64 elapsedTime;
    GLint64 deltaTime;
    const GLint64 SECONDS_PER_FRAME = 1 / 60;
};

enum Lines
{
    DIRECTION,
    XAXIS,
	YAXIS,
	ZAXIS,
	NUM_LINES
};

enum Cubes
{
	MOVING,
	STATIC,
	NUM_CUBES
};

void processInput(
    GLFWwindow* window, 
    Camera& camera,
    CubeManager& cubeManager);
void update(
    GLint64& deltaTime,
    CubeManager& cubeManager,
    LightManager& lightManager, 
    LineManager& lineManager,
    GJKCollisionChecker& gjk);
void render(
    GLFWwindow* window, 
    Camera& camera, 
    Shader& basicShader, 
    Shader& lightSourceShader, 
    Shader& lineShader, 
    CubeManager& cubeManager,
    LightManager& lightManager, 
    LineManager& lineManager,
    GJKCollisionChecker& gjk);

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
    glLineWidth(2.0f);
    glfwSetCursorPos(window, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    
    Camera camera(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    
    Cube cube({ -1.0f, 0.6f, 0.0f });
    Cube cube2({ 1.0f, 0.6f, 0.0f });
    CubeManager cubeManager;
	cubeManager.addCube(&cube);
	cubeManager.addCube(&cube2);
    
    Light pointLight({ 0.0f, 0.0f, 1.0f });
    Light pointLight1({ 0.0f, 0.0f, 2.0f });
	LightManager lightManager;
	lightManager.addLight(&pointLight);
	lightManager.addLight(&pointLight1);
    
    Line direction(glm::vec3(0.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
    Line xAxis(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    xAxis.setAColor(glm::vec3(0.0f));
	xAxis.setBColor(glm::vec3(1.0f, 0.0f, 0.0f));
    Line yAxis(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	yAxis.setAColor(glm::vec3(0.0f));
	yAxis.setBColor(glm::vec3(0.0f, 1.0f, 0.0f));
    Line zAxis(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	zAxis.setAColor(glm::vec3(0.0f));
	zAxis.setBColor(glm::vec3(0.0f, 0.0f, 1.0f));
    LineManager lineManager;
	lineManager.addLine(&direction);
	lineManager.addLine(&xAxis);
	lineManager.addLine(&yAxis);
	lineManager.addLine(&zAxis);

    Shader basicShader("res/shaders/basic.shader");
    Shader lightSourceShader("res/shaders/lightSource.shader");
    Shader lineShader("res/shaders/line.shader");
    
    GJKCollisionChecker gjk;
    
    GameLoop gameLoop;
    gameLoop.previousTime = glfwGetTime();
    gameLoop.deltaTime = 0.0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        gameLoop.currentTime = glfwGetTime();
        gameLoop.elapsedTime = gameLoop.currentTime - gameLoop.previousTime;
        gameLoop.previousTime = gameLoop.currentTime;
        gameLoop.deltaTime += gameLoop.elapsedTime;
        
        if (gameLoop.deltaTime >= gameLoop.SECONDS_PER_FRAME)
        {
            processInput(
                window, 
                camera, 
                cubeManager);
        
            update(
                gameLoop.deltaTime,
                cubeManager,
                lightManager,
                lineManager,
                gjk);
			gameLoop.deltaTime -= gameLoop.SECONDS_PER_FRAME;
        }
        
        render(
            window, 
            camera, 
            basicShader, 
            lightSourceShader,
            lineShader,
            cubeManager, 
			lightManager,
            lineManager,
            gjk);
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera, CubeManager& cubeManager)
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

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        cubeManager.getCubes()[0]->moveWithVector(glm::vec3({0.0f, 0.0f, -0.001f}));
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        cubeManager.getCubes()[0]->moveWithVector(glm::vec3({ 0.0f, 0.0f, 0.001f }));
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        cubeManager.getCubes()[0]->moveWithVector(glm::vec3({ -0.001f, 0.0f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
        cubeManager.getCubes()[0]->moveWithVector(glm::vec3({ 0.001f, 0.0f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        cubeManager.getCubes()[0]->moveWithVector(glm::vec3({ 0.0f, 0.001f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        cubeManager.getCubes()[0]->moveWithVector(glm::vec3({ 0.0f, -0.001f, 0.0f }));

    GLdouble mousePositionX, mousePositionY;
    glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
    camera.setMousePosition(mousePositionX, mousePositionY);
}

void update(GLint64& deltaTime, CubeManager& cubeManager, LightManager& lightManager, LineManager& lineManager, GJKCollisionChecker& gjk)
{
    lightManager.getLights()[0]->setPosition(
        gjk.findFurthestPointOnDirection(
            *cubeManager.getCubes()[MOVING],
            lineManager.getLines()[DIRECTION]->getDirection()
        )
    );
    lightManager.getLights()[1]->setPosition(
        gjk.findFurthestPointOnDirection(
			*cubeManager.getCubes()[STATIC],
            -lineManager.getLines()[DIRECTION]->getDirection()
        )
    );
    
    lineManager.getLines()[DIRECTION]->setA(glm::vec3(0.0f));
	lineManager.getLines()[DIRECTION]->setB(glm::vec3(glm::sin((float)glfwGetTime()), glm::sin((float)glfwGetTime() * 0.5f), glm::cos((float)glfwGetTime())));
    lineManager.getLines()[XAXIS]->setB(glm::vec3(glm::sin((float)glfwGetTime()), 0.0f, 0.0f));
    lineManager.getLines()[YAXIS]->setB(glm::vec3(0.0f, glm::sin((float)glfwGetTime() * 0.5f), 0.0f));
    lineManager.getLines()[ZAXIS]->setB(glm::vec3(0.0f, 0.0f, glm::cos((float)glfwGetTime())));
    
    cubeManager.resolveMovement();
}

void render(GLFWwindow* window, Camera& camera, Shader& basicShader, Shader& lightSourceShader, Shader& lineShader, CubeManager& cubeManager, LightManager& lightManager, LineManager& lineManager, GJKCollisionChecker& gjk)
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader::setViewAndProjection(camera.getViewMatrix(), glm::perspective(glm::radians(camera.getZoom()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.01f, 100.0f));
    
    cubeManager.render(basicShader, lightManager);
    lightManager.render(lightSourceShader);
	lineManager.render(lineShader);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}