#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include "EventType.hpp"

class EventManager {
private:
    EventManager() = default;
    ~EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    using CallbackBase = std::function<void(const std::shared_ptr<void>&)>;
    template <typename T>
    using Callback = std::function<void(const std::shared_ptr<T>&)>;

    std::unordered_map<EventType, std::vector<CallbackBase>> m_subscribers;

public:
    static EventManager& getInstance();
    
    template <typename T>
    void subscribe(EventType eventName, Callback<T> callback) {
        m_subscribers[eventName].emplace_back([callback](const std::shared_ptr<void>& eventData) {
            callback(std::static_pointer_cast<T>(eventData));
        });
    }

    template <typename T>
    void publish(EventType eventName, const std::shared_ptr<T>& eventData) {
        if (m_subscribers.find(eventName) != m_subscribers.end()) {
            for (const auto& callback : m_subscribers[eventName]) {
                callback(eventData);
            }
        }
    }
};

#endif
