#pragma once

namespace ly {
class Object {
public:
  Object();
  virtual ~Object();

  virtual void Destroy();
  bool isPendingDestroy() const { return mIsPendingDestroy; }

private:
  bool mIsPendingDestroy;
};
} // namespace ly