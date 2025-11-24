#pragma once
#include <functional>

// TODO: Place some safe guards and test properly

template<typename FuncSig>
struct Callable
{
    void* obj{};
    std::function<FuncSig> func;
    bool standalone{};
};

template <typename FuncSig>
class Event
{
public:
    [[maybe_unused]] void AddBind(std::function<FuncSig> callback, void* object)
    {
        callbacks.push_back({object, callback});
    }

    [[maybe_unused]] void AddBind(std::function<FuncSig> callback)
    {
        callbacks.push_back({callback, nullptr, true});
    }

    [[maybe_unused]] void Execute()
    {
        for (auto& callback : callbacks)
        {
            if (callback.obj || callback.standalone)
            {
                callback.func();
            }
        }
    }
private:
    std::vector<Callable<FuncSig>> callbacks{};
};
