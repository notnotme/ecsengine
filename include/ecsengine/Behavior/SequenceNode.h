#ifndef SEQUENCE_NODE_H
#define SEQUENCE_NODE_H

#include <vector>
#include <memory>

#include "Node.h"


class SequenceNode final : public Node {
private:
    std::vector<std::unique_ptr<Node>> m_children;
    size_t m_index;

public:
    template<class T = std::unique_ptr<Node>, typename ... Children>
    explicit SequenceNode(Children&& ... children);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    template<class T = std::unique_ptr<Node>, typename ... Children>
    [[nodiscard]] static std::unique_ptr<SequenceNode> create(Children&& ... children);
};

template<class T, typename ... Children>
SequenceNode::SequenceNode(Children&& ... children)
    : m_index(0) {
    ( m_children.emplace_back( std::forward<Children>(children) ), ... );
}

template<class T, typename ... Children>
[[nodiscard]] std::unique_ptr<SequenceNode> SequenceNode::create(Children&& ... children) {
    return std::make_unique<SequenceNode>(std::forward<Children>(children) ...);
}

#endif //SEQUENCE_NODE_H
