#ifndef DRAW_STATIC_MODELS_H
#define DRAW_STATIC_MODELSH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "ShaderGen.h"

void draw_house(Model house, ShaderGen sceneShader)
{
    glm::mat4 sceneModel = glm::mat4(1.0f);
    sceneModel = glm::translate(sceneModel, glm::vec3(0.0f, 0.0f, 0.0f));
    sceneModel = glm::scale(sceneModel, glm::vec3(0.5f, 0.5f, 0.5f));
    sceneShader.setMat4("model", sceneModel);
    sceneShader.setBool("draw_windows", false);
    house.Draw(sceneShader);
}

void draw_windows(vector<Mesh> windows, ShaderGen sceneShader)
{

    for (auto window : windows)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        sceneShader.setMat4("model", model);
        sceneShader.setBool("draw_windows", true);
        window.Draw(sceneShader);
    }

    sceneShader.setBool("draw_windows", false);
}

void draw_tree(Model treeModel, ShaderGen sceneShader)
{ 
    glm::mat4 treeMod = glm::mat4(1.0f);
    treeMod = glm::translate(treeMod, glm::vec3(-7.0f, 0.06f, 7.0f));
    treeMod = glm::scale(treeMod, glm::vec3(0.2f, 0.2f, 0.2f));
    sceneShader.setMat4("model", treeMod);
    treeModel.Draw(sceneShader);

    glm::mat4 treeMod1 = glm::mat4(1.0f);
    treeMod1 = glm::translate(treeMod1, glm::vec3(-7.0f, 0.06f, -7.0f));
    treeMod1 = glm::scale(treeMod1, glm::vec3(0.2f, 0.2f, 0.2f));
    sceneShader.setMat4("model", treeMod1);
    treeModel.Draw(sceneShader);

    glm::mat4 treeMod2 = glm::mat4(1.0f);
    treeMod2 = glm::translate(treeMod2, glm::vec3(6.0f, 0.06f, 6.0f));
    treeMod2 = glm::scale(treeMod2, glm::vec3(0.2f, 0.2f, 0.2f));
    sceneShader.setMat4("model", treeMod2);
    treeModel.Draw(sceneShader);
}


void draw_trash_bin(Model trashBinModel, ShaderGen sceneShader)
{
    glm::mat4 binModel = glm::mat4(1.0f);
    binModel = glm::translate(binModel, glm::vec3(2.7f, 0.03f, -1.88f));
    binModel = glm::scale(binModel, glm::vec3(0.0009f, 0.0009f, 0.0009f));
    sceneShader.setMat4("model", binModel);
    trashBinModel.Draw(sceneShader);
}


