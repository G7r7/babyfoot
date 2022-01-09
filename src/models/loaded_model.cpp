#include "loaded_model.hpp"
#include <glad/glad.h>
#include "../stb_image.h"
#include <iostream>

LoadedModel::LoadedModel(Model* model) {
    // VAO : Vertex Array Object, VBO : Vertex Buffer Object, EBO: Element Buffer Object
    // These are the GPU side representation in memory of the vertices
    VAO = (unsigned int*)malloc(sizeof(unsigned int)*1);
    glGenVertexArrays(1, VAO);
    VBO = (unsigned int*)malloc(sizeof(unsigned int)*3);
    glGenBuffers(3, VBO);
    EBO = (unsigned int*)malloc(sizeof(unsigned int)*1);
    glGenBuffers(1, EBO);
    
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

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->getIndicesSize(), model->getIndices().data(), GL_STATIC_DRAW);

    // TEXTURES

    // Setting up border color for GL_CLAMP_TO_BORDER option
    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

    // Setting texture filtering : GL_NEAREST, GL_LINEAR
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setting texture mignification and magnification filtering : 
    // GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Loading the texture file
    // int width, height, nrChannels, width2, height2, nrChannels2, width3, height3, nrChannels3;
    // stbi_set_flip_vertically_on_load(true);
    // unsigned char *data = stbi_load("../src/textures/verre-sur-mesure-granite.jpg", &width, &height, &nrChannels, 0); 
    // unsigned char *data2 = stbi_load("../src/textures/rl.png", &width2, &height2, &nrChannels2, 0); 
    // unsigned char *data3 = stbi_load("../src/textures/rl2.jpg", &width3, &height3, &nrChannels3, 0); 

    // Generating the texture
    // 2 is the number of textures we generate
    // store the generated textures in an unsigned int array
    // unsigned int textures[3];
    // glGenTextures(3, textures);  


    // We bind the generated texture to the current context
    // glBindTexture(GL_TEXTURE_2D, textures[0]);
    // Loading the date in the texture we created
    // 0 is the mipmap level for wich we are creating a texture
    // GL_RGB is the format in wich we store the data
    // other 0 is legacy
    // GL_RGB format of source
    // GL_UNSIGNED_BYTE datatype of source
    // We also generate automatically the associated mipmap

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // glGenerateMipmap(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, textures[1]);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    // glGenerateMipmap(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, textures[2]);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
    // glGenerateMipmap(GL_TEXTURE_2D);

    // we can free the loaded image
    // stbi_image_free(data);
    // stbi_image_free(data2);
    // stbi_image_free(data3);

}

void LoadedModel::Bind() {
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, textures[1]);
        // glActiveTexture(GL_TEXTURE2);
        // glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
}

LoadedModel::~LoadedModel() {
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
}