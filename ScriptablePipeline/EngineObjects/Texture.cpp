//
// Created by tsaury on 14/03/2022.
//

#include "Texture.h"
#include "../../helper/stb_image.h"
#include <filesystem>
#include "../../helper/find_exe_path.h"

Texture::Texture(const char* filepath) {

    filesystem::path appPath(GetAppPath());
    filesystem::path appDir = appPath.parent_path();
    filesystem::path imgPath = appDir / "Images";
    filesystem::path modelPath = imgPath / filepath;
    texels = stbi_load(modelPath.string().c_str(), &width, &height, &channels, 0);
    if(!texels){
        printf("Couldn't load %s\n", filepath);
    }
}

Texture::Texture() {
    texels = new unsigned char[] {0,0,0};
    width = 1;
    height = 1;
    channels = 3;
}

Texture::~Texture() {

}

void Texture::bind(){

    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);

    glGenerateMipmap(GL_TEXTURE_2D);

}

void Texture::select(GLuint shaderID) const {

    GLuint textureID = glGetUniformLocation(shaderID, "TextureSampler");
    glUniform1i(textureID, 0);

}
