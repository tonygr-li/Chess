#ifndef EVENT_VARIANT_H
#define EVENT_VARIANT_H

#include <variant>
#include <memory>
#include <string>

class Board;

using EventVariant = std::variant<std::string, std::shared_ptr<Board>>;

#endif // EVENT_VARIANT_H
