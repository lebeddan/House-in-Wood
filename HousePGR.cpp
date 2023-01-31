//----------------------------------------------------------------------------------------
/**
 * \file    HousePGR.cpp
 * \author  Lebedev Daniil
 * \date    2022
 * \brief   Main file
 */
 //----------------------------------------------------------------------------------------

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <irrKlang/irrKlang.h>

#include "ShaderGen.h"
#include "camera.h"
#include "Model.h"
#include "Mesh.h"
#include "render_stuff.h"
#include "glm/gtx/string_cast.hpp"
#include "data.h"
#include "stb_image.h"

using namespace irrklang;

// Functions prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
void setCallbacks(GLFWwindow* window);
bool checkCollisions(glm::vec3 pos);
float updateTime();
void myGLFWInit();
void enableTests();
bool initOpenGlFunc();

// Camera
Camera camera(cameraStartPos);

// Sound engine for sound effects
ISoundEngine* soundEngine = createIrrKlangDevice();


int main()
{
    // glfw: Init
    myGLFWInit();

    // glfw: Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "House", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return MY_ERROR_RET;
    }
    
    // Set callback functions
    setCallbacks(window);

    // glad: Init OpenGl functions
    auto error = initOpenGlFunc();
    if (error) return MY_ERROR_RET;
    
    // Enable depth, stecil tests and setup blend
    enableTests();

    // Setup shader programs
    ShaderGen sceneShader(coreVSpath, coreFSpath);
    ShaderGen skyboxShader(skyboxVSpath, skyboxFSpath);
    ShaderGen duckShader(duckVSpath, duckFSpath);
    ShaderGen butterflyShader(butterflyVSpath, butterflyFSpath);    
    
    // Setup buffers for dynamical objects
    auto duckVAO = initDuckBuffers();
    auto butterflyVAO = initButterflyBuffers();
    
    auto tableVAO = initTableBuffers();// < ---- object with 30+ triangles
  
    // Setup textures for dynamical objects
    auto duckTex = load_texture(textureDuck, pngFileEnable);
    auto butterflyTex = load_texture(textureButterfly, pngFileEnable);

    auto tableTex = load_texture(textureTable, pngFileDisable);

    // Setup skybox
    auto skyboxTexture = loadCubemap(skyboxFacesPaths);
    auto skyboxVAO = init_skybox();

    
    //  Sort windows depend on distance from camera

    /*
    map<float, Mesh> sorted_windows_pos;
    unsigned int i = 0;
    for (auto e : windows)
    {
        cout << i << endl;
        glm::vec3 pos = glm::vec3(0.0f);
        vector<Vertex> vertices = e.vertices;
        for (unsigned int j = 0; j < vertices.size(); j++)
        {
           // cout << glm::to_string(vertices[j].Position) << endl;
        }
        i++;
       // cout << glm::to_string(pos) << endl;
    }
    */
    
    // Define textures in fragment shader
    skyboxShader.use();
    glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

    duckShader.use();
    glUniform1i(glGetUniformLocation(duckShader.ID, "texture_diffuse1"), 0);

    butterflyShader.use();
    glUniform1i(glGetUniformLocation(butterflyShader.ID, "texture_diffuse1"), 0);
    
    // Init models
    load_models();   

    // Render
    while (!glfwWindowShouldClose(window))
    {
       // glClearStencil(0);
        
        // Update frames
        auto currentFrame = updateTime();

        processInput(window);

        // Clear window and buffers
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Calc projection and view models
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
        glm::mat4 view = camera.GetViewMatrix();
        

        // Draw skybox
        glStencilFunc(GL_ALWAYS, 0, -1); // Set skybox unclickable
        draw_skybox(skyboxShader, skyboxVAO, skyboxTexture, view, projection);

         // COLLISONS OBJECT
         /*
         glm::mat4 model = glm::mat4(1.0f);
         model = glm::translate(model, glm::vec3(-0.6f, 0.5f, 4.0f));
         glm::vec3 newPos = buttefrlyPos + glm::vec3(sin(glfwGetTime() * 1.0f), 0.5f, 1.5f);
         if (checkCollisions(newPos))
         {
             model = glm::translate(model, buttefrlyPos);
             model = glm::translate(model, glm::vec3(sin(glfwGetTime() * 1.0f), 0.5f, 1.5f));
             stopPos = buttefrlyPos + glm::vec3(sin(glfwGetTime() * 1.0f), 0.5f, 1.5f);
         }
         else
         {
             model = glm::translate(model, stopPos);
         }

         //model = glm::translate(model, glm::vec3(sin(glfwGetTime() * 1.0f), 0.5f, 1.5f));
         model = glm::scale(model, glm::vec3(0.2f));
         butterflyShader.setMat4("model", model);
         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, butterflySprite);
         glBindVertexArray(butterflyVAO);
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
         */


        // Draw butterfly
        glStencilFunc(GL_ALWAYS, 0, -1); // Set butterfly unclickable
        draw_butterfly(butterflyShader, butterflyVAO, butterflyTex, view, projection);

        // Draw duck
        glStencilFunc(GL_ALWAYS, 21, -1); // Set duck clickable
        draw_duck(duckShader, duckVAO, duckTex, view, projection);

        glStencilFunc(GL_ALWAYS, 0, -1); 
        sceneShader.use();
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);

        // 30+ TRIANGLES
        draw_table(sceneShader, tableVAO, tableTex);
        
        // Draw scene
        render_scene(sceneShader);
        // Set lights
        setLight(sceneShader, lightDir, camera, Kl, Kq);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return MY_SUCCESS_RET;
}

