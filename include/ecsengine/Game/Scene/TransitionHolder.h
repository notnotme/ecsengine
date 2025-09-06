#ifndef TRANSITION_HOLDER_H
#define TRANSITION_HOLDER_H

#include <memory>

#include "../Scene/GameScene.h"
#include "../Scene/TransitionScene.h"


struct TransitionHolder {
    std::unique_ptr<GameScene> next_scene;
    std::unique_ptr<TransitionScene> transition_scene;

    explicit TransitionHolder(std::unique_ptr<GameScene> nextScene, std::unique_ptr<TransitionScene> transitionScene)
        : next_scene(std::move(nextScene)),
          transition_scene(std::move(transitionScene)) {}
};


#endif //TRANSITION_HOLDER_H
