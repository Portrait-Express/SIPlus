#pragma once
#ifndef INCLUDE_INTERNAL_BINARY_TYPE_CACHE_H_
#define INCLUDE_INTERNAL_BINARY_TYPE_CACHE_H_

#include <list>
#include <memory>
#include <unordered_map>

#include "siplus/config.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {
namespace internal {

template<typename T, bool (T::*Handle)(const TypeInfo&, const TypeInfo&) const = T::can_handle>
struct BinaryTypeCache {
    using iterator = std::list<std::shared_ptr<T>>::iterator;
    using const_iterator = std::list<std::shared_ptr<T>>::const_iterator;

    iterator begin() { return items_.begin(); }
    iterator end() { return items_.end(); }

    const_iterator begin() const { return items_.begin(); }
    const_iterator end() const { return items_.end(); }

    template<std::derived_from<T> U, typename... Ts>
    std::shared_ptr<U> emplace_item(Ts&&... args) {
        //put at front to prioritized newest entries.
        auto value = std::make_shared<U>(std::forward<Ts>(args)...);
        items_.push_front(std::static_pointer_cast<T>(value));
        return value;
    }

    iterator find(const TypeInfo& first, const TypeInfo& second) {
        auto firstIt = cache_.find(first.name());

        if(firstIt != cache_.end()) {
            auto secondIt = firstIt->second.find(second.name());

            if(secondIt != firstIt->second.end()) {
                return convert_constness(secondIt->second);
            }
        }

        for(auto it = items_.begin(); it != items_.end(); it++) {
            auto& item = *it;

            if(((*item).*Handle)(first, second)) {
                if(firstIt != cache_.end()) {
                    (firstIt->second)[second.name()] = it;
                } else {
                    cache_[first.name()][second.name()] = it;
                }

                return it;
            }
        }

        return items_.end();
    }

    const_iterator find(const TypeInfo& first, const TypeInfo& second) const {
        auto firstIt = cache_.find(first.name());

        if(firstIt != cache_.end()) {
            auto secondIt = firstIt->second.find(second.name());

            if(secondIt != firstIt->second.end()) {
                return secondIt->second;
            }
        }

        for(auto it = items_.begin(); it != items_.end(); it++) {
            auto& item = *it;

            if(((*item).*Handle)(first, second)) {
                if(firstIt != cache_.end()) {
                    (firstIt->second)[second.name()] = it;
                } else {
                    cache_[first.name()][second.name()] = it;
                }

                return it;
            }
        }

        return items_.end();
    }

private:
    std::list<std::shared_ptr<T>> items_;
    mutable std::unordered_map<std::string, std::unordered_map<std::string, const_iterator>> cache_;

    iterator convert_constness(const_iterator it) {
        //dont think about it too much... It cant hurt you any more
        return items_.erase(it, it);
    }
};

} /* internal */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_INTERNAL_BINARY_TYPE_CACHE_H_