/// Intilize GLFW 
/**
  Function that initnitlize glfw window contex
*/
void myGLFWInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/// Set callbacks 
/**
  Function that set callbacks from window

  \param[in] window current window.
*/
void setCallbacks(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/// Init GLAD 
/**
  Function that init GLAD to use OpenGl fucntions
*/
bool initOpenGlFunc()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return true;
    }
    return false;
}

/// Tests 
/**
  Function that enable depth, stencil tests and enable blending
*/
void enableTests()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/// Time 
/**
  Function that updates frames
*/
float updateTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    return currentFrame;
}

/// Callback keybords
/**
  Function that handels pushed keyboard buutons 
*/
void processInput(GLFWwindow* window)
{
    // Exit 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // WASD control
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime, true);
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime, false);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime, true);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime, false);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime, false);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime, false);
    // Enable/Disable lighter
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        NlKeyPress++;
        if (NlKeyPress == 2)
        {
            lighterEnable = false;
            NlKeyPress = 0;
        }
        else
            lighterEnable = true;
    }
    // Enable/Disable fog
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        NfKeyPress++;
        if (NfKeyPress == 2)
        {
            fogEnable = false;
            NfKeyPress = 0;
        }
        else
            fogEnable = true;
    }
    // Change static cameras by arrows    
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camera.updatePosition(n_static_view);
        n_static_view++;
        firstMouse = true;
        if (n_static_view == 4) n_static_view = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera.updatePosition(n_static_view);
        n_static_view--;
        firstMouse = true;
        if (n_static_view < 0) n_static_view = 3;
    }
}

/// Viewport
/**
  Function that updates framebuffers size, when user change resoluton of window
  
  \param[in] window current window.
  \param[in] width of window.
  \param[in] height of window.

*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/// Mouse callback
/**
  Function that handels mouse position on window and update offsets for mouse moving 

  \param[in] window current window.
  \param[in] xpos on X axis in window.
  \param[in] ypos on Y axis in window.

*/
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = (float)xpos - lastX;
    float yoffset = lastY -(float) ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

/// Scrloll callback
/**
  Function that handels scrolls and update offsets for mouse zooming

  \param[in] window current window.
  \param[in] xoffset
  \param[in] yoffset

*/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

/// Mouse button callback
/**
  Function that handels mouse click and start interacte with clickable object

  \param[in] window current window.
  \param[in] button pressed button
  \param[in] action state of button.
  \param[in] mods modifier bits.

*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        
        unsigned char ID = 0;
        // Read pixels from stencil buffer to get ID of object
        glReadPixels(xpos, SCR_HEIGHT - 1 - ypos, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &ID);

        if (ID == 0)
        {
            cout << "BACKGROUND" << endl;
        }
        else
        {
            // Click on police car model, play audio effect
            if (ID == models.policeCarModel.ID)
                soundEngine->play2D(startCar, false);
            // Click on duck, start animate
            else if (ID == DUCK_ID)
            {
                start_animate_duck = true;
                cout << "hi" << endl;
            }
            // Click on painting model, play audio effect and stop drawing model
            else if (ID == models.paintingModel.ID)
            {
                tearPicture = true;
                soundEngine->play2D(tearPainting, false);
            }
                
            cout << "CLICK " << ID << endl;
        }
    }
}

/*
void init_models()
{
    int sharedId1 = 0;
    models.houseModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\house.obj", sharedId1++);
    models.policeCarModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\police car.obj", sharedId1++);
    models.trashBinModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\outdoor_bin.obj", sharedId1++);
    models.treeModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\tree.obj", sharedId1++);
    models.plantModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\Dieffenbachia_Plants.obj", sharedId1++);
    models.tableModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\wooden_table.obj", sharedId1++);
    models.frootsModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\Fruits pack.obj", sharedId1++);
    models.stoolModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\Counter Stool.obj", sharedId1++);
    models.paintingModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\painting1.obj", sharedId1++);
    models.couchModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\Couch.obj", sharedId1++);
    models.coffeeTableModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\CoffeeTable.obj", sharedId1++);
    models.loungeChair.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\lounge_chair.obj", sharedId1++);
    models.bedModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\Bed.obj", sharedId1++);
    models.chairModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\FabricChair.obj", sharedId1++);
    models.modernTableModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\ModernTable.obj", sharedId1++);
    models.terroristModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\red_01.obj", sharedId1++);
    models.terroristModel1.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\red_02.obj", sharedId1++);
    models.terroristModel2.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\red_03.obj", sharedId1++);
    models.policeManModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\police_man.obj", sharedId1++);
    models.lampModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\house_lamp.obj", sharedId1++);
    models.wallLampModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\wall_lamp.obj", sharedId1++);
}
*/

/// Collisions
/**
  Function check if object does not go beyond the boundaries of the scene

  \param[in] pos position of object.
*/
bool checkCollisions(glm::vec3 pos)
{
    if (pos.x > sceneInfo.x || pos.x < -sceneInfo.x) return false;

    if (pos.y > sceneInfo.y || pos.y < -sceneInfo.y) return false;

    if (pos.z > sceneInfo.z || pos.z < -sceneInfo.z) return false;

    return true;
}