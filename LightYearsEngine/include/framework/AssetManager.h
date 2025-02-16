#pragma once

#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ly {

class AssetManager {
public:
  static AssetManager &Get();
  shared<sf::Texture> LoadTexture(const std::string &name);
  void CleanCycle();
  void SetAssetRootDirectory(const std::string &rootDirectory);

protected:
  AssetManager();

private:
  static unique<AssetManager> assetManager;
  Dictionary<std::string, shared<sf::Texture>> mLoadedTextures;
  std::string mRootDirectory;
};
} // namespace ly