#ifndef FONT_LOADABLE_H
#define FONT_LOADABLE_H

#include <cstdint>
#include <string_view>

#include "../LoadableAsset.h"
#include "FontAsset.h"


class FontLoadable final : public LoadableAsset<FontAsset> {
private:
    const int32_t m_texture_size;
    const bool m_is_solid;
    const int32_t m_font_size;

public:
    explicit FontLoadable(int32_t fontSizePt, int32_t textureSize, bool isSolid);

public:
    void load(std::string_view path) override;
    void unload() override;
};


#endif //FONT_LOADABLE_H
