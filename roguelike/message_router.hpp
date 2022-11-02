#pragma once

#include <functional>
#include <map>
#include <typeindex>

class MessageHandler 
{
public:
    void* handler;

    MessageHandler(void* handler) : handler(handler), id(id_counter++) {}

    bool operator==(const MessageHandler& other) const noexcept { return id == other.id; }
private:
    static int id_counter;
    int id;
};

class MessageRouter
{
    static std::shared_ptr<MessageRouter> instance;
public:
    static std::shared_ptr<MessageRouter> GetInstance()
    {
        if (instance == nullptr)
            instance = std::shared_ptr<MessageRouter>(new MessageRouter());
        return instance;
    }


    template<typename MessageType>
    int GetHandlerCount()
    {
        auto handlers = GetHandlers<MessageType>();
        if (handlers == nullptr)
            return 0;

        return handlers->size();
    }

    
    template<typename MessageType>
    std::shared_ptr<MessageHandler> AddHandler(std::function<void(MessageType)>& handler)
    {
        auto type = std::type_index(typeid(MessageType));

        auto handlers = GetHandlers<MessageType>();
        if (handlers == nullptr)
        {
            message_handlers[type] = std::vector<std::shared_ptr<MessageHandler>>();
            handlers = &message_handlers[type];
        }

        std::shared_ptr<MessageHandler> message_handler = std::make_shared<MessageHandler>(
            reinterpret_cast<void*>(&handler)
        );
        handlers->push_back(message_handler);
        return message_handler;
    }

    template<typename MessageType>
    void RemoveHandler(std::shared_ptr<MessageHandler> handler)
    {
        if (message_handlers.size() == 0)
            return; 

        auto handlers = GetHandlers<MessageType>();
        if (handlers == nullptr)
            return;

        for (auto it = handlers->begin(); it != handlers->end(); ++it)
        {
            if (*it == handler)
            {
                handlers->erase(it);
                handler = nullptr;
                break;
            }
        }
    }

    template<typename MessageType>
    void RaiseMessage(MessageType message)
    {
        auto handlers = GetHandlers<MessageType>();
        if (handlers == nullptr)
            return;

        for (auto handler : *handlers)
        {
            auto func = reinterpret_cast<std::function<void(MessageType)>*>(handler->handler);
            if (func == nullptr)
                continue;

            (*func)(message);
        }
    }
    

    template<typename MessageType>
    void Clear()
    {
        auto handlers = GetHandlers<MessageType>();
        handlers->clear();
    }

    void Clear()
    {
        for (auto& handlers : message_handlers)
        {
            handlers.second.clear();
        }
        message_handlers.clear();
    }

private:

    std::map<std::type_index, std::vector<std::shared_ptr<MessageHandler>>> message_handlers;

    template<typename MessageType>
    std::vector<std::shared_ptr<MessageHandler>>* GetHandlers(bool insert_to_map_if_not_found = false)
    {
        if (message_handlers.size() == 0)
            return nullptr; 

        auto type = std::type_index(typeid(MessageType));
        auto it = message_handlers.find(type);
        if (it == message_handlers.end())
            return nullptr;

        return &(*it).second;
    }
};
