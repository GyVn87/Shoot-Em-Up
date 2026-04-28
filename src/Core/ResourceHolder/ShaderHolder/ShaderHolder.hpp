#include "ResourceHolder.hpp"

#include <SFML/Graphics/Shader.hpp>

namespace Shaders {
    enum ID {};
}

using ShaderHolder = ResourceHolder<sf::Shader, Shaders::ID>;