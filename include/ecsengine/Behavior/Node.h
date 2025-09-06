#ifndef NODE_H
#define NODE_H

#include <entityx/entityx.h>


class Node {
public:
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
    explicit Node() = default;
    virtual ~Node() = default;

public:
    [[nodiscard]] virtual bool execute(entityx::TimeDelta dt) = 0;
};


#endif //NODE_H
