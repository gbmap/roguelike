#include "command_poll.hpp"
#include <iostream>

namespace roguelike::commands {
    // template <typename CommandType>
    // void CommandPoll<CommandType>::CommandPoll() : condition(false) {}

    template <typename CommandType>
    void CommandPoll<CommandType>::QueueCommand(CommandType* command) {
        std::lock_guard<std::mutex> lock(mutex);
        commands.push(command);
        condition.notify_one();
    }

    template <typename CommandType>
    CommandType* CommandPoll<CommandType>::PopCommand() {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [this]() { return !commands.empty(); });

        CommandType* c = commands.front();
        commands.pop();
        return c;
    }
}