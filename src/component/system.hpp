#pragma once

#include "util/uuid.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace cherrypink {

template<typename T>

class System {
public:
    virtual void ProcessComponent(const UUID& entityUuid, T& object) = 0;
};

class SystemRegistry {
public:
    template<typename T>
    void RegisterSystem(std::shared_ptr<System<T>> system) {
        m_systems[std::type_index(typeid(T))] = system;
    }

    template<typename T>
    void ProcessComponent(const UUID& entityUuid, T& component) {
        auto it = m_systems.find(std::type_index(typeid(T)));
        if (it != m_systems.end()) {
            auto processor = std::static_pointer_cast<System<T>>(it->second);
            processor->ProcessComponent(entityUuid, component);
        }
    }

    void Shutdown() { m_systems.clear(); }

private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> m_systems;
};

}
