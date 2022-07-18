#pragma once

namespace roguelike::commands {
    class Command;

    template <typename CommandType>
    class CommandHandler {
        static_assert(std::is_base_of<Command, CommandType>::value, "CommandType must be a Command");
    public:
        virtual bool HandleCommand(const CommandType& command) = 0;
    };
}