#pragma once

#include <map>
#include <memory>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace ly {

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

template <typename T> using unique = std::unique_ptr<T>;

template <typename T> using shared = std::shared_ptr<T>;

template <typename T> using weak = std::weak_ptr<T>;

template <typename T> using List = std::vector<T>;

template <typename keyT, typename ValT, typename Pr = std::less<keyT>>
using Map = std::map<keyT, ValT, Pr>;

template <typename keyT, typename ValT, typename Hasher = std::hash<keyT>>
using Dictionary = std::unordered_map<keyT, ValT, Hasher>;

template <typename T> using Set = std::unordered_set<T>;

} // namespace ly
