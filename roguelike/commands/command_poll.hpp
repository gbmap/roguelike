
#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include "command.hpp"

namespace roguelike::commands {
    template<typename CommandType>
    class CommandPoll {
        public:
            void QueueCommand(CommandType* command);
            CommandType* PopCommand();
        private:
            std::queue<CommandType*> commands;
            mutable std::mutex mutex;
            std::condition_variable condition;
    };
}

#include "command_poll.tpp"