#include "enemy/VanguardStage.h"
#include "enemy/Vanguard.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly {
VanguardStage::VanguardStage(World *world)
    : GameStage(world), mSpawnInterval{2.0f}, mSwitchInterval{5.0f},
      mSpawnDistanceToEdge{100.0f}, mLeftSpawnLoc{0.0f, 0.0f},
      mRightSpawnLoc{0.0f, 0.0f}, mSpawnLoc{0.0f, 0.0f}, mRowsToSpawn{2},
      mRowSpawnCount{0}, mVanguardsPerRow{5}, mCurrentRowVanguardCount{0} {}

void VanguardStage::StartStage() {
  auto windowSize = GetWorld()->GetWindowSize();
  mLeftSpawnLoc = sf::Vector2f{mSpawnDistanceToEdge, -100.f};
  mRightSpawnLoc = sf::Vector2f{windowSize.x - mSpawnDistanceToEdge, -100.f};
  SwitchRow();
}

void VanguardStage::SwitchRow() {
  if (mRowSpawnCount == mRowsToSpawn) {
    StageFinished();
    return;
  }

  if (mSpawnLoc == mLeftSpawnLoc) {
    mSpawnLoc = mRightSpawnLoc;
  } else {
    mSpawnLoc = mLeftSpawnLoc;
  }

  mSpawnTimerHandle = TimerManager::Get().SetTimer(
      GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
  ++mRowSpawnCount;
}

void VanguardStage::SpawnVanguard() {
  weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>(mSpawnLoc);
  newVanguard.lock()->SetActorLocation(mSpawnLoc);
  ++mCurrentRowVanguardCount;
  if (mCurrentRowVanguardCount == mVanguardsPerRow) {
    TimerManager::Get().ClearTimer(mSpawnTimerHandle);
    mSwitchTimerHandle = TimerManager::Get().SetTimer(
        GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
    mCurrentRowVanguardCount = 0;
  }
}

void VanguardStage::StageFinished() {
  TimerManager::Get().ClearTimer(mSpawnTimerHandle);
  TimerManager::Get().ClearTimer(mSwitchTimerHandle);
}

} // namespace ly
