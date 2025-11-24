#pragma once
#include <functional>

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
    void AddBind(std::function<FuncSig> callback, void* object)
    {
        callbacks.emplace_back(object, callback);
    }

    void AddBind(std::function<FuncSig> callback)
    {
        callbacks.emplace_back(callback, nullptr, true);
    }

    void Execute()
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
