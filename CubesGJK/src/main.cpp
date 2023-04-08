#include "Camera.h"
#include "CubeManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GJKCollisionChecker.h"
#include <iostream>
#include "Light.h"
#include "LightManager.h"
#include "Line.h"
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

struct Colors
{
	static glm::vec3 Red        ;   
	static glm::vec3 Green      ; 
	static glm::vec3 Blue       ;  
	static glm::vec3 Yellow     ;
	static glm::vec3 Cyan       ;  
	static glm::vec3 Magenta    ;
	static glm::vec3 White      ; 
	static glm::vec3 Black      ; 
	static glm::vec3 Orange     ;
	static glm::vec3 Purple     ;
	static glm::vec3 Brown      ; 
};

glm::vec3 Colors::Red      =   { 1.0f, 0.0f, 0.0f };
glm::vec3 Colors::Green    =   { 0.0f, 1.0f, 0.0f };
glm::vec3 Colors::Blue     =   { 0.0f, 0.0f, 1.0f };
glm::vec3 Colors::Yellow   =   { 1.0f, 1.0f, 0.0f };
glm::vec3 Colors::Cyan     =   { 0.0f, 1.0f, 1.0f };
glm::vec3 Colors::Magenta  =   { 1.0f, 0.0f, 1.0f };
glm::vec3 Colors::White    =   { 1.0f, 1.0f, 1.0f };
glm::vec3 Colors::Black    =   { 0.0f, 0.0f, 0.0f };
glm::vec3 Colors::Orange   =   { 1.0f, 0.5f, 0.0f };
glm::vec3 Colors::Purple   =   { 0.5f, 0.0f, 1.0f };
glm::vec3 Colors::Brown    =   { 0.5f, 0.25f, 0.0f };

enum Cubes
{
	MOVING_CUBE,
	STATIC_CUBE,
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
    GJKCollisionChecker& gjk);
void render(
    GLFWwindow* window, 
    Camera& camera, 
    Shader& basicShader, 
    Shader& lightSourceShader, 
    Shader& lineShader, 
    CubeManager& cubeManager,
    LightManager& lightManager, 
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
                cubeManager
            );
        
            update(
                gameLoop.deltaTime,
                cubeManager,
                lightManager,
                gjk
            );
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
            gjk
        );
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
        cubeManager[MOVING_CUBE].moveWithVector(glm::vec3({0.0f, 0.0f, -0.001f}));
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        cubeManager[MOVING_CUBE].moveWithVector(glm::vec3({ 0.0f, 0.0f, 0.001f }));
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        cubeManager[MOVING_CUBE].moveWithVector(glm::vec3({ -0.001f, 0.0f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
        cubeManager[MOVING_CUBE].moveWithVector(glm::vec3({ 0.001f, 0.0f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        cubeManager[MOVING_CUBE].moveWithVector(glm::vec3({ 0.0f, 0.001f, 0.0f }));
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        cubeManager[MOVING_CUBE].moveWithVector(glm::vec3({ 0.0f, -0.001f, 0.0f }));

    //if ctrl pressed set timescale to zero
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		glfwSetTime(0.0);

    GLdouble mousePositionX, mousePositionY;
    glfwGetCursorPos(window, &mousePositionX, &mousePositionY);
    camera.setMousePosition(mousePositionX, mousePositionY);
}

void update(GLint64& deltaTime, CubeManager& cubeManager, LightManager& lightManager, GJKCollisionChecker& gjk)
{
	glm::vec3 direction = cubeManager[STATIC_CUBE].getPosition() - cubeManager[MOVING_CUBE].getPosition();
    lightManager[MOVING_CUBE].setPosition(
        gjk.findFurthestPointOnDirection(cubeManager[MOVING_CUBE], glm::normalize(direction))
    );
    lightManager[STATIC_CUBE].setPosition(
        gjk.findFurthestPointOnDirection(cubeManager[STATIC_CUBE], -glm::normalize(direction))
    );
    
    cubeManager.resolveMovement();
}

void render(GLFWwindow* window, Camera& camera, Shader& basicShader, Shader& lightSourceShader, Shader& lineShader, CubeManager& cubeManager, LightManager& lightManager, GJKCollisionChecker& gjk)
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Shader::setViewAndProjection(camera.getViewMatrix(), glm::perspective(glm::radians(camera.getZoom()), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.01f, 100.0f));
    
    cubeManager.render(basicShader, lightManager);
    lightManager.render(lightSourceShader);    
    
    //setting the direction (the same as for lights in update())
    glm::vec3 direction = cubeManager[STATIC_CUBE].getPosition() - cubeManager[MOVING_CUBE].getPosition();
    Line::drawLine(lineShader, glm::vec3(0.0f), Colors::White, glm::normalize(direction), Colors::Magenta);
	glm::vec3 supportPoint = gjk.findSupportPoint(cubeManager[MOVING_CUBE], cubeManager[STATIC_CUBE], glm::normalize(direction));
    Line::drawLine(lineShader, glm::vec3(0.0f), Colors::White, supportPoint, Colors::White);
	Line::drawLine(lineShader, glm::vec3(0.0f), Colors::Black, glm::vec3(1.0f, 0.0f, 0.0f), Colors::Red);
	Line::drawLine(lineShader, glm::vec3(0.0f), Colors::Black, glm::vec3(0.0f, 1.0f, 0.0f), Colors::Green);
	Line::drawLine(lineShader, glm::vec3(0.0f), Colors::Black, glm::vec3(0.0f, 0.0f, 1.0f), Colors::Blue);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}