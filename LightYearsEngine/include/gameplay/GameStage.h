#pragma once

#include "framework/Delegate.h"
#include "framework/Object.h"

namespace ly {
class World;
class GameStage : public Object {
public:
  GameStage(World *world);
  const World *GetWorld() const { return mWorld; }
  World *GetWorld() { return mWorld; }

  virtual void StartStage();
  virtual void TickStage(float deltaTime);
  void FinishStage();
  bool IsStageFinished() const { return mStageFinished; }

  Delegate<> OnStageFinished;

private:
  World *mWorld;
  bool mStageFinished;
  virtual void StageFinished();
};
}; // namespace ly