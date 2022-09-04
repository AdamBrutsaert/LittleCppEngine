#pragma once

#include <map>
#include <vector>

#include "Message.h"
#include "MessageQueue.h"
#include "MessageSubscriber.h"

namespace Genesis {

    class MessageBus {
    public:
        template <typename M> 
        static void Register(MessageSubscriber<M> const& subscriber) {
            s_Subscribers[GetMessageID<M>()].push_back(subscriber);
        }

        template <typename M, typename F> 
        static MessageSubscriber<M> Subscribe(F&& func) {
            auto subscriber = MakeMessageSubscriber<M, F>(std::forward<F>(func));
            Register(subscriber);
            return subscriber;
        }

        template <typename M> 
        static void Remove(MessageSubscriber<M> const& subscriber) {
            auto &v = s_Subscribers[GetMessageID<M>()];
            // TODO - Swap to the end and pop instead
            v.erase(std::remove(v.begin(), v.end(), subscriber), v.end());
        }

        template <typename M> 
        static void Send(M&& msg) {
            s_Queue.push({&msg, sizeof(msg), GetMessageID<M>()});
        }

        template <typename M, typename... Args> 
        static void Send(Args&&... args) {
            Send<M>({std::forward<Args>(args)...});
        }

    private:
        friend class Application;
        static void Dispatch();


        // TODO - Add priorities
        static std::map<MessageID, std::vector<std::shared_ptr<MessageCallable>>> s_Subscribers;
        static MessageQueue s_Queue;
    };

}
