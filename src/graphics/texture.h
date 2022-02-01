#ifndef VOX_TEXTURE_H
#define VOX_TEXTURE_H

#include <glad/glad.h>
#include <string>

#include "../util/log.h"

struct Texture
{
    unsigned int m_id;

    int m_width, m_height, m_channels;
    Texture() = default;
    /* Type must  be one of "PNG", "JPEG", "JPG" */
    Texture(const std::string& path, const std::string& type);

    inline void Bind()
    {
        if (m_id == 0)
        {
            Logger::Warn("Cannot bind texture, m_id not inititalized!");
            return;
        }
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    inline void Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    inline void Destroy()
    {
        glDeleteTextures(1, &m_id);
        m_id = m_width = m_height = m_channels = 0;
    }
};

#endif
