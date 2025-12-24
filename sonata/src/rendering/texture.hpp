#pragma once
#include "core.hpp"

namespace Sonata {

class Texture {
public:
    virtual ~Texture() = default;

    [[nodiscard]] virtual int GetWidth() const = 0;
    [[nodiscard]] virtual int GetHeight() const = 0;

    virtual void SetData(const void* p_Data, int p_Size) = 0;

    virtual void Bind(uint32_t p_Unit = 0) const = 0;

    virtual bool operator==(const Texture& p_Other) const = 0;
};

class Texture2D : public Texture {
public:
    virtual ~Texture2D() override = default;

    static Ref<Texture2D> Create(int p_Width, int p_Height);
    static Ref<Texture2D> Create(std::string_view p_Path);
};

} // namespace Sonata
