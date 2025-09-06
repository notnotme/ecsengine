#ifndef TEXTURE_LOADABLE_H
#define TEXTURE_LOADABLE_H

#include <string_view>

#include "../LoadableAsset.h"
#include "TextureAsset.h"


class TextureLoadable final : public LoadableAsset<TextureAsset> {
public:
    TextureLoadable() = default;

public:
    void load(std::string_view path) override;
    void unload() override;
};


#endif //TEXTURE_LOADABLE_H
