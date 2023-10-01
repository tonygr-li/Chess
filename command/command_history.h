#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

#include <memory>
#include <stack>

#include "../command/command.h"

template <typename T>
class CommandHistory {
    std::stack<std::shared_ptr<T>> history;
public:
    void push(std::shared_ptr<T> command) {
        history.push(std::move(command));
    }
    
    void pop() {
        history.pop();
    }

    std::shared_ptr<T> top() {
        return history.top();
    }

    bool empty() {
        return history.empty();
    }

    void clear() {
        while (!history.empty()) {
            history.pop();
        }
    }
};

#endif // COMMAND_HISTORY_H
