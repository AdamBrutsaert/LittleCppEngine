#include "MessageBus/MessageBus.h"

namespace Genesis {

    std::map<MessageID, std::vector<std::shared_ptr<MessageCallable>>> MessageBus::s_Subscribers{};
    MessageQueue MessageBus::s_Queue{1000};

    void MessageBus::Dispatch() {
        while (!s_Queue.empty()) {
            auto element = s_Queue.front();

            for (auto const& subscriber : s_Subscribers[element.id])
                (*subscriber)(element.msg);

            s_Queue.pop();
        }
    }
}
