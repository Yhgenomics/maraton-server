#ifndef MESSAGE_INTRO_HANDLER_HPP_
#define MESSAGE_INTRO_HANDLER_HPP_

#include "MessageIntro.hpp"
#include "ExecutorManager.h"

namespace Protocol
{
    static int MessageIntroHandler( MessageIntro msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        auto exe = ExecutorManager::instance()->find( msg.owner()->id() );
        if ( exe == nullptr )
            return -1;

        exe->ability( msg.process_100m() );
        exe->disk_size( msg.free_disk() );
        exe->memory_size( msg.free_memory() );
        exe->id( msg.uuid() );

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !Message_Intro_HANDLER_HPP_
