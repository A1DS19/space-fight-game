#include "gameFramework/GameApplication.h"
#include "config.h"
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

  weak<Spaceship> playerSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
  playerSpaceship.lock()->SetTexture(
      "SpaceShooterRedux/PNG/playerShip1_green.png");
  playerSpaceship.lock()->SetActorLocation(sf::Vector2f{100, 50});
}

void GameApplication::Tick(float deltaTime) {}
} // namespace ly