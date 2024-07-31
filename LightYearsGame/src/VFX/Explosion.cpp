#include "VFX/Explosion.h"
#include "VFX/Particle.h"
#include "framework/MathUtils.h"
#include "framework/World.h"

namespace ly {
Explosion::Explosion(int particleAmount, float lifeTimeMin, float lifeTimeMax,
                     float sizeMin, float sizeMax, float speedMin,
                     float speedMax, const sf::Color &particleColor,
                     const List<std::string> &particleImagePaths)
    : mParticleAmount(particleAmount), mLifeTimeMin(lifeTimeMin),
      mLifeTimeMax(lifeTimeMax), mSizeMin(sizeMin), mSizeMax(sizeMax),
      mSpeedMin(speedMin), mSpeedMax(speedMax), mParticleColor(particleColor),
      mParticleImagePaths(particleImagePaths) {}

void Explosion::SpawnExplosion(World *world, const sf::Vector2f &location) {

  if (!world) {
    return;
  }

  for (int i = 0; i < mParticleAmount; i++) {
    std::string imagePath = mParticleImagePaths[(int)RandomRange(
        0, mParticleImagePaths.size() - 1)];
    weak<Particle> particle = world->SpawnActor<Particle>(imagePath);

    particle.lock()->RandomLifeTime(mLifeTimeMin, mLifeTimeMax);
    particle.lock()->SetActorLocation(location);

    particle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
    particle.lock()->RandomSize(mSizeMin, mSizeMax);

    particle.lock()->GetSprite().setColor(mParticleColor);
  }
}

}; // namespace ly