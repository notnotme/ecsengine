#include <ecsengine/Behavior/Node/PredefinedResult.h>


PredefinedResult::PredefinedResult(const bool result)
    : m_result(result) {}

bool PredefinedResult::execute(const entityx::TimeDelta dt) {
    return m_result;
}
