#ifndef PARALLEL_NODE_H
#define PARALLEL_NODE_H

#include <vector>
#include <memory>

#include "Node.h"


class ParallelNode final : public Node {
private:
    std::vector<std::unique_ptr<Node>> m_children;
    bool m_success;

public:
    template<class T = std::unique_ptr<Node>, typename ... Children>
    explicit ParallelNode(Children&& ... children);

public:
    [[nodiscard]] bool execute(entityx::TimeDelta dt) override;

public:
    template<class T = std::unique_ptr<Node>, typename ... Children>
    [[nodiscard]] static std::unique_ptr<ParallelNode> create(Children&& ... children);
};

template<class T, typename ... Children>
ParallelNode::ParallelNode(Children&& ... children)
    : m_success(false) {
    ( m_children.emplace_back( std::forward<Children>(children) ), ... );
}

template<class T, typename ... Children>
[[nodiscard]] std::unique_ptr<ParallelNode> ParallelNode::create(Children&& ... children) {
    return std::make_unique<ParallelNode>(std::forward<Children>(children) ...);
}

#endif //PARALLEL_NODE_H
