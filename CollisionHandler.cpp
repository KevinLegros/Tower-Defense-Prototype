#include "Entity.hpp"

std::vector<CollisionHandler> CollisionHandler::entityColQueue;

CollisionHandler::CollisionHandler() {
    this->entityA = NULL;
    this->entityB = NULL;
}
