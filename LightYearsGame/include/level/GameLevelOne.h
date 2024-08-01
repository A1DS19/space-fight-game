#pragma once

#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly {
class PlayerSpaceship;
class GameLevelOne : public World {
public:
  GameLevelOne(Application *app);

private:
  virtual void BeginPlay() override;
  void TimerCallback();
  weak<PlayerSpaceship> player;
  TimerHandle timerHandle;
  virtual void InitGameStages() override;
};
}; // namespace ly