#ifndef MESSAGE_HEART_BEAT_HANDLER_HPP_
#define MESSAGE_HEART_BEAT_HANDLER_HPP_

#include "MessageHeartBeat.hpp"
#include "ExecutorManager.h"
#include "Executor.h"

namespace Protocol
{
    static int MessageHeartBeatHandler( MessageHeartBeat msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!
        auto exe = ExecutorManager::instance()->find( msg.owner()->id() );
        if ( exe == nullptr ) return -1;

        exe->refresh();

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !Message_Heart_Beat_HANDLER_HPP_
