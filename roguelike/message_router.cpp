
#include "message_router.hpp"

int MessageHandler::id_counter = 0;
std::shared_ptr<MessageRouter> MessageRouter::instance = nullptr;