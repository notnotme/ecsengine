#include <ecsengine/Behavior/ParallelNode.h>


bool ParallelNode::execute(const entityx::TimeDelta dt) {
    if (m_success) {
        return true;
    }

    auto success = static_cast<size_t>(0);
    for (const auto &child : m_children) {
        if (child->execute(dt)) {
            ++success;
        }
    }

    return m_success = success == m_children.size();
}
