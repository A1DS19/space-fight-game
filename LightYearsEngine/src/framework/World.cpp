#include "framework/World.h"
#include "framework/Core.h"

namespace ly {
World::World(Application *owningApp)
    : mOwningApp{owningApp}, mBegunPlay{false} {}

World::~World() {}

void World::BeginPlay() { LOG("World::BeginPlay"); }

void World::BeginPlayInternal() {
  if (!mBegunPlay) {
    mBegunPlay = true;
    BeginPlay();
  }
}

void World::TickInternal(float deltaTime) { Tick(deltaTime); }

void World::Tick(float deltaTime) { LOG("World::Tick at %f", 1.f / deltaTime); }

} // namespace ly