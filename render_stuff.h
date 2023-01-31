//----------------------------------------------------------------------------------------
/**
 * \file    reder_stuff.h
 * \author  Lebedev Daniil
 * \date    2022
 * \brief   Helper functions for render
 */
 //----------------------------------------------------------------------------------------

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

#include "data.h"
#include "ShaderGen.h"
#include "Model.h"
#include "Mesh.h"
#include "stb_image.h"
using namespace std;


vector <Mesh> windows;
// Models
struct Models {
    Model houseModel;
    Model policeCarModel;
    Model trashBinModel;
    Model treeModel;
    Model plantModel;
    Model tableModel;
    Model frootsModel;
    Model stoolModel;
    Model paintingModel;
    Model couchModel;
    Model coffeeTableModel;
    Model loungeChair;
    Model bedModel;
    Model chairModel;
    Model modernTableModel;
    Model terroristModel;
    Model terroristModel1;
    Model terroristModel2;
    Model policeManModel;
    Model lampModel;
    Model wallLampModel;
    Model backpack;
};
Models models;

// Functions prototypes
void render_scene(Models models, vector<Mesh>windows, ShaderGen& sceneShader);

void load_models();
void draw_house(Models models, ShaderGen sceneShader);
void draw_lamps(Models models, ShaderGen sceneShader);
void draw_trash_bin(Models models, ShaderGen sceneShader);
void draw_tree(Models models, ShaderGen sceneShader);
void draw_police_car(Models models, ShaderGen sceneShader);
void draw_plants(Models models, ShaderGen sceneShader);
void draw_interior(ShaderGen sceneShader, Models models);
void draw_terrorists(Models models, ShaderGen sceneShader);
void draw_windows(vector<Mesh> windows, ShaderGen sceneShader);
void draw_police_mans(Models models, ShaderGen shader);

unsigned int init_skybox();
void draw_skybox(ShaderGen skyboxShader, unsigned int skyboxVAO, unsigned int skyboxTexture, glm::mat4 view, glm::mat4 projection);
unsigned int loadCubemap(vector<std::string> faces);

void setLight(ShaderGen& shader, glm::vec3 lightDir, Camera &camera, float Kl, float Kq);
void setMaterials(ShaderGen& shader, glm::vec3 ambnt, glm::vec3 diff, glm::vec3 spec, float shinniness);
unsigned int load_texture(const char* path, bool png);

unsigned int initDuckBuffers();
unsigned int initButterflyBuffers();
unsigned int initTableBuffers();

void draw_butterfly(ShaderGen butterflyShader, unsigned int butterflyVAO, unsigned int butterflyTexture, glm::mat4 view, glm::mat4 projection);
void draw_duck(ShaderGen duckShader, unsigned int duckVAO, unsigned int duckTexture, glm::mat4 view, glm::mat4 projection);
void draw_table(ShaderGen tableShader, unsigned int tableVAO, unsigned int tableTexture);


/// Load texture 
/**
  Function that load texture and returns id of texture

  \param[in] path where texture is stored.
  \param[in] png flag for png textures.
*/
unsigned int load_texture(const char* path, bool png)
{
    // Flip textures
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        if (png)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(false);
    return texture;
}


/// Init models 
/**
  Function that inits models from structure models
*/
void load_models()
{
    int sharedId1 = 0;
    models.houseModel.init(houseModelpath, sharedId1++);
    models.policeCarModel.init(policeCarModelpath, sharedId1++);
    models.trashBinModel.init(trashBinModelpath, sharedId1++);
    models.treeModel.init(treeModelpath, sharedId1++);
    models.plantModel.init(plantsModelpath, sharedId1++);
    models.tableModel.init(tableModelpath, sharedId1++);
    models.frootsModel.init(frootsModelpath, sharedId1++);
    models.stoolModel.init(chairModelpath, sharedId1++);
    models.paintingModel.init(paintingModelpath, sharedId1++);
    models.couchModel.init(couchModelpath, sharedId1++);
    models.coffeeTableModel.init(coffeeTableModelpath, sharedId1++);
    models.loungeChair.init(loungeModelpath, sharedId1++);
    models.bedModel.init(bedModelpath, sharedId1++);
    models.chairModel.init(moderChairModelpath, sharedId1++);
    models.modernTableModel.init(modernTableModelpath, sharedId1++);
    //models.terroristModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\red_01.obj", sharedId1++);
    //models.terroristModel1.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\red_02.obj", sharedId1++);
    //models.terroristModel2.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\red_03.obj", sharedId1++);
    //models.policeManModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\police_man.obj", sharedId1++);
    models.lampModel.init(lampModelpath, sharedId1++);
    //models.wallLampModel.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\wall_lamp.obj", sharedId1++);
    windows = models.houseModel.getWindows();
    //models.backpack.init("C:\\Users\\daniil.lebedev\\Desktop\\MANSION\\backpack.obj");

}
/// Init skybox 
/**
  Function that setup buffers for skybox and return skyboxVAO
*/
unsigned int init_skybox()
{
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    return skyboxVAO;
}

