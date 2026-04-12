#include "Command.hpp"

#include "Category.hpp"

#include <SFML/System/Time.hpp>

#include <functional>

Command::Command() : action(nullptr), category(Category::None) {}