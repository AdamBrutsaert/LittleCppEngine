#include "MessageBus/MessageBus.h"

namespace Genesis {

    std::vector<std::map<MessageID, std::vector<std::shared_ptr<MessageCallable>>>> MessageBus::s_Subscribers = {
        std::map<MessageID, std::vector<std::shared_ptr<MessageCallable>>>{}
    };

    MessageQueue MessageBus::s_Queue{1000};

    void MessageBus::Dispatch() {
        while (!s_Queue.empty()) {
            auto element = s_Queue.front();

            for (auto it = s_Subscribers.begin(); it != s_Subscribers.end(); it++) {
                for (auto const& subscriber : (*it)[element.id]) {
                    (*subscriber)(element.msg);
                }
            }

            s_Queue.pop();
        }
    }
}
