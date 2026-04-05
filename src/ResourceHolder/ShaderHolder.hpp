#include "ResourceHolder.hpp"
#include <SFML/Graphics.hpp>

namespace Shaders {
    enum ID {Tint};
}

using ShaderHolder = ResourceHolder<sf::Shader, Shaders::ID>;