#ifndef SCENE_TRANSITION_H
#define SCENE_TRANSITION_H

#include <cstdint>


struct SceneTransition {
    uint32_t scene_id;
    uint32_t transition_id;

    explicit SceneTransition(const uint32_t sceneId, const uint32_t transitionId)
        : scene_id(sceneId),
          transition_id(transitionId) {}
};


#endif //SCENE_TRANSITION_H
