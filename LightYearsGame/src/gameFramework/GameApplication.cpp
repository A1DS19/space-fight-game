#include "gameFramework/GameApplication.h"
#include "config.h"
#include "framework/Actor.h"
#include "framework/World.h"
#include "spaceship/Spaceship.h"

ly::Application *GetApplication() { return new ly::GameApplication(); }

namespace ly {
GameApplication::GameApplication()
    : Application{600, 980, "Space Shooter",
                  sf::Style::Titlebar | sf::Style::Close} {

  weak<World> newWorld = LoadWorld<World>();

  newWorld.lock()->SpawnActor<Actor>();
  player = newWorld.lock()->SpawnActor<Spaceship>();
  player.lock()->SetTexture(GetResourceDir() +
                            "SpaceShooterRedux/PNG/playerShip2_blue.png");

  player.lock()->SetActorLocation(sf::Vector2f{300, 490});
  player.lock()->SetActorRotation(-90.f);
  player.lock()->SetVelocity(sf::Vector2f{0, -200.f});

  counter = 0;
}

void GameApplication::Tick(float deltaTime) {}
} // namespace ly