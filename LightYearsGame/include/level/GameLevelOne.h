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
  virtual void InitGameStages() override;
  weak<PlayerSpaceship> player;
  TimerHandle timerHandle;
};
}; // namespace ly