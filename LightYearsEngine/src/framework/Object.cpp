#include "framework/Object.h"
#include "framework/Core.h"

namespace ly {
Object::Object() : mIsPendingDestroy{false} {}

Object::~Object() { LOG("Object::~Object destroyed"); }

void Object::Destroy() {
  mIsPendingDestroy = true;
  OnDestroy.Broadcast(this);
}

weak<Object> Object::GetWeakRef() { return weak_from_this(); }

weak<const Object> Object::GetWeakRef() const { return weak_from_this(); }
}; // namespace ly