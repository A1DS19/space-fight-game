#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ly {
GameStage::GameStage(World *world) : mWorld{world}, mStageFinished{false} {}

void GameStage::StartStage() { LOG("Starting stage"); }

void GameStage::TickStage(float deltaTime) {}

void GameStage::FinishStage() {
  mStageFinished = true;
  OnStageFinished.Broadcast();
  StageFinished();
}

void GameStage::StageFinished() { LOG("Stage finished"); }

}; // namespace ly