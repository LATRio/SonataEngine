#pragma once
#include "core.hpp"

namespace Sonata {

class Texture {
public:
    virtual ~Texture() = default;

    [[nodiscard]] virtual int GetWidth() const = 0;
    [[nodiscard]] virtual int GetHeight() const = 0;

    virtual void Bind(uint32_t p_Unit = 0) const = 0;
};

class Texture2D : public Texture
{
public:
    virtual ~Texture2D() override = default;

    static Ref<Texture2D> Create(const std::string& p_Path);
};

}
