#ifndef PREDEFINED_RESULT_H
#define PREDEFINED_RESULT_H


#include <entityx/entityx.h>

#include "../Node.h"


class PredefinedResult final : public Node {
private:
    bool m_result;

public:
    explicit PredefinedResult(bool result);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    [[nodiscard]] static std::unique_ptr<PredefinedResult> create(const bool result) {
        return std::make_unique<PredefinedResult>(result);
    }
};


#endif //PREDEFINED_RESULT_H
