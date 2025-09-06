#ifndef ECS_ENGINE_H
#define ECS_ENGINE_H


#include "ecsengine/Asset/Font/Character.h"
#include "ecsengine/Asset/Font/FontAsset.h"
#include "ecsengine/Asset/Font/FontLoadable.h"
#include "ecsengine/Asset/SpriteSheet/TextureRegion.h"
#include "ecsengine/Asset/SpriteSheet/SpriteSheetAsset.h"
#include "ecsengine/Asset/SpriteSheet/SpriteSheetLoadable.h"
#include "ecsengine/Asset/Texture/TextureAsset.h"
#include "ecsengine/Asset/Texture/TextureLoadable.h"
#include "ecsengine/Asset/AssetManager.h"
#include "ecsengine/Asset/LoadableAsset.h"

#include "ecsengine/Behavior/Node/BindTexture.h"
#include "ecsengine/Behavior/Node/ClearBuffer.h"
#include "ecsengine/Behavior/Node/CreateQuad.h"
#include "ecsengine/Behavior/Node/CreateSprite.h"
#include "ecsengine/Behavior/Node/CreateText.h"
#include "ecsengine/Behavior/Node/Delay.h"
#include "ecsengine/Behavior/Node/FadeIn.h"
#include "ecsengine/Behavior/Node/FadeOut.h"
#include "ecsengine/Behavior/Node/GameEnd.h"
#include "ecsengine/Behavior/Node/PredefinedResult.h"
#include "ecsengine/Behavior/Node/SetFriction.h"
#include "ecsengine/Behavior/Node/SetTextureUnit.h"
#include "ecsengine/Behavior/Node/SetTint.h"
#include "ecsengine/Behavior/Node/SetVelocity.h"
#include "ecsengine/Behavior/Node/StartPlayer.h"
#include "ecsengine/Behavior/Node/TransitionTo.h"
#include "ecsengine/Behavior/Node/WaitPlayer.h"
#include "ecsengine/Behavior/Node.h"
#include "ecsengine/Behavior/ParallelNode.h"
#include "ecsengine/Behavior/SequenceNode.h"

#include "ecsengine/Component/Friction.h"
#include "ecsengine/Component/Gravity.h"
#include "ecsengine/Component/Position.h"
#include "ecsengine/Component/Rotation.h"
#include "ecsengine/Component/Scale.h"
#include "ecsengine/Component/Size.h"
#include "ecsengine/Component/TextureCoordinate.h"
#include "ecsengine/Component/TextureUnit.h"
#include "ecsengine/Component/Tint.h"
#include "ecsengine/Component/Velocity.h"

#include "ecsengine/Event/ExitGame.h"
#include "ecsengine/Event/MusicTick.h"
#include "ecsengine/Event/SceneTransition.h"

#include "ecsengine/Game/Scene/GameScene.h"
#include "ecsengine/Game/Scene/SceneFactory.h"
#include "ecsengine/Game/Scene/TransitionFactory.h"
#include "ecsengine/Game/Scene/TransitionScene.h"
#include "ecsengine/Game/Transition/FadeOutFadeIn.h"
#include "ecsengine/Game/GamePad.h"
#include "ecsengine/Game/OnGameStart.h"

#include "ecsengine/Renderer/QuadProgram.h"
#include "ecsengine/Renderer/RendererUtil.h"
#include "ecsengine/Renderer/Shader.h"
#include "ecsengine/Renderer/SpriteProgram.h"
#include "ecsengine/Renderer/SpriteVertex.h"

#include "ecsengine/System/BehaviorSystem.h"
#include "ecsengine/System/MovementSystem.h"
#include "ecsengine/System/SpriteSystem.h"

#include "ecsengine/GameWindow.h"


#endif //ECS_ENGINE_H