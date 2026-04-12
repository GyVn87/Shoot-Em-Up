#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include "Command.hpp"

#include <queue>

class CommandQueue {
    public:
        Command pop();
        void push(const Command& cmd);
        bool isEmpty() const;
    private:
        std::queue<Command> mQueue;
};

#endif