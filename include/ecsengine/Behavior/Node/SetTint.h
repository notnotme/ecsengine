#ifndef SET_TINT_H
#define SET_TINT_H

#include <cstdint>

#include <entityx/entityx.h>

#include "../Node.h"
#include "../../Component/Tint.h"


class SetTint final : public Node {
private:
    entityx::Entity m_target;
    Tint m_tint;
    bool m_is_set;

public:
    explicit SetTint(entityx::Entity target, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<SetTint> create(const entityx::Entity target, const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) {
        return std::make_unique<SetTint>(target, red, green, blue, alpha);
    }
};


#endif //SET_TINT_H
