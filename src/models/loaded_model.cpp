#include "loaded_model.hpp"
#include <glad/glad.h>
#include <iostream>
#include <sstream>

LoadedModel::LoadedModel(Model* model) :
    shader(model->getVertexShaderPath(), model->getFragmentShaderPath()), verticesNb(model->getVerticesNb()),
    textureData(Texture(model->getTexturePath()))
{
    // VAO : Vertex Array Object, VBO : Vertex Buffer Object, EBO: Element Buffer Object
    // These are the GPU side representation in memory of the vertices
    VAO = (unsigned int*)malloc(sizeof(unsigned int)*1);
    glGenVertexArrays(1, VAO);
    VBO = (unsigned int*)malloc(sizeof(unsigned int)*4);
    glGenBuffers(4, VBO);
    
    // bind the Vertex Array Object, then bind and set vertex buffer(s), and then configure attribute(s)
    glBindVertexArray(*VAO);

    // SETTING UP THE INPUT VARIABLES IN THE VERTEX SHADER CODE
    //positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, model->getPositionsSize(), model->getPositions().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, model->getPositionLength(), GL_FLOAT, GL_FALSE, model->getPositionSize(), (void*)0);
    glEnableVertexAttribArray(0);

    // colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, model->getColorsSize(), model->getColors().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, model->getColorLength(), GL_FLOAT, GL_FALSE, model->getColorSize(), (void*)0);
    glEnableVertexAttribArray(1);

    // texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, model->getTextureCoordinatesSize(), model->getTextureCoordinates().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, model->getTextureCoordinateLength(), GL_FLOAT, GL_FALSE, model->getTextureCoordinateSize(), (void*)0);
    glEnableVertexAttribArray(2);

    // normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, model->getNormalsSize(), model->getNormals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, model->getNormalLength(), GL_FLOAT, GL_FALSE, model->getNormalSize(), (void*)0);
    glEnableVertexAttribArray(3);

    // TEXTURES

    // Setting up border color for GL_CLAMP_TO_BORDER option
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

    // Setting texture filtering : GL_NEAREST, GL_LINEAR
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setting texture mignification and magnification filtering : 
    // GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generating the texture
    // 2 is the number of textures we generate
    // store the generated textures in an unsigned int array
    this->textureData = Texture(model->getTexturePath());
    glGenTextures(1, &texture);  

    // We bind the generated texture to the current context
    // Loading the date in the texture we created
    // 0 is the mipmap level for wich we are creating a texture
    // GL_RGB is the format in wich we store the data
    // other 0 is legacy
    // GL_RGB format of source
    // GL_UNSIGNED_BYTE datatype of source
    // We also generate automatically the associated mipmap

    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.getWidth(), textureData.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.getData());
    glGenerateMipmap(GL_TEXTURE_2D);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    setShaderInt("ourTexture", 0);
}

void LoadedModel::bind() {
    this->shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(*VAO);
}

void LoadedModel::setShaderFloat(const char * name, float value) { this->shader.setFloat(name, value); };
void LoadedModel::setShaderInt(const char * name, int value) { this->shader.setInt(name, value); };
void LoadedModel::setShaderBool(const char * name, bool value) { this->shader.setBool(name, value); };
void LoadedModel::setShaderMat4f(const char * name, glm::mat4 value) { this->shader.setMat4f(name, value); };
void LoadedModel::setShaderVec3f(const char * name, glm::vec3 value) { this->shader.setVec3f(name, value); };

void LoadedModel::draw() {
    glDrawArrays(GL_TRIANGLES, 0, this->verticesNb);
}

LoadedModel::~LoadedModel() {
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    free(VAO);
    free(VBO);
}