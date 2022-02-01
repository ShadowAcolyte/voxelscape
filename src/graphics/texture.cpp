#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "texture.h"

Texture::Texture(const std::string& path, const std::string& type)
{
    m_id = m_width = m_height = m_channels = 0;
    unsigned char* _data = stbi_load(path.c_str() , &m_width, &m_height, &m_channels, 0);
    if (!_data)
    {
        Logger::Error("Could not read texture file: {}", path);
        std::exit(-1);
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    if (type == "PNG")
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(_data);
    }
    else if (type == "JPG" || type == "JPEG")
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(_data);
    }
    else
    {
        Logger::Error("Unknow texture type passed into Texture constructor: {}", type);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
