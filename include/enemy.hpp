#pragma once

#include <glm/fwd.hpp>

#include "components/health.hpp"
#include "components/position.hpp"

struct Enemy : public PositionComponent, public HealthComponent
{
    
};