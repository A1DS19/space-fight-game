#include "level/GameLevelOne.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceship.h"

namespace ly {
GameLevelOne::GameLevelOne(Application *app) : World(app) {
  player = SpawnActor<PlayerSpaceship>();
  player.lock()->SetActorLocation(sf::Vector2f{300, 490});
}

void GameLevelOne::BeginPlay() {}

void GameLevelOne::InitGameStages() {
  AddStage(shared<WaitStage>{new WaitStage{this, 1.f}});
  AddStage(shared<VanguardStage>{new VanguardStage{this}});
  AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
  AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
}
}; // namespace ly