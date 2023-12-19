#include "EventManager.hpp"

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

