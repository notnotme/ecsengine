#ifndef LOADABLE_ASSET_H
#define LOADABLE_ASSET_H

#include <string_view>

#include "Asset.h"


template <class A = Asset>
class LoadableAsset : public A {
public:
    using BaseType = A;

    template <typename... Args>
    explicit LoadableAsset(Args&&... args);

public:
    virtual void load(std::string_view path) = 0;
    virtual void unload() = 0;
};


template<class A>
template<typename ... Args>
LoadableAsset<A>::LoadableAsset(Args &&...args) : A(std::forward<Args>(args)...) {}


#endif //LOADABLE_ASSET_H
