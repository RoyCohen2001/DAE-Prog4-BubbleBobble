#pragma once
#include <vector>
#include <memory>
#include <functional>

template <typename T>
class ObjectPool
{
public:
    ObjectPool(size_t initialSize, std::function<std::unique_ptr<T>()> factory)
        : m_Factory(factory)
    {
        for (size_t i = 0; i < initialSize; ++i)
            m_Pool.push_back(factory());
    }

    T* Acquire()
    {
        for (auto& obj : m_Pool)
        {
            if (!obj->IsActive())
            {
                return obj.get();
            }
        }
        m_Pool.push_back(m_Factory());
        return m_Pool.back().get();
    }

    const std::vector<std::unique_ptr<T>>& GetAll() const { return m_Pool; }

private:
    std::vector<std::unique_ptr<T>> m_Pool;
    std::function<std::unique_ptr<T>()> m_Factory;
};