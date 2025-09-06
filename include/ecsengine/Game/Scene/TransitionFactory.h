#ifndef TRANSITION_FACTORY_H
#define TRANSITION_FACTORY_H

#include <functional>
#include <memory>
#include <cstdint>

#include "TransitionScene.h"


using TransitionFactory =
    std::function<
        std::unique_ptr<TransitionScene>(uint32_t transitionId)
    >;


#endif //TRANSITION_FACTORY_H
