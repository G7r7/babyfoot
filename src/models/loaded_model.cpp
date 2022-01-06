#include "loaded_model.hpp"
#include <glad/glad.h>
#include "../stb_image.h"

LoadedModel::LoadedModel(Model* model) {
        // VAO : Vertex Array Object, VBO : Vertex Buffer Object, EBO: Element Buffer Object
    // These are the GPU side representation in memory of the vertices
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model->getVertices()), model->getVertices().data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->getIndices()), model->getIndices().data(), GL_STATIC_DRAW);

    // SETTING UP THE INPUT VARIABLES IN THE VERTEX SHADER CODE
    // for index 0 of the VAO corresponds to currently bound VBO
    // 3 corresponds to the number of elements we are reading from the buffer
    // GL_FLOAT : We're specifying the type of the data we are reading
    // GL_FALSE : not important
    // 3 * sizeof(float) : Then we specify the size of each of the element (ex: 3 floats for a vertice)  
    
    // bind the Vertex Array Object, then bind and set vertex buffer(s), and then configure attribute(s)
    glBindVertexArray(VAO);
    //positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

        // colors : last parameter is the byte offset in the array to skip the positions to get to the colors
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // texture:
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    // TEXTURES

    // Setting up border color for GL_CLAMP_TO_BORDER option
    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

    // Setting texture filtering : GL_NEAREST, GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setting texture mignification and magnification filtering : 
    // GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Loading the texture file
    int width, height, nrChannels, width2, height2, nrChannels2, width3, height3, nrChannels3;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../src/textures/verre-sur-mesure-granite.jpg", &width, &height, &nrChannels, 0); 
    unsigned char *data2 = stbi_load("../src/textures/rl.png", &width2, &height2, &nrChannels2, 0); 
    unsigned char *data3 = stbi_load("../src/textures/rl2.jpg", &width3, &height3, &nrChannels3, 0); 

    // Generating the texture
    // 2 is the number of textures we generate
    // store the generated textures in an unsigned int array
    unsigned int textures[3];
    glGenTextures(3, textures);  


    // We bind the generated texture to the current context
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    // Loading the date in the texture we created
    // 0 is the mipmap level for wich we are creating a texture
    // GL_RGB is the format in wich we store the data
    // other 0 is legacy
    // GL_RGB format of source
    // GL_UNSIGNED_BYTE datatype of source
    // We also generate automatically the associated mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
    glGenerateMipmap(GL_TEXTURE_2D);

    // we can free the loaded image
    stbi_image_free(data);
    stbi_image_free(data2);
    stbi_image_free(data3);

}

void LoadedModel::Bind() {
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, textures[0]);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, textures[1]);
        // glActiveTexture(GL_TEXTURE2);
        // glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

LoadedModel::~LoadedModel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}