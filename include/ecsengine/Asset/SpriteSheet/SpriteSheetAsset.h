#ifndef SPRITE_SHEET_ASSET_H
#define SPRITE_SHEET_ASSET_H

#include <string>
#include <string_view>
#include <unordered_map>

#include "../Asset.h"
#include "TextureRegion.h"


class SpriteSheetAsset : public Asset {
protected:
    std::unordered_map<std::string, TextureRegion> m_sprites;

protected:
    explicit SpriteSheetAsset() = default;

public:
    [[nodiscard]] const TextureRegion& getTextureRegion(std::string_view name) const;
};


#endif //SPRITE_SHEET_ASSET_H
