#ifndef TEXTURE_ASSET_H
#define TEXTURE_ASSET_H

#include <glad/glad.h>

#include "../Asset.h"


class TextureAsset : public Asset {
protected:
    GLuint m_texture;

protected:
    explicit TextureAsset();

public:
    [[nodiscard]] GLuint getTexture() const;
};


#endif //TEXTURE_ASSET_H
