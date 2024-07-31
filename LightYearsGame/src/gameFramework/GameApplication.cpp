#include "gameFramework/GameApplication.h"
#include "config.h"
#include "enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

ly::Application *GetApplication() { return new ly::GameApplication(); }

namespace ly {
GameApplication::GameApplication()
    : Application{600, 980, "Space Shooter",
                  sf::Style::Titlebar | sf::Style::Close} {
  AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
  weak<World> newWorld = LoadWorld<World>();

  newWorld.lock()->SpawnActor<Actor>();
  player = newWorld.lock()->SpawnActor<PlayerSpaceship>();
  player.lock()->SetActorLocation(sf::Vector2f{300, 490});

  weak<Vanguard> playerVanguard = newWorld.lock()->SpawnActor<Vanguard>();
  playerVanguard.lock()->SetActorLocation(sf::Vector2f{100, 50});
  counter = 0;
}

void GameApplication::Tick(float deltaTime) {
  counter += deltaTime;
  // if (counter > 10.f) {
  //   if (!player.expired()) {
  //     player.lock()->Destroy();
  //   }
  // }
}
} // namespace ly