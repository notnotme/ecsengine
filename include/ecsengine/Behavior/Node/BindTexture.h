#ifndef BIND_TEXTURE_H
#define BIND_TEXTURE_H

#include <entityx/entityx.h>
#include <glad/glad.h>

#include "../Node.h"
#include "../../Component/TextureUnit.h"


class BindTexture final : public Node {
private:
    GLuint m_texture;
    TextureUnit::Unit m_unit;

public:
    explicit BindTexture(GLuint texture, TextureUnit::Unit unit);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<BindTexture> create(GLuint texture, TextureUnit::Unit unit) {
        return std::make_unique<BindTexture>(texture, unit);
    }
};


#endif //BIND_TEXTURE_H
