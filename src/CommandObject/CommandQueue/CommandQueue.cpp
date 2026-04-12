#include "CommandQueue.hpp"

#include "Command.hpp"

#include <queue>

Command CommandQueue::pop() {
    Command result = mQueue.front();
    mQueue.pop();
    return result;
}

void CommandQueue::push(const Command& cmd) {
    mQueue.push(cmd);
}

bool CommandQueue::isEmpty() const {
    return mQueue.empty();
}