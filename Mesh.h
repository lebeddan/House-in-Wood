//----------------------------------------------------------------------------------------
/**
 * \file    Mesh.h
 * \author  Lebedev Daniil
 * \date    2022
 * \brief   A class that represent data of model
 */
 //----------------------------------------------------------------------------------------


#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shadergen.h" 

#include <string>
#include <vector>
using namespace std;

// Data of vertex
struct Vertex {

    glm::vec3 Position;///<Position vector of vertex in local space
    glm::vec3 Normal;///<Normal vector of normals of vertex
    glm::vec2 TexCoords;///<TexCoords vector of vertex

    glm::vec4 color;///<color vector of vertex
    float useDiffuseTexture;///<useDiffuseTexture if there is one

    glm::vec3 Tangent;///<Tangent vector of vertex
    glm::vec3 Bitangent;///<Bitangent vector of vertex
};

// Data of texture
struct Texture {
    unsigned int id;///<id of texture
    string type;///<type of texture
    string path;///<path of texture
};

/// Class that holds info about mesh.
class Mesh {
public:
    // Mesh data
    vector<Vertex> vertices;///<vertices of mesh
    vector<unsigned int> indices;///<indices of mesh
    vector<Texture> textures;///<textures of mesh
    aiString mesh_name;///<mesh_name
    unsigned int VAO;///<VAO of mesh

    /// Constructor
    /**
      Constructor used vetrices, indices, textures and mesh_name

      \param[in] vertices vector.
      \param[in] indices vector.
      \param[in] textures vector.
      \param[in] mesh_name name of mesh.
    */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, aiString mesh_name);
    
    /// Mesh render
    /**
      Function that start draw mesh
      
      \param[in] shader to bind textures in fragment shader.
    */
    void Draw(ShaderGen& shader);

private:
    
    // Data for rendering
    unsigned int VBO, EBO;

    
    /// Init all buffers
    /**
      Function that initialize and setup VAO,VBO and EBO buffers
    */
    void setupMesh();
};



Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, aiString mesh_name)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->mesh_name = mesh_name;

    setupMesh();
}

void Mesh::Draw(ShaderGen& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        
        // Before binding, activate the desired texture unit
        glActiveTexture(GL_TEXTURE0 + i);
        //Get num of texture
        
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        // Bind texture
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
  

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    // Genetate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind buffers
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertices coord
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    //Texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    //Tangent vector
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    //Bitangent vector
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Clean
    glBindVertexArray(0);
}
#endif