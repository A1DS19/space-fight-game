#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "gameplay/GameStage.h"

namespace ly {
World::World(Application *owningApp)
    : mOwningApp{owningApp}, mBegunPlay{false}, mActors{}, mPendingActors{},
      mCurrentStageIndex{-1}, mGameStages{} {}

World::~World() {}

void World::BeginPlay() {}

void World::InitGameStages() {}

void World::AllGameStagesFinished() {}

void World::NextGameStage() {
  ++mCurrentStageIndex;
  if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size()) {
    mGameStages[mCurrentStageIndex]->OnStageFinished.BindAction(
        GetWeakRef(), &World::NextGameStage);
    mGameStages[mCurrentStageIndex]->StartStage();
  } else {
    AllGameStagesFinished();
  }
}

void World::BeginPlayInternal() {
  if (!mBegunPlay) {
    mBegunPlay = true;
    BeginPlay();
    InitGameStages();
    NextGameStage();
  }
}

void World::AddStage(const shared<GameStage> &stage) {
  mGameStages.push_back(stage);
}

void World::TickInternal(float deltaTime) {
  for (shared<Actor> actor : mPendingActors) {
    mActors.push_back(actor);
    actor->BeginPlayInternal();
  }
  mPendingActors.clear();

  for (auto iter = mActors.begin(); iter != mActors.end();) {
    iter->get()->TickInternal(deltaTime);
    ++iter;
  }

  if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size()) {
    mGameStages[mCurrentStageIndex]->TickStage(deltaTime);
  }

  Tick(deltaTime);
}

sf::Vector2u World::GetWindowSize() const {
  return mOwningApp->GetWindowSize();
}

void World::Render(sf::RenderWindow &window) {
  for (auto &actor : mActors) {
    actor->Render(window);
  }
}

void World::Tick(float deltaTime) {}

void World::CleanCycle() {
  for (auto iter = mActors.begin(); iter != mActors.end();) {
    if (iter->get()->isPendingDestroy()) {
      iter = mActors.erase(iter);
    } else {
      ++iter;
    }
  }

  for (auto iter = mGameStages.begin(); iter != mGameStages.end();) {
    if (iter->get()->IsStageFinished()) {
      iter = mGameStages.erase(iter);
    } else {
      ++iter;
    }
  }
}

} // namespace ly