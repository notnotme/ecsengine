#ifndef TEXTURE_LOADABLE_H
#define TEXTURE_LOADABLE_H

#include <string_view>

#include "../LoadableAsset.h"
#include "TextureAsset.h"


class TextureLoadable final : public LoadableAsset<TextureAsset> {
private:
    const GLint m_repeat;

public:
    explicit TextureLoadable(GLint repeat = GL_CLAMP_TO_EDGE);

public:
    void load(std::string_view path) override;
    void unload() override;
};


#endif //TEXTURE_LOADABLE_H