/// Draw skybox 
/**
  Function that draw skybox

  \param[in] skyboxShader activates shader.
  \param[in] skyboxVAO bind VAO.
  \param[in] skyboxTexture bind texture.
  \param[in] view model.
  \param[in] projection model.

*/
void draw_skybox(ShaderGen skyboxShader, unsigned int skyboxVAO, unsigned int skyboxTexture, glm::mat4 view, glm::mat4 projection)
{
    glDepthFunc(GL_LEQUAL);
    skyboxShader.use();
    glm::mat4 viewSky = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, &viewSky[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

/// Load cubemap
/**
  Function that load and bind skybox faces

  \param[in] faces vector with paths for skybox faces.
*/
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

/// Set materials
/**
  Function that set unifrom parametrs for materials in fragment shader

  \param[in] shader set uniform parametrs.
  \param[in] ambnt ambient vector.
  \param[in] diff diffuse vector.
  \param[in] spec specular vector.
  \param[in] shinniness value.
*/
void setMaterials(ShaderGen& shader, glm::vec3 ambnt, glm::vec3 diff, glm::vec3 spec, float shinniness)
{
    glUniform1f(glGetUniformLocation(shader.ID, "material1.shininess" ), shinniness);
    glUniform3fv(glGetUniformLocation(shader.ID, "material1.ambient"), 1, &ambnt[0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "material1.diffuse"), 1, &diff[0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "material1.specular"), 1, &spec[0]);
}

/// Set lights
/**
  Function that set unifrom parametrs for diffrent types of light in fragment shader

  \param[in] shader set uniform parametrs.
  \param[in] lightDir light direction.
  \param[in] camera camera spec.
  \param[in] Kl linear value for attenuation.
  \param[in] Kq quadratic value for attenuation.
*/
void setLight(ShaderGen& shader, glm::vec3 lightDir, Camera &camera, float Kl, float Kq)
{
    // Set directional lights uniforms
    glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.direction"), 1, &lightDir[0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.ambient"), 1, &lightDirAmbient[0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.diffuse"), 1, &lightDirDiffuse[0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.specular"), 1, &lightDirSpecular[0]);

    // Set lighter uniforms
    glUniform1i(glGetUniformLocation(shader.ID, "lighterEnable"), (int)lighterEnable);
    glUniform1f(glGetUniformLocation(shader.ID, "cutOffLighter"), cutOffLighter);
    
    glUniform3fv(glGetUniformLocation(shader.ID, "viewPos"), 1, &camera.Position[0]);
    glUniform3fv(glGetUniformLocation(shader.ID, "cameraDir"), 1, &camera.Front[0]);

    // Enable/Disable fog
    glUniform1i(glGetUniformLocation(shader.ID, "fogEnable"), (int)fogEnable);

    // Enable point lights 
   // glUniform1i(glGetUniformLocation(shader.ID, "disableSpot"), (int)true);
    glUniform1i(glGetUniformLocation(shader.ID, "disableSpot"), (int)false);

    // Set point lights uniforms
    string tmp;
    for (int i = 0; i < N_POINT_LIGHTS; i++)
    {
        string pos = "pointLights[].position";
        string kc = "pointLights[].Kc";
        string kl = "pointLights[].Kl";
        string kq = "pointLights[].Kq";
        string ambient = "pointLights[].ambient";
        string diffuse = "pointLights[].diffuse";
        string specular = "pointLights[].specular";
        string cut = "pointLights[].cutOff";
        string dir = "pointLights[].direction";


        pos.insert(12, to_string(i));
        kc.insert(12, to_string(i));
        kl.insert(12, to_string(i));
        kq.insert(12, to_string(i));
        ambient.insert(12, to_string(i));
        diffuse.insert(12, to_string(i));
        specular.insert(12, to_string(i));
        cut.insert(12, to_string(i));
        dir.insert(12, to_string(i));

        glm::vec3 pointLightPos = pointLightPositions[i];
        glUniform3fv(glGetUniformLocation(shader.ID, pos.c_str()), 1, &pointLightPos[0]);
        glUniform3fv(glGetUniformLocation(shader.ID, dir.c_str()), 1, &pointLightDir[0]);
        // Set attenuation
        glUniform1f(glGetUniformLocation(shader.ID, kc.c_str()), 1.0f);
        glUniform1f(glGetUniformLocation(shader.ID, kl.c_str()), Kl);
        glUniform1f(glGetUniformLocation(shader.ID, kq.c_str()), Kq);
        glUniform1f(glGetUniformLocation(shader.ID, cut.c_str()), glm::cos(glm::radians(pointLightCutOff)));


        glUniform3fv(glGetUniformLocation(shader.ID, ambient.c_str()), 1, &lightPointAmbient[0]);
        glUniform3fv(glGetUniformLocation(shader.ID, diffuse.c_str()), 1, &lightPointDiffuse[0]);
        glUniform3fv(glGetUniformLocation(shader.ID, specular.c_str()), 1, &lightPointSpecular[0]);
    }
}

/// Draw scene
/**
  Function that cals draw functions of objects in scene

  \param[in] shader set uniform parametrs.
*/
void render_scene(ShaderGen sceneShader)
{
    // Model render
    draw_house(models, sceneShader);
    draw_windows(windows, sceneShader);
 
  //  draw_lamps(models, sceneShader);
  //  draw_trash_bin(models, sceneShader);

       // Tree 
   // draw_tree(models, sceneShader);

    // Police car 1
 //   draw_police_car(models, sceneShader);


    // Plants
 //   draw_plants(models, *sceneShader);

  //  draw_interior(*sceneShader, models);

 //   draw_terrorists(models, *sceneShader);

//    draw_police_mans(models, *sceneShader);
}


