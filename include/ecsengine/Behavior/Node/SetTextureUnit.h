#ifndef SET_TEXTURE_UNIT_H
#define SET_TEXTURE_UNIT_H

#include <entityx/entityx.h>

#include "../Node.h"
#include "../../Component/TextureUnit.h"


class SetTextureUnit final : public Node {
private:
    entityx::Entity m_target;
    TextureUnit::Unit m_unit;
    bool m_is_set;

public:
    explicit SetTextureUnit(entityx::Entity target, TextureUnit::Unit unit);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<SetTextureUnit> create(const entityx::Entity target, const TextureUnit::Unit unit) {
        return std::make_unique<SetTextureUnit>(target, unit);
    }
};


#endif //SET_TEXTURE_UNIT_H
