#ifndef CLEAR_BUFFER_H
#define CLEAR_BUFFER_H

#include <array>

#include "../Node.h"


class ClearBuffer final : public Node {
private:
    std::array<float, 4> m_color;

public:
    explicit ClearBuffer(const std::array<float, 4>& color);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<ClearBuffer> create(const std::array<float, 4>& color) {
        return std::make_unique<ClearBuffer>(color);
    }
};


#endif //CLEAR_BUFFER_H
