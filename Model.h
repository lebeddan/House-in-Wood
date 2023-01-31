//----------------------------------------------------------------------------------------
/**
 * \file    Model.h
 * \author  Lebedev Daniil
 * \date    2022
 * \brief   A class that load and draw 3D model using Assimp
 */
 //----------------------------------------------------------------------------------------

#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shadergen.h"
#include "data.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

/// Class that holds info about model.
class Model
{
public:
     
    // Model data
    int ID;///<ID of model
    vector<Texture> textures_loaded;///<textures_loaded from mtl file
    vector<Mesh> meshes;///<meshes of model
    string directory;///<directory where model stored 

   /// Constructor
   /**
       Default constructor
    */
    Model() { }

    /// Init model
    /**
      Function that initialize model
      
      \param[in] path to model.
      \param[in] id of model.
    */
    void init(string const& path, int id);

    /// Draw model
    /**
      Function that call Draw() function in mesh class

      \param[in] shader requiers for Draw() function in mesh class.
    */
    void Draw(ShaderGen shader);

    /// Get windows
    /**
      Helper function that returns vector meshes of windo
    */
    vector<Mesh> getWindows();

private:
    vector<Mesh> meshes_of_windows;///<meshes_of_windows vector contains meshes of windows

    
    ///Load models and save meshes in vector
    /**
      Function that load model from assimp library

     \param[in] path where model is stored.
    */
    void loadModel(string const& path);

    
    /// Recursive process node
    /**
      Function that recursive process nodes of model and stored mesh info in mesh vector

      \param[in] node current node of model.
      \param[in] scene loaded model.
    */
    void processNode(aiNode* node, const aiScene* scene);

    /// Procces mesh in scene
    /**
      Function that extract info about processed mesh and return mesh object

      \param[in] mesh current mesh of model.
      \param[in] scene loaded model.
    */
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    /// Check all textures of materials of the specified type and load textures if they have not been loaded yet
    /**
      Function that loaded textures with materials from model

      \param[in] mat material of model.
      \param[in] type texture type of model.
      \param[in] typeName of texture.
    */
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

    /// Load textures
    /**
      Function that loaded and return textures from .mtl file

      \param[in] path where texture is stored.
      \param[in] directory of model where stored .mtl file.
      \param[in] gamma of texture.
    */
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

};



void Model::init(string const& path, int id)
{
    ID = id;
    loadModel(path);
}


void Model::Draw(ShaderGen shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    { 
        meshes[i].Draw(shader);
    }
}


void Model::loadModel(string const& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
   
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR ASSIMP: " << importer.GetErrorString() << endl;
        return;
    }

    
    //Get file direction
    directory = path.substr(0, path.find_last_of('\\'));

    processNode(scene->mRootNode, scene);
}


void Model::processNode(aiNode* node, const aiScene* scene)
{

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {

        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];  
      

        string tmp = (string)mesh->mName.data;
        // This is necessary to separate the windows from the model of the house
        if (tmp != back_window_bottom_left_name && tmp != back_window_bottom_middle_name &&
            tmp != back_window_bottom_rightest_name && tmp != back_window_top_rightest_name &&
            tmp != back_window_top_miidle_name && tmp != back_window_top_left_name &&
            tmp != front_window_top_left_name && tmp != front_window_top_middle_name &&
            tmp != front_window_top_right_name && tmp != door_window_front_left_name &&
            tmp != front_windows_bottom_name && tmp != door_window_front_right_name &&
            tmp != front_window10 && tmp != door_window_top_right_teracce &&
            tmp != door_window_top_right_teracce2 && tmp != door_window_top_left_teracce &&
            tmp != door_window_top_left_teracce2 && tmp != water)
        {
            meshes.push_back(processMesh(mesh, scene));
        }
        else
        {
            meshes_of_windows.push_back(processMesh(mesh, scene));
        }
        
    }


    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}


Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        // Vertices
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        //Texture coors
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // Tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // Bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);



        // IsMaterials? 
        if (scene->mNumMaterials > mesh->mMaterialIndex)
        {
            const auto& mat = scene->mMaterials[mesh->mMaterialIndex];
            aiColor4D diffuse;
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            {
                vertex.color = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
            }

            if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                vertex.useDiffuseTexture = 1.f;
            }
            else
            {
                vertex.useDiffuseTexture = 0.f;
            }
        }

        vertices.push_back(vertex);
    }

    //Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //Materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // Diffuse map
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Specular map
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    
    // Normal map
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // Height map
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures, mesh->mName);
}


vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        // Skip if textures materils are none
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}


unsigned int Model::TextureFromFile(const char* path, const string& directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '\\' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, depth;
    bool texture_alpha = false;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &depth, 0);
    if (data)
    {
        // Texture type 
        GLenum format;
        if (depth == 1)
            format = GL_RED;
        else if (depth == 2)
            format = GL_RG;
        else if (depth == 3)
            format = GL_RGB;
        else if (depth == 4)
        {
            format = GL_RGBA;
            texture_alpha = true;
            //cout << "ALHPA" << endl;
            //cout << filename.c_str() << endl;
        }
            
        else if (depth == 0 || depth > 4) throw std::runtime_error("invalid depth");

        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        
        if (texture_alpha)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            cout << "BIND ALPHA TEXTURE" << endl;
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

vector<Mesh> Model::getWindows()
{
    return meshes_of_windows;
}

#endif
