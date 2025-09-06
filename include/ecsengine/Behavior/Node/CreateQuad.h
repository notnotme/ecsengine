#ifndef CREATE_QUAD_H
#define CREATE_QUAD_H

#include <cstdint>

#include <entityx/entityx.h>

#include "../../Component/Position.h"
#include "../../Component/Size.h"
#include "../../Component/Tint.h"
#include "../Node.h"


class CreateQuad final : public Node {
private:
    entityx::Entity m_target;
    Position m_position;
    Size m_size;
    Tint m_tint;
    bool m_created;

public:
    explicit CreateQuad(entityx::Entity target, float x, float y, int16_t width, int16_t height, uint8_t, uint8_t g, uint8_t b, uint8_t a);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<CreateQuad> create(const entityx::Entity target, const float x, const float y, const int16_t width, const int16_t height, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
        return std::make_unique<CreateQuad>(target, x, y, width, height, r, g, b, a);
    }
};


#endif //CREATE_QUAD_H
