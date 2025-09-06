#include <ecsengine/Asset/SpriteSheet/SpriteSheetLoadable.h>

#include <fstream>
#include <stdexcept>


void SpriteSheetLoadable::load(const std::string_view path) {
    auto file = std::ifstream(path.data(), std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(path));
    }

    if (file.tellg() <= 8) {
        throw std::runtime_error("File seems not a SpriteSheetAsset: " + std::string(path));
    }

    char check[5] = {};
    file.seekg(std::ios::beg);
    file.read(check, 4);

    if (std::string(check) != "SPSH") {
        throw std::runtime_error("File seems not a SpriteSheetAsset: " + std::string(path));
    }

    auto count = 0;
    file.read(reinterpret_cast<char *>(&count), sizeof(count));

    for (int i = 0; i < count; ++i) {
        char name[32] = {};
        file.read(name, 32);

        TextureRegion region;
        file.read(reinterpret_cast<char *>(&region), sizeof(TextureRegion));
        m_sprites.emplace(name, region);
    }

    file.close();
}

void SpriteSheetLoadable::unload() {
}