/// Draw static
/**
  Function that cals static objects in scene

  \param[in] models struct with models.
  \param[in] shader set uniform parametrs.
*/
void draw_house(Models models, ShaderGen sceneShader)
{
    // Hardcode materials off
    glUniform1i(glGetUniformLocation(sceneShader.ID, "hardcode"), (int)disableHardcode);
    // House model
    glm::mat4 sceneModel = glm::mat4(1.0f);
    sceneModel = glm::translate(sceneModel, housePos);
    sceneModel = glm::scale(sceneModel, houseSize);
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &sceneModel[0][0]);
    glUniform1i(glGetUniformLocation(sceneShader.ID, "draw_windows"), (int)defaultAlpha);
    setMaterials(sceneShader, perlAmbient, perlDiffuse, perlSpecular, perlShininess); // Perl
    models.houseModel.Draw(sceneShader);
    
    // Lamps models
    for (int lamp = 0; lamp < lampPositions.size(); lamp++)
    {
        glm::mat4 lampModel = glm::mat4(1.0f);
        lampModel = glm::translate(lampModel, lampPositions[lamp]);
        lampModel = glm::scale(lampModel, glm::vec3(0.005f, 0.005f, 0.005f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &lampModel[0][0]);
        setMaterials(sceneShader, silverAmbient, silverDiffuse, silverSpecular, silverShininess); //Silver 
        models.lampModel.Draw(sceneShader);
    }

    // Table model
    setMaterials(sceneShader, defaultAmbient, defaultDiffuse, defaultSpecular, defaultShininess);
    glm::mat4 tableMod = glm::mat4(1.0f);
    tableMod = glm::translate(tableMod, tablePos);
    tableMod = glm::scale(tableMod, glm::vec3(0.6f, 0.6f, 0.6f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &tableMod[0][0]);
    models.tableModel.Draw(sceneShader);

    
    // Froots model
    glm::mat4 frootsMod = glm::mat4(1.0f);
    frootsMod = glm::translate(frootsMod, frootsPos);
    frootsMod = glm::scale(frootsMod, glm::vec3(0.02f, 0.02f, 0.02f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &frootsMod[0][0]);
    models.frootsModel.Draw(sceneShader);
    
    // Chairs model
   // glStencilFunc(GL_ALWAYS, 0, -1);
    for (int chair = 0; chair < chairsPostion.size(); chair++)
    {
        glm::mat4 stoolMod = glm::mat4(1.0f);
        stoolMod = glm::translate(stoolMod, chairsPostion[chair]);
        stoolMod = glm::scale(stoolMod, glm::vec3(0.0003f, 0.0003f, 0.0003f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &stoolMod[0][0]);
        models.stoolModel.Draw(sceneShader);
    }


    // Painting model
    glStencilFunc(GL_ALWAYS, models.paintingModel.ID, -1);
    // If user click on picture, tear it
    if (!tearPicture)
    {
        glm::mat4 paintingMod = glm::mat4(1.0f);
        paintingMod = glm::translate(paintingMod, glm::vec3(2.0f, 0.01f, 0.1f));
        paintingMod = glm::rotate(paintingMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        paintingMod = glm::scale(paintingMod, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &paintingMod[0][0]);

        models.paintingModel.Draw(sceneShader);
    }
    
    glDisable(GL_STENCIL_TEST);

    // Couch model
   // glStencilFunc(GL_ALWAYS, 0, -1);
    glm::mat4 couchMod = glm::mat4(1.0f);
    couchMod = glm::translate(couchMod, couchPos);
    couchMod = glm::scale(couchMod, glm::vec3(0.3f, 0.3f, 0.3f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &couchMod[0][0]);
    models.couchModel.Draw(sceneShader);

    // Coffee table model
    glm::mat4 coffeeTableMod = glm::mat4(1.0f);
    coffeeTableMod = glm::translate(coffeeTableMod, coffeeTablePos);
    coffeeTableMod = glm::scale(coffeeTableMod, glm::vec3(0.3f, 0.3f, 0.3f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &coffeeTableMod[0][0]);
    models.coffeeTableModel.Draw(sceneShader);

    // Lounge chair model
    for (int lounge = 0; lounge < loungeChairPositions.size(); lounge++)
    {
        setMaterials(sceneShader, copperAmbient, copperDiffuse, copperSpecular, copperShininess);
        glm::mat4 loungeСhair = glm::mat4(1.0f);
        loungeСhair = glm::translate(loungeСhair, loungeChairPositions[lounge]);
        loungeСhair = glm::scale(loungeСhair, glm::vec3(0.3f, 0.3f, 0.3f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &loungeСhair[0][0]);
        models.loungeChair.Draw(sceneShader);
    }
    
    // Bed model
    for (int bed = 0; bed < bedPositions.size(); bed++)
    {
        setMaterials(sceneShader, bedAmbient, bedDiffuse, bedSpecular, bedShininess);
        glm::mat4 bedMod = glm::mat4(1.0f);
        bedMod = glm::translate(bedMod, bedPositions[bed]);
        bedMod = glm::scale(bedMod, glm::vec3(0.3f, 0.3f, 0.3f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &bedMod[0][0]);
        models.bedModel.Draw(sceneShader);
    }


    // Hardcode materials on
    glUniform1i(glGetUniformLocation(sceneShader.ID, "hardcode"), (int)enableHardcode);

    // Modern table model
    glm::mat4 modernTableMod = glm::mat4(1.0f);
    modernTableMod = glm::translate(modernTableMod, modernTablePos);
    modernTableMod = glm::rotate(modernTableMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modernTableMod = glm::scale(modernTableMod, glm::vec3(0.3f, 0.3f, 0.3f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &modernTableMod[0][0]);
    models.modernTableModel.Draw(sceneShader);

    // Modern chair model
    glm::mat4 chairMod = glm::mat4(1.0f);
    chairMod = glm::translate(chairMod, modernChairPos);
    chairMod = glm::rotate(chairMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    chairMod = glm::scale(chairMod, glm::vec3(0.3f, 0.3f, 0.3f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &chairMod[0][0]);
    models.chairModel.Draw(sceneShader);

    // Bin model
    glm::mat4 binModel = glm::mat4(1.0f);
    binModel = glm::translate(binModel, binPos);
    binModel = glm::scale(binModel, glm::vec3(0.0009f, 0.0009f, 0.0009f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &binModel[0][0]);
    models.trashBinModel.Draw(sceneShader);

    // Tree models
    for (int tree = 0; tree < treePositions.size(); tree++)
    {
        glm::mat4 treeMod = glm::mat4(1.0f);
        treeMod = glm::translate(treeMod, treePositions[tree]);
        treeMod = glm::scale(treeMod, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &treeMod[0][0]);
        models.treeModel.Draw(sceneShader);
    }

    // Plant Models
    for (int plant = 0; plant < plantsPositions.size(); plant++)
    {
        glm::mat4 plantMod = glm::mat4(1.0f);
        plantMod = glm::translate(plantMod, plantsPositions[plant]);
        plantMod = glm::rotate(plantMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        plantMod = glm::scale(plantMod, glm::vec3(0.0005f, 0.0005f, 0.0005f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &plantMod[0][0]);
        models.plantModel.Draw(sceneShader);
    }


    glEnable(GL_STENCIL_TEST);
    // Police car model
    glm::mat4 carModel = glm::mat4(1.0f);
    carModel = glm::translate(carModel, policeCarPos);
    carModel = glm::rotate(carModel, glm::radians(290.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    carModel = glm::scale(carModel, glm::vec3(0.3f, 0.3f, 0.3f));
    glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &carModel[0][0]);


    glStencilFunc(GL_ALWAYS, models.policeCarModel.ID, -1);
    models.policeCarModel.Draw(sceneShader);
}

/// Draw windows
/**
  Function that draw static windows in scene

  \param[in] windows vector.
  \param[in] sceneShader set uniform parametrs.
*/
void draw_windows(vector<Mesh> windows, ShaderGen sceneShader)
{
    /*
    for (map<float, Mesh>::reverse_iterator it = sorted_windows_pos.rbegin(); it != sorted_windows_pos.rend(); ++it)
    {
        auto window = it->second;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        sceneShader.setMat4("model", model);
        sceneShader.setBool("draw_windows", true);
        window.Draw(sceneShader);
    }
    */


    for (auto window : windows)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, windowsPos);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(sceneShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        glUniform1i(glGetUniformLocation(sceneShader.ID, "draw_windows"), (int)windowsAlpha);

        // Unclickable
        glStencilFunc(GL_ALWAYS, 0, -1);
        window.Draw(sceneShader);
    }
    // Draw other object with normal alpha 
    glUniform1i(glGetUniformLocation(sceneShader.ID, "draw_windows"), (int)defaultAlpha);
}

/// Draw table
/**
  Function that draw table

  \param[in] tableShader activates shader and set uniforms.
  \param[in] tableVAO bind VAO.
  \param[in] tableTexture bind texture.
  \param[in] view model.
  \param[in] projection model.

*/
void draw_table(ShaderGen tableShader, unsigned int tableVAO, unsigned int tableTexture)
{
    tableShader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, tableStartPos);
    model = glm::scale(model, tableSize);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(tableShader.ID, "model"), 1, GL_FALSE, &model[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tableTexture);
    glBindVertexArray(tableVAO);
    glDrawElements(GL_TRIANGLES, cube_002NTriangles * 3, GL_UNSIGNED_INT, 0);

}

/// Draw duck
/**
  Function that draw duck

  \param[in] duckShader activates shader and set uniforms.
  \param[in] duckVAO bind VAO.
  \param[in] duckTexture bind texture.
  \param[in] view model.
  \param[in] projection model.

*/
void draw_duck(ShaderGen duckShader, unsigned int duckVAO, unsigned int duckTexture, glm::mat4 view, glm::mat4 projection)
{
    duckShader.use();
    glUniformMatrix4fv(glGetUniformLocation(duckShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(duckShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);


    glm::mat4 model = glm::mat4(1.0f);
    float rot = sin(glfwGetTime()) * speedOfRotation;
    model = glm::translate(model, duckStartPos);
    
    if (start_animate_duck)
    {
        model = glm::translate(model, glm::vec3(sin(glfwGetTime()) * 0.08f, 0.01f, 4.0f));
    }
    else
        model = glm::translate(model, duckWaitiingPos);
    model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, duckSize);
    glUniformMatrix4fv(glGetUniformLocation(duckShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
    glm::vec2 shiftCoords = glm::vec2(0.0f, sin(glfwGetTime()) * 0.02f);
    glUniform2fv(glGetUniformLocation(duckShader.ID, "TexShift"), 1, &shiftCoords[0]);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, duckTexture);
    glBindVertexArray(duckVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

/// Draw butterfly
/**
  Function that draw butterfly

  \param[in] butterflyShader activates shader and set uniforms.
  \param[in] butterflyVAO bind VAO.
  \param[in] butterflyTexture bind texture.
  \param[in] view model.
  \param[in] projection model.

*/
void draw_butterfly(ShaderGen butterflyShader, unsigned int butterflyVAO, unsigned int butterflyTexture, glm::mat4 view, glm::mat4 projection)
{
    butterflyShader.use();
    glUniformMatrix4fv(glGetUniformLocation(butterflyShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(butterflyShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, butterflyPos2);
    model = glm::scale(model, butterflySize);
    for (int i = 0; i < 1; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(3);
        float x = 0.1f * glm::cos(theta);
        float y = 0.1f * glm::sin(theta);
        float angle = 20.0f * 1;
        model = glm::translate(model, glm::vec3(cos(glfwGetTime() * 0.2f) + x, sin(glfwGetTime() * 0.2f) + y, 0.0f));
        angle = glfwGetTime() * 9.0f;
        model = glm::rotate(model, glm::radians(angle), butterflyRot);
        glUniformMatrix4fv(glGetUniformLocation(butterflyShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        glUniform1f(glGetUniformLocation(butterflyShader.ID, "time"), sin(deltaTime * speedAnimation));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, butterflyTexture);
        glBindVertexArray(butterflyVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    }
}



/// Set buffers for duck object
/**
  Function that setup VAO, VBO buffers for duck object and return VAO
*/
unsigned int initDuckBuffers()
{
    unsigned int duckVBO, duckVAO;

    glGenVertexArrays(1, &duckVAO);
    glGenBuffers(1, &duckVBO);

    glBindVertexArray(duckVAO);

    glBindBuffer(GL_ARRAY_BUFFER, duckVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    return duckVAO;
}

/// Set buffers for butterfly object
/**
  Function that setup VAO, VBO buffers for butterfly object and return VAO
*/
unsigned int initButterflyBuffers()
{
    unsigned int butterflyVBO, butterflyVAO;

    glGenVertexArrays(1, &butterflyVAO);
    glGenBuffers(1, &butterflyVBO);

    glBindVertexArray(butterflyVAO);

    glBindBuffer(GL_ARRAY_BUFFER, butterflyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    return butterflyVAO;
}

/// Set buffers for table object
/**
  Function that setup VAO, VBO and EBO buffers for table object and return VAO
*/
unsigned int initTableBuffers()
{
    unsigned int tableVBO, tableVAO, tableEBO;
     
    glGenVertexArrays(1, &tableVAO);
    glGenBuffers(1, &tableVBO);
    glGenBuffers(1, &tableEBO);

    glBindVertexArray(tableVAO);

    glBindBuffer(GL_ARRAY_BUFFER, tableVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_002Vertices), cube_002Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tableEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_002Triangles), cube_002Triangles, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
    return tableVAO;
}

// Unused draw functions of static objects
/*
void draw_tree(Models models, ShaderGen sceneShader)
{
    glm::mat4 treeMod = glm::mat4(1.0f);
    treeMod = glm::translate(treeMod, glm::vec3(-7.0f, 0.06f, 7.0f));
    treeMod = glm::scale(treeMod, glm::vec3(0.2f, 0.2f, 0.2f));
    sceneShader.setMat4("model", treeMod);
    sceneShader.setUInt("gObjectIndex", 12);
    models.treeModel.Draw(sceneShader);

    glm::mat4 treeMod1 = glm::mat4(1.0f);
    treeMod1 = glm::translate(treeMod1, glm::vec3(-7.0f, 0.06f, -7.0f));
    treeMod1 = glm::scale(treeMod1, glm::vec3(0.2f, 0.2f, 0.2f));
    sceneShader.setMat4("model", treeMod1);
    sceneShader.setUInt("gObjectIndex", 13);
    models.treeModel.Draw(sceneShader);

    glm::mat4 treeMod2 = glm::mat4(1.0f);
    treeMod2 = glm::translate(treeMod2, glm::vec3(6.0f, 0.06f, 6.0f));
    treeMod2 = glm::scale(treeMod2, glm::vec3(0.2f, 0.2f, 0.2f));
    sceneShader.setMat4("model", treeMod2);
    sceneShader.setUInt("gObjectIndex", 14);
    models.treeModel.Draw(sceneShader);
}


void draw_trash_bin(Models models, ShaderGen sceneShader)
{
    glm::mat4 binModel = glm::mat4(1.0f);
    binModel = glm::translate(binModel, glm::vec3(2.7f, 0.03f, -1.88f));
    binModel = glm::scale(binModel, glm::vec3(0.0009f, 0.0009f, 0.0009f));
    sceneShader.setMat4("model", binModel);
    sceneShader.setUInt("gObjectIndex", 0);
    models.trashBinModel.Draw(sceneShader);
}


void draw_plants(Models models, ShaderGen sceneShader)
{
    glm::mat4 plantMod = glm::mat4(1.0f);
    plantMod = glm::translate(plantMod, glm::vec3(-2.7f, 0.0f, 3.0f));
    plantMod = glm::rotate(plantMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    plantMod = glm::scale(plantMod, glm::vec3(0.0005f, 0.0005f, 0.0005f));
    sceneShader.setMat4("model", plantMod);
    sceneShader.setUInt("gObjectIndex", 17);
    models.plantModel.Draw(sceneShader);

    glm::mat4 plantMod2 = glm::mat4(1.0f);
    plantMod2 = glm::translate(plantMod2, glm::vec3(2.7f, 0.0f, 3.0f));
    plantMod2 = glm::rotate(plantMod2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    plantMod2 = glm::scale(plantMod2, glm::vec3(0.0005f, 0.0005f, 0.0005f));
    sceneShader.setMat4("model", plantMod2);
    sceneShader.setUInt("gObjectIndex", 18);
    models.plantModel.Draw(sceneShader);
}


void draw_police_car(Models models, ShaderGen policeCarShader)
{
    glStencilFunc(GL_ALWAYS, models.policeCarModel.ID, -1);
    glm::mat4 carModel = glm::mat4(1.0f);
    carModel = glm::translate(carModel, glm::vec3(0.0f, 0.05f, -6.0f));
    carModel = glm::rotate(carModel, glm::radians(290.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    carModel = glm::scale(carModel, glm::vec3(0.3f, 0.3f, 0.3f));
    policeCarShader.setMat4("model", carModel);
    policeCarShader.setUInt("gObjectIndex", 15);
    models.policeCarModel.Draw(policeCarShader);
    /*
    glm::mat4 carModel1 = glm::mat4(1.0f);
    carModel1 = glm::translate(carModel1, glm::vec3(3.0f, 0.05f, -3.7f));
    carModel1 = glm::rotate(carModel1, glm::radians(300.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    carModel1 = glm::scale(carModel1, glm::vec3(0.3f, 0.3f, 0.3f));
    policeCarShader.setMat4("model", carModel1);
    policeCarShader.setUInt("gObjectIndex", 16);
    models.policeCarModel.Draw(policeCarShader);
 
}


void draw_interior(ShaderGen sceneShader,
    Models models)
{
   
    glm::mat4 tableMod = glm::mat4(1.0f);
    tableMod = glm::translate(tableMod, glm::vec3(-2.0f, 0.05f, -0.7f));
    tableMod = glm::scale(tableMod, glm::vec3(0.6f, 0.6f, 0.6f));
    sceneShader.setMat4("model", tableMod);
    sceneShader.setUInt("gObjectIndex", 19);
    models.tableModel.Draw(sceneShader);


 
    glm::mat4 frootsMod = glm::mat4(1.0f);
    frootsMod = glm::translate(frootsMod, glm::vec3(-1.7f, 0.35f, -0.7f));
    frootsMod = glm::scale(frootsMod, glm::vec3(0.02f, 0.02f, 0.02f));
    sceneShader.setMat4("model", frootsMod);
    sceneShader.setUInt("gObjectIndex", 20);
    models.frootsModel.Draw(sceneShader);


    glm::mat4 stoolMod = glm::mat4(1.0f);
    stoolMod = glm::translate(stoolMod, glm::vec3(-2.0f, 0.1f, -0.5f));
    stoolMod = glm::scale(stoolMod, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod);
    sceneShader.setUInt("gObjectIndex", 21);
    models.stoolModel.Draw(sceneShader);

    glm::mat4 stoolMod1 = glm::mat4(1.0f);
    stoolMod1 = glm::translate(stoolMod1, glm::vec3(-1.2f, 0.1f, -0.5f));
    stoolMod1 = glm::scale(stoolMod1, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod1);
    sceneShader.setUInt("gObjectIndex", 22);
    models.stoolModel.Draw(sceneShader);


    glm::mat4 stoolMod2 = glm::mat4(1.0f);
    stoolMod2 = glm::translate(stoolMod2, glm::vec3(-2.0f, 0.1f, -0.9f));
    stoolMod2 = glm::scale(stoolMod2, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod2);
    sceneShader.setUInt("gObjectIndex", 23);
    models.stoolModel.Draw(sceneShader);


    glm::mat4 stoolMod3 = glm::mat4(1.0f);
    stoolMod3 = glm::translate(stoolMod3, glm::vec3(-1.2f, 0.1f, -0.9f));
    stoolMod3 = glm::scale(stoolMod3, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod3);
    sceneShader.setUInt("gObjectIndex", 24);
    models.stoolModel.Draw(sceneShader);


 
    glm::mat4 paintingMod = glm::mat4(1.0f);
    paintingMod = glm::translate(paintingMod, glm::vec3(2.0f, 0.01f, 0.1f));
    paintingMod = glm::rotate(paintingMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    paintingMod = glm::scale(paintingMod, glm::vec3(0.5f, 0.5f, 0.5f));
    sceneShader.setMat4("model", paintingMod);
    sceneShader.setUInt("gObjectIndex", 25);
    models.paintingModel.Draw(sceneShader);


    glm::mat4 couchMod = glm::mat4(1.0f);
    couchMod = glm::translate(couchMod, glm::vec3(2.0f, 0.0f, 0.59f));
    couchMod = glm::scale(couchMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", couchMod);
    sceneShader.setUInt("gObjectIndex", 26);
    models.couchModel.Draw(sceneShader);


    glm::mat4 coffeeTableMod = glm::mat4(1.0f);
    coffeeTableMod = glm::translate(coffeeTableMod, glm::vec3(2.0f, 0.03f, 0.59f));
    coffeeTableMod = glm::scale(coffeeTableMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", coffeeTableMod);
    sceneShader.setUInt("gObjectIndex", 27);
    models.coffeeTableModel.Draw(sceneShader);

    glm::mat4 loungeСhair = glm::mat4(1.0f);
    loungeСhair = glm::translate(loungeСhair, glm::vec3(2.0f, 0.03f, 2.5f));
    loungeСhair = glm::scale(loungeСhair, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", loungeСhair);
    sceneShader.setUInt("gObjectIndex", 28);
    models.loungeChair.Draw(sceneShader);

    glm::mat4 loungeСhair1 = glm::mat4(1.0f);
    loungeСhair1 = glm::translate(loungeСhair1, glm::vec3(-1.0f, 0.03f, 3.5f));
    loungeСhair1 = glm::rotate(loungeСhair1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    loungeСhair1 = glm::scale(loungeСhair1, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", loungeСhair1);
    sceneShader.setUInt("gObjectIndex", 29);
    models.loungeChair.Draw(sceneShader);

    glm::mat4 bedMod = glm::mat4(1.0f);
    bedMod = glm::translate(bedMod, glm::vec3(2.5f, 0.93f, -0.95f));
    bedMod = glm::scale(bedMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", bedMod);
    sceneShader.setUInt("gObjectIndex", 30);
    models.bedModel.Draw(sceneShader);

    glm::mat4 bedMod2 = glm::mat4(1.0f);
    bedMod2 = glm::translate(bedMod2, glm::vec3(-2.5f, 0.93f, -0.95f));
    bedMod2 = glm::scale(bedMod2, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", bedMod2);
    sceneShader.setUInt("gObjectIndex", 31);
    models.bedModel.Draw(sceneShader);


    glm::mat4 modernTableMod = glm::mat4(1.0f);
    modernTableMod = glm::translate(modernTableMod, glm::vec3(-1.7f, 0.93f, -0.95f));
    modernTableMod = glm::rotate(modernTableMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modernTableMod = glm::scale(modernTableMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", modernTableMod);
    sceneShader.setUInt("gObjectIndex", 34);
    models.modernTableModel.Draw(sceneShader);

    glm::mat4 chairMod = glm::mat4(1.0f);
    chairMod = glm::translate(chairMod, glm::vec3(-1.7f, 0.93f, -0.95f));
    chairMod = glm::rotate(chairMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    chairMod = glm::scale(chairMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", chairMod);
    sceneShader.setUInt("gObjectIndex", 35);
    models.chairModel.Draw(sceneShader);
}

void draw_police_mans(Models models, ShaderGen shader)
{
    glm::mat4 policeMan = glm::mat4(1.0f);
    policeMan = glm::translate(policeMan, glm::vec3(3.0f, 0.0f, 3.0f));
    policeMan = glm::scale(policeMan, glm::vec3(0.16f, 0.16f, 0.16f));
    shader.setMat4("model", policeMan);
    shader.setUInt("gObjectIndex", 39);
    models.policeManModel.Draw(shader);
}

void draw_terrorists(Models models, ShaderGen shader)
{
    glm::mat4 terrorModel = glm::mat4(1.0f);
    terrorModel = glm::translate(terrorModel, glm::vec3(0.0f, 0.0f, 3.0f));
    terrorModel = glm::scale(terrorModel, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", terrorModel);
    shader.setUInt("gObjectIndex", 36);
    models.terroristModel.Draw(shader);

    glm::mat4 terrorModel1 = glm::mat4(1.0f);
    terrorModel1 = glm::translate(terrorModel1, glm::vec3(1.0f, 0.0f, 3.0f));
    terrorModel1 = glm::scale(terrorModel1, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", terrorModel1);
    shader.setUInt("gObjectIndex", 37);
    models.terroristModel.Draw(shader);

    glm::mat4 terrorModel2 = glm::mat4(1.0f);
    terrorModel2 = glm::translate(terrorModel2, glm::vec3(2.0f, 0.0f, 3.0f));
    terrorModel2 = glm::scale(terrorModel2, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", terrorModel2);
    shader.setUInt("gObjectIndex", 38);
    models.terroristModel.Draw(shader);
}

void draw_lamps(Models models, ShaderGen shader)
{
    glm::mat4 lampKitchen = glm::mat4(1.0f);
    lampKitchen = glm::translate(lampKitchen, glm::vec3(-1.70f, 0.83f, -0.7f));
    lampKitchen = glm::scale(lampKitchen, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampKitchen);
    shader.setUInt("gObjectIndex", 1);
    models.lampModel.Draw(shader);

    glm::mat4 lampNearStairs = glm::mat4(1.0f);
    lampNearStairs = glm::translate(lampNearStairs, glm::vec3(1.70f, 0.85f, -0.7f));
    lampNearStairs = glm::scale(lampNearStairs, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampNearStairs);
    shader.setUInt("gObjectIndex", 2);
    models.lampModel.Draw(shader);


    glm::mat4 lampVestibuleLeft = glm::mat4(1.0f);
    lampVestibuleLeft = glm::translate(lampVestibuleLeft, glm::vec3(-1.70f, 0.85f, 0.7f));
    lampVestibuleLeft = glm::scale(lampVestibuleLeft, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setUInt("gObjectIndex", 3);
    shader.setMat4("model", lampVestibuleLeft);
    models.lampModel.Draw(shader);


    glm::mat4 lampVestibuleRight = glm::mat4(1.0f);
    lampVestibuleRight = glm::translate(lampVestibuleRight, glm::vec3(1.70f, 0.85f, 0.7f));
    lampVestibuleRight = glm::scale(lampVestibuleRight, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampVestibuleRight);
    shader.setUInt("gObjectIndex", 4);
    models.lampModel.Draw(shader);


    glm::mat4 lampVestibuleMiddle = glm::mat4(1.0f);
    lampVestibuleMiddle = glm::translate(lampVestibuleMiddle, glm::vec3(0.00f, 0.85f, 0.7f));
    lampVestibuleMiddle = glm::scale(lampVestibuleMiddle, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampVestibuleMiddle);
    shader.setUInt("gObjectIndex", 5);
    models.lampModel.Draw(shader);


    glm::mat4 lampSecondFloorLeftFirst = glm::mat4(1.0f);
    lampSecondFloorLeftFirst = glm::translate(lampSecondFloorLeftFirst, glm::vec3(-1.70f, 1.85f, -0.7f));
    lampSecondFloorLeftFirst = glm::scale(lampSecondFloorLeftFirst, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorLeftFirst);
    shader.setUInt("gObjectIndex", 6);
    models.lampModel.Draw(shader);


    glm::mat4 lampSecondFloorRightFirst = glm::mat4(1.0f);
    lampSecondFloorRightFirst = glm::translate(lampSecondFloorRightFirst, glm::vec3(1.70f, 1.85f, -0.7f));
    lampSecondFloorRightFirst = glm::scale(lampSecondFloorRightFirst, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorRightFirst);
    shader.setUInt("gObjectIndex", 7);
    models.lampModel.Draw(shader);


    glm::mat4 lampSecondFloorLeftSecond = glm::mat4(1.0f);
    lampSecondFloorLeftSecond = glm::translate(lampSecondFloorLeftSecond, glm::vec3(-1.70f, 1.85f, 0.7f));
    lampSecondFloorLeftSecond = glm::scale(lampSecondFloorLeftSecond, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorLeftSecond);
    shader.setUInt("gObjectIndex", 8);
    models.lampModel.Draw(shader);


    glm::mat4 lampSecondFloorRightSecond = glm::mat4(1.0f);
    lampSecondFloorRightSecond = glm::translate(lampSecondFloorRightSecond, glm::vec3(1.70f, 1.85f, 0.7f));
    lampSecondFloorRightSecond = glm::scale(lampSecondFloorRightSecond, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorRightSecond);
    shader.setUInt("gObjectIndex", 9);
    models.lampModel.Draw(shader);


    glm::mat4 lampSecondFloorMiddle = glm::mat4(1.0f);
    lampSecondFloorMiddle = glm::translate(lampSecondFloorMiddle, glm::vec3(0.00f, 1.85f, 0.93f));
    lampSecondFloorMiddle = glm::scale(lampSecondFloorMiddle, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorMiddle);
    shader.setUInt("gObjectIndex", 10);
    models.lampModel.Draw(shader);

    /*
    glm::mat4 wallLampRightOutside = glm::mat4(1.0f);
    wallLampRightOutside = glm::translate(wallLampRightOutside, glm::vec3(3.03f, 1.5f, 1.2f));
    wallLampRightOutside = glm::rotate(wallLampRightOutside, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampRightOutside = glm::rotate(wallLampRightOutside, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampRightOutside = glm::scale(wallLampRightOutside, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampRightOutside);
    wallLampModel.Draw(shader);

    glm::mat4 wallLampRightOutside1 = glm::mat4(1.0f);
    wallLampRightOutside1 = glm::translate(wallLampRightOutside1, glm::vec3(3.03f, 1.5f, -1.2f));
    wallLampRightOutside1 = glm::rotate(wallLampRightOutside1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampRightOutside1 = glm::rotate(wallLampRightOutside1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampRightOutside1 = glm::scale(wallLampRightOutside1, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampRightOutside1);
    wallLampModel.Draw(shader);

    glm::mat4 wallLampLeftOutside = glm::mat4(1.0f);
    wallLampLeftOutside = glm::translate(wallLampLeftOutside, glm::vec3(-3.03f, 1.5f, 1.2f));
    wallLampLeftOutside = glm::rotate(wallLampLeftOutside, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampLeftOutside = glm::rotate(wallLampLeftOutside, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampLeftOutside = glm::scale(wallLampLeftOutside, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampLeftOutside);
    wallLampModel.Draw(shader);

    glm::mat4 wallLampLeftOutside1 = glm::mat4(1.0f);
    wallLampLeftOutside1 = glm::translate(wallLampLeftOutside1, glm::vec3(-3.03f, 1.5f, -1.2f));
    wallLampLeftOutside1 = glm::rotate(wallLampLeftOutside1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampLeftOutside1 = glm::rotate(wallLampLeftOutside1, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampLeftOutside1 = glm::scale(wallLampLeftOutside1, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampLeftOutside1);
    wallLampModel.Draw(shader);


    glm::mat4 wallLampRightBottomOutside = glm::mat4(1.0f);
    wallLampRightBottomOutside = glm::translate(wallLampRightBottomOutside, glm::vec3(3.03f, 0.5f, 1.2f));
    wallLampRightBottomOutside = glm::rotate(wallLampRightBottomOutside, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampRightBottomOutside = glm::rotate(wallLampRightBottomOutside, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampRightBottomOutside = glm::scale(wallLampRightBottomOutside, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampRightBottomOutside);
    wallLampModel.Draw(shader);

    glm::mat4 wallLampRightBottomOutside1 = glm::mat4(1.0f);
    wallLampRightBottomOutside1 = glm::translate(wallLampRightBottomOutside1, glm::vec3(3.03f, 0.5f, -1.2f));
    wallLampRightBottomOutside1 = glm::rotate(wallLampRightBottomOutside1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampRightBottomOutside1 = glm::rotate(wallLampRightBottomOutside1, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampRightBottomOutside1 = glm::scale(wallLampRightBottomOutside1, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampRightBottomOutside1);
    wallLampModel.Draw(shader);

    glm::mat4 wallLampLeftBottomOutside = glm::mat4(1.0f);
    wallLampLeftBottomOutside = glm::translate(wallLampLeftBottomOutside, glm::vec3(-3.03f, 0.5f, 1.2f));
    wallLampLeftBottomOutside = glm::rotate(wallLampLeftBottomOutside, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampLeftBottomOutside = glm::rotate(wallLampLeftBottomOutside, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampLeftBottomOutside = glm::scale(wallLampLeftBottomOutside, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampLeftBottomOutside);
    wallLampModel.Draw(shader);

    glm::mat4 wallLampLeftBottomOutside1 = glm::mat4(1.0f);
    wallLampLeftBottomOutside1 = glm::translate(wallLampLeftBottomOutside1, glm::vec3(-3.03f, 0.5f, -1.2f));
    wallLampLeftBottomOutside1 = glm::rotate(wallLampLeftBottomOutside1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    wallLampLeftBottomOutside1 = glm::rotate(wallLampLeftBottomOutside1, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    wallLampLeftBottomOutside1 = glm::scale(wallLampLeftBottomOutside1, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", wallLampLeftBottomOutside1);
    wallLampModel.Draw(shader);
    
}
*/

