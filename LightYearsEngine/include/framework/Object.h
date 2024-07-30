#pragma once
#include "framework/Core.h"
#include "framework/Delegate.h"

namespace ly {
class Object : public std::enable_shared_from_this<Object> {
public:
  Object();
  virtual ~Object();

  virtual void Destroy();
  bool isPendingDestroy() const { return mIsPendingDestroy; }
  weak<Object> GetWeakRef();
  weak<const Object> GetWeakRef() const;
  Delegate<Object *> OnDestroy;

private:
  bool mIsPendingDestroy;
};
} // namespace ly