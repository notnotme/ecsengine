#ifndef SPRITE_SHEET_LOADABLE_H
#define SPRITE_SHEET_LOADABLE_H

#include <string_view>

#include "../LoadableAsset.h"
#include "SpriteSheetAsset.h"


class SpriteSheetLoadable final : public LoadableAsset<SpriteSheetAsset> {
public:
    SpriteSheetLoadable() = default;

public:
    void load(std::string_view path) override;
    void unload() override;
};



#endif //SPRITE_SHEET_LOADABLE_H
