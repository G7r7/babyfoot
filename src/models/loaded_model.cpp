#include "loaded_model.hpp"
#include <glad/glad.h>
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
    texturesNb = model->getTexturesLength();
    textures = (unsigned int*)malloc(sizeof(unsigned int)*texturesNb);
    glGenTextures(texturesNb, textures);  

    // We bind the generated texture to the current context
    // Loading the date in the texture we created
    // 0 is the mipmap level for wich we are creating a texture
    // GL_RGB is the format in wich we store the data
    // other 0 is legacy
    // GL_RGB format of source
    // GL_UNSIGNED_BYTE datatype of source
    // We also generate automatically the associated mipmap

    for (int i = 0; i < texturesNb; i++)
    {
        Texture tex = model->getTextures()[i];
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.getWidth(), tex.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, tex.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    }
}

void LoadedModel::Bind() {
    for (int i = 0; i < texturesNb; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
}

LoadedModel::~LoadedModel() {
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
    free(textures);
    free(VAO);
    free(VBO);
    free(EBO);
}