void draw_plants(Model plantModel, ShaderGen sceneShader)
{
    glm::mat4 plantMod = glm::mat4(1.0f);
    plantMod = glm::translate(plantMod, glm::vec3(-2.7f, 0.0f, 3.0f));
    plantMod = glm::rotate(plantMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    plantMod = glm::scale(plantMod, glm::vec3(0.0005f, 0.0005f, 0.0005f));
    sceneShader.setMat4("model", plantMod);
    plantModel.Draw(sceneShader);

    glm::mat4 plantMod2 = glm::mat4(1.0f);
    plantMod2 = glm::translate(plantMod2, glm::vec3(2.7f, 0.0f, 3.0f));
    plantMod2 = glm::rotate(plantMod2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    plantMod2 = glm::scale(plantMod2, glm::vec3(0.0005f, 0.0005f, 0.0005f));
    sceneShader.setMat4("model", plantMod2);
    plantModel.Draw(sceneShader);
}


void draw_police_car(Model policeCarModel, ShaderGen policeCarShader)
{
    glm::mat4 carModel = glm::mat4(1.0f);
    carModel = glm::translate(carModel, glm::vec3(0.0f, 0.05f, -6.0f));
    carModel = glm::rotate(carModel, glm::radians(290.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    carModel = glm::scale(carModel, glm::vec3(0.3f, 0.3f, 0.3f));
    policeCarShader.setMat4("model", carModel);
    policeCarModel.Draw(policeCarShader);

    glm::mat4 carModel1 = glm::mat4(1.0f);
    carModel1 = glm::translate(carModel1, glm::vec3(3.0f, 0.05f, -3.7f));
    carModel1 = glm::rotate(carModel1, glm::radians(300.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    carModel1 = glm::scale(carModel1, glm::vec3(0.3f, 0.3f, 0.3f));
    policeCarShader.setMat4("model", carModel1);
    policeCarModel.Draw(policeCarShader);
}


void draw_interior(ShaderGen sceneShader, 
    Model tableModel,
    Model frootsModel,
    Model stoolModel,
    Model paintingModel,
    Model couchModel,
    Model coffeeTableModel,
    Model loungeChairModel,
    Model bedModel,
    Model chairModel,
    Model modernTableModel)
{   
    /*
    * Table
    */
    glm::mat4 tableMod = glm::mat4(1.0f);
    tableMod = glm::translate(tableMod, glm::vec3(-2.0f, 0.05f, -0.7f));
    tableMod = glm::scale(tableMod, glm::vec3(0.6f, 0.6f, 0.6f));
    sceneShader.setMat4("model", tableMod);
    tableModel.Draw(sceneShader);
    
    
    /*
    * Froots
    */

    glm::mat4 frootsMod = glm::mat4(1.0f);
    frootsMod = glm::translate(frootsMod, glm::vec3(-1.7f, 0.35f, -0.7f));
    frootsMod = glm::scale(frootsMod, glm::vec3(0.02f, 0.02f, 0.02f));
    sceneShader.setMat4("model", frootsMod);
    frootsModel.Draw(sceneShader);

    /*
    * Chairs
    */

    glm::mat4 stoolMod = glm::mat4(1.0f);
    stoolMod = glm::translate(stoolMod, glm::vec3(-2.0f, 0.1f, -0.5f));
    stoolMod = glm::scale(stoolMod, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod);
    stoolModel.Draw(sceneShader);

    glm::mat4 stoolMod1 = glm::mat4(1.0f);
    stoolMod1 = glm::translate(stoolMod1, glm::vec3(-1.2f, 0.1f, -0.5f));
    stoolMod1 = glm::scale(stoolMod1, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod1);
    stoolModel.Draw(sceneShader);
    
    glm::mat4 stoolMod2 = glm::mat4(1.0f);
    stoolMod2 = glm::translate(stoolMod2, glm::vec3(-2.0f, 0.1f, -0.9f));
    stoolMod2 = glm::scale(stoolMod2, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod2);
    stoolModel.Draw(sceneShader);
    
    glm::mat4 stoolMod3 = glm::mat4(1.0f);
    stoolMod3 = glm::translate(stoolMod3, glm::vec3(-1.2f, 0.1f, -0.9f));
    stoolMod3 = glm::scale(stoolMod3, glm::vec3(0.0003f, 0.0003f, 0.0003f));
    sceneShader.setMat4("model", stoolMod3);
    stoolModel.Draw(sceneShader);
    

    /*
    * Painting
    */
    glm::mat4 paintingMod = glm::mat4(1.0f);
    paintingMod = glm::translate(paintingMod, glm::vec3(2.0f, 0.01f, 0.1f));
    paintingMod = glm::rotate(paintingMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    paintingMod = glm::scale(paintingMod, glm::vec3(0.5f, 0.5f, 0.5f));
    sceneShader.setMat4("model", paintingMod);
    paintingModel.Draw(sceneShader);


    glm::mat4 couchMod = glm::mat4(1.0f);
    couchMod = glm::translate(couchMod, glm::vec3(2.0f, 0.0f, 0.59f));
    couchMod = glm::scale(couchMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", couchMod);
    couchModel.Draw(sceneShader);


    glm::mat4 coffeeTableMod = glm::mat4(1.0f);
    coffeeTableMod = glm::translate(coffeeTableMod, glm::vec3(2.0f, 0.03f, 0.59f));
    coffeeTableMod = glm::scale(coffeeTableMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", coffeeTableMod);
    coffeeTableModel.Draw(sceneShader);

    glm::mat4 loungeСhair = glm::mat4(1.0f);
    loungeСhair = glm::translate(loungeСhair, glm::vec3(2.0f, 0.03f, 2.5f));
    loungeСhair = glm::scale(loungeСhair, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", loungeСhair);
    loungeChairModel.Draw(sceneShader);

    glm::mat4 loungeСhair1 = glm::mat4(1.0f);
    loungeСhair1 = glm::translate(loungeСhair1, glm::vec3(-1.0f, 0.03f, 3.5f));
    loungeСhair1 = glm::rotate(loungeСhair1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    loungeСhair1 = glm::scale(loungeСhair1, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", loungeСhair1);
    loungeChairModel.Draw(sceneShader);

    glm::mat4 bedMod = glm::mat4(1.0f);
    bedMod = glm::translate(bedMod, glm::vec3(2.5f, 0.93f, -0.95f));
    bedMod = glm::scale(bedMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", bedMod);
    bedModel.Draw(sceneShader);

    glm::mat4 bedMod2 = glm::mat4(1.0f);
    bedMod2 = glm::translate(bedMod2, glm::vec3(-2.5f, 0.93f, -0.95f));
    bedMod2 = glm::scale(bedMod2, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", bedMod2);
    bedModel.Draw(sceneShader);


    glm::mat4 modernTableMod = glm::mat4(1.0f);
    modernTableMod = glm::translate(modernTableMod, glm::vec3(-1.7f, 0.93f, -0.95f));
    modernTableMod = glm::rotate(modernTableMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modernTableMod = glm::scale(modernTableMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", modernTableMod);
    modernTableModel.Draw(sceneShader);

    glm::mat4 chairMod = glm::mat4(1.0f);
    chairMod = glm::translate(chairMod, glm::vec3(-1.7f, 0.93f, -0.95f));
    chairMod = glm::rotate(chairMod, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    chairMod = glm::scale(chairMod, glm::vec3(0.3f, 0.3f, 0.3f));
    sceneShader.setMat4("model", chairMod);
    chairModel.Draw(sceneShader);
}

void draw_police_mans(Model policeManModel, ShaderGen shader)
{
    glm::mat4 policeMan = glm::mat4(1.0f);
    policeMan = glm::translate(policeMan, glm::vec3(3.0f, 0.0f, 3.0f));
    policeMan = glm::scale(policeMan, glm::vec3(0.16f, 0.16f, 0.16f));
    shader.setMat4("model", policeMan);
    policeManModel.Draw(shader);
}

void draw_terrorists(Model terroristModel, Model terroristModel1, Model terroristModel2, ShaderGen shader)
{
    glm::mat4 terrorModel = glm::mat4(1.0f);
    terrorModel = glm::translate(terrorModel, glm::vec3(0.0f, 0.0f, 3.0f));
    terrorModel = glm::scale(terrorModel, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", terrorModel);
    terroristModel.Draw(shader);

    glm::mat4 terrorModel1 = glm::mat4(1.0f);
    terrorModel1 = glm::translate(terrorModel1, glm::vec3(1.0f, 0.0f, 3.0f));
    terrorModel1 = glm::scale(terrorModel1, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", terrorModel1);
    terroristModel1.Draw(shader);

    glm::mat4 terrorModel2 = glm::mat4(1.0f);
    terrorModel2 = glm::translate(terrorModel2, glm::vec3(2.0f, 0.0f, 3.0f));
    terrorModel2 = glm::scale(terrorModel2, glm::vec3(0.7f, 0.7f, 0.7f));
    shader.setMat4("model", terrorModel2);
    terroristModel2.Draw(shader);
}

void draw_lamps(Model lampModel, Model wallLampModel, ShaderGen shader)
{
    glm::mat4 lampKitchen = glm::mat4(1.0f);
    lampKitchen = glm::translate(lampKitchen, glm::vec3(-1.70f, 0.85f, -0.7f));
    lampKitchen = glm::scale(lampKitchen, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampKitchen);
    lampModel.Draw(shader);

    glm::mat4 lampNearStairs = glm::mat4(1.0f);
    lampNearStairs = glm::translate(lampNearStairs, glm::vec3(1.70f, 0.85f, -0.7f));
    lampNearStairs = glm::scale(lampNearStairs, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampNearStairs);
    lampModel.Draw(shader);

    glm::mat4 lampVestibuleLeft = glm::mat4(1.0f);
    lampVestibuleLeft = glm::translate(lampVestibuleLeft, glm::vec3(-1.70f, 0.85f, 0.7f));
    lampVestibuleLeft = glm::scale(lampVestibuleLeft, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampVestibuleLeft);
    lampModel.Draw(shader);

    glm::mat4 lampVestibuleRight = glm::mat4(1.0f);
    lampVestibuleRight = glm::translate(lampVestibuleRight, glm::vec3(1.70f, 0.85f, 0.7f));
    lampVestibuleRight = glm::scale(lampVestibuleRight, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampVestibuleRight);
    lampModel.Draw(shader);

    glm::mat4 lampVestibuleMiddle = glm::mat4(1.0f);
    lampVestibuleMiddle = glm::translate(lampVestibuleMiddle, glm::vec3(0.00f, 0.85f, 0.7f));
    lampVestibuleMiddle = glm::scale(lampVestibuleMiddle, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampVestibuleMiddle);
    lampModel.Draw(shader);

    glm::mat4 lampSecondFloorLeftFirst = glm::mat4(1.0f);
    lampSecondFloorLeftFirst = glm::translate(lampSecondFloorLeftFirst, glm::vec3(-1.70f, 1.85f, -0.7f));
    lampSecondFloorLeftFirst = glm::scale(lampSecondFloorLeftFirst, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorLeftFirst);
    lampModel.Draw(shader);

    glm::mat4 lampSecondFloorRightFirst = glm::mat4(1.0f);
    lampSecondFloorRightFirst = glm::translate(lampSecondFloorRightFirst, glm::vec3(1.70f, 1.85f, -0.7f));
    lampSecondFloorRightFirst = glm::scale(lampSecondFloorRightFirst, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorRightFirst);
    lampModel.Draw(shader);

    glm::mat4 lampSecondFloorLeftSecond = glm::mat4(1.0f);
    lampSecondFloorLeftSecond = glm::translate(lampSecondFloorLeftSecond, glm::vec3(-1.70f, 1.85f, 0.7f));
    lampSecondFloorLeftSecond = glm::scale(lampSecondFloorLeftSecond, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorLeftSecond);
    lampModel.Draw(shader);

    glm::mat4 lampSecondFloorRightSecond = glm::mat4(1.0f);
    lampSecondFloorRightSecond = glm::translate(lampSecondFloorRightSecond, glm::vec3(1.70f, 1.85f, 0.7f));
    lampSecondFloorRightSecond = glm::scale(lampSecondFloorRightSecond, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorRightSecond);
    lampModel.Draw(shader);

    glm::mat4 lampSecondFloorMiddle = glm::mat4(1.0f);
    lampSecondFloorMiddle = glm::translate(lampSecondFloorMiddle, glm::vec3(0.00f, 1.85f, 0.7f));
    lampSecondFloorMiddle = glm::scale(lampSecondFloorMiddle, glm::vec3(0.005f, 0.005f, 0.005f));
    shader.setMat4("model", lampSecondFloorMiddle);
    lampModel.Draw(shader);

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

#endif
