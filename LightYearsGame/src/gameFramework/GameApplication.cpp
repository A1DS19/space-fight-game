#include "gameFramework/GameApplication.h"
#include "config.h"
#include "framework/Actor.h"
#include "framework/World.h"

ly::Application *GetApplication() { return new ly::GameApplication(); }

namespace ly {
GameApplication::GameApplication()
    : Application{600, 980, "Space Shooter",
                  sf::Style::Titlebar | sf::Style::Close} {

  weak<World> newWorld = LoadWorld<World>();

  newWorld.lock()->SpawnActor<Actor>();
  actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
  actorToDestroy.lock()->SetTexture(
      GetResourceDir() + "SpaceShooterRedux/PNG/playerShip2_blue.png");

  actorToDestroy.lock()->SetActorLocation(sf::Vector2f{300, 490});
  actorToDestroy.lock()->SetActorRotation(90.f);

  counter = 0;
}

void GameApplication::Tick(float deltaTime) {
  counter += deltaTime;
  if (counter > 2.f) {
    if (!actorToDestroy.expired()) {
      actorToDestroy.lock()->Destroy();
    }
  }
}
} // namespace ly