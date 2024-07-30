#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtils.h"
#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

namespace ly {
unique<PhysicsSystem> PhysicsSystem::physicsSystem{nullptr};

PhysicsSystem::PhysicsSystem()
    : mPhysicsWorld{b2Vec2{0.f, 0.f}}, mPhysicsScale{0.01f},
      mVelocityIterations{8}, mPositionIterations{3}, mContactListener{} {
  mPhysicsWorld.SetContactListener(&mContactListener);
  mPhysicsWorld.SetAllowSleeping(false);
}

void PhysicsContactListener::BeginContact(b2Contact *contact) {
  Actor *actorA = reinterpret_cast<Actor *>(
      contact->GetFixtureA()->GetBody()->GetUserData().pointer);

  Actor *actorB = reinterpret_cast<Actor *>(
      contact->GetFixtureB()->GetBody()->GetUserData().pointer);

  if (actorA && !actorA->isPendingDestroy()) {
    actorA->OnActorOverlap(actorB);
  }

  if (actorB && !actorB->isPendingDestroy()) {
    actorB->OnActorOverlap(actorA);
  }
}

void PhysicsContactListener::EndContact(b2Contact *contact) {
  Actor *actorA = nullptr;
  Actor *actorB = nullptr;

  if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody()) {
    actorA = reinterpret_cast<Actor *>(
        contact->GetFixtureA()->GetBody()->GetUserData().pointer);
  }

  if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody()) {
    actorB = reinterpret_cast<Actor *>(
        contact->GetFixtureB()->GetBody()->GetUserData().pointer);
  }

  if (actorA && !actorA->isPendingDestroy()) {
    actorA->OnActorEndOverlap(actorB);
  }

  if (actorB && !actorB->isPendingDestroy()) {
    actorB->OnActorEndOverlap(actorA);
  }
}

PhysicsSystem &PhysicsSystem::Get() {
  if (!physicsSystem) {
    physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
  }
  return *physicsSystem;
}

void PhysicsSystem::Step(float deltaTime) {
  mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
}

b2Body *PhysicsSystem::AddListener(Actor *listener) {
  if (listener->isPendingDestroy()) {
    return nullptr;
  }

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
  bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(),
                       listener->GetActorLocation().y * GetPhysicsScale());
  bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
  b2Body *body = mPhysicsWorld.CreateBody(&bodyDef);

  b2PolygonShape shape;
  auto bounds = listener->GetActorGlobalBounds();
  shape.SetAsBox(bounds.width / 2.f * GetPhysicsScale(),
                 bounds.height / 2.f * GetPhysicsScale());

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixtureDef.isSensor = true;

  body->CreateFixture(&fixtureDef);

  return body;
}

void PhysicsSystem::RemoveListener(b2Body *bodyToRemove) {}

} // namespace ly