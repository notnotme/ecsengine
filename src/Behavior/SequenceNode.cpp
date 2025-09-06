#include <ecsengine/Behavior/SequenceNode.h>


bool SequenceNode::execute(const entityx::TimeDelta dt) {
    for (auto i = m_index; i < m_children.size(); ++i) {
        if (! m_children[i]->execute(dt)) {
            break;
        }

        ++m_index;
    }

    return m_index == m_children.size();
}
