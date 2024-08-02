#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "gameplay/GameStage.h"

namespace ly {
World::World(Application *owningApp)
    : mOwningApp{owningApp}, mBegunPlay{false}, mActors{}, mPendingActors{},
      mCurrentStage{mGameStages.end()}, mGameStages{} {}

World::~World() {}

void World::BeginPlay() {}

void World::InitGameStages() {}

void World::AllGameStagesFinished() {}

void World::NextGameStage() {
  mCurrentStage = mGameStages.erase(mCurrentStage);

  if (mCurrentStage != mGameStages.end()) {
    mCurrentStage->get()->StartStage();
    mCurrentStage->get()->OnStageFinished.BindAction(GetWeakRef(),
                                                     &World::NextGameStage);
  } else {
    AllGameStagesFinished();
  }
}

void World::BeginPlayInternal() {
  if (!mBegunPlay) {
    mBegunPlay = true;
    BeginPlay();
    InitGameStages();
    StartStages();
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

  if (mCurrentStage != mGameStages.end()) {
    mCurrentStage->get()->TickStage(deltaTime);
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

void World::StartStages() {
  mCurrentStage = mGameStages.begin();
  mCurrentStage->get()->StartStage();
  mCurrentStage->get()->OnStageFinished.BindAction(GetWeakRef(),
                                                   &World::NextGameStage);
}

} // namespace ly