#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace dd {

struct TransformComponent {
   glm::mat4 world;

   glm::quat rotation;
   glm::vec3 position;
};

}
