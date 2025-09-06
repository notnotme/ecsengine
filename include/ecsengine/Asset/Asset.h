#ifndef ASSET_H
#define ASSET_H


class Asset {
protected:
    explicit Asset() = default;

public:
    Asset(const Asset &) = delete;
    Asset &operator=(const Asset &) = delete;
    virtual ~Asset() = default;
};


#endif //ASSET_H
