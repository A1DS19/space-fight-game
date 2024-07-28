#include "framework/AssetManager.h"

namespace ly {
unique<AssetManager> AssetManager::assetManager{nullptr};

AssetManager &AssetManager::Get() {
  if (assetManager == nullptr) {
    assetManager = std::move(unique<AssetManager>(new AssetManager()));
  }
  return *assetManager;
};

shared<sf::Texture> AssetManager::LoadTexture(const std::string &path) {
  auto found = mLoadedTextures.find(path);

  if (found != mLoadedTextures.end()) {
    return found->second;
  }

  shared<sf::Texture> newTexture{new sf::Texture()};
  if (newTexture->loadFromFile(path)) {
    mLoadedTextures.insert({path, newTexture});
    return newTexture;
  }

  return shared<sf::Texture>{nullptr};
}

AssetManager::AssetManager() {}

void AssetManager::CleanCycle() {
  for (auto it = mLoadedTextures.begin(); it != mLoadedTextures.end();) {
    if (it->second.unique()) {
      it = mLoadedTextures.erase(it);
    } else {
      ++it;
    }
  }
}
} // namespace ly