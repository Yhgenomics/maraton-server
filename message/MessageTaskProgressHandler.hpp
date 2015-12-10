#ifndef MESSAGE_TASK_PROGRESS_HANDLER_HPP_
#define MESSAGE_TASK_PROGRESS_HANDLER_HPP_

#include "MessageTaskProgress.hpp"
#include "TaskManager.h"
#include "ExecutorManager.h"

namespace Protocol
{
    static int MessageTaskProgressHandler( MessageTaskProgress msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        std::string taskid  = msg.task_id();
        auto task           = TaskManager::instance()->find( taskid );
        auto executor       = ExecutorManager::instance()->find( msg.owner() );

        if ( task == nullptr )
        {
            Logger::error( "MessageTaskProgressHandler can not find task %s" , taskid.c_str() );
            return 1;
        }

        executor->progress( msg.progress() );
        task->update_progress( );
        Logger::sys( "%s progress %lld" , taskid.c_str() , msg.progress() );

        return 0;

        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !Message_Task_Progress_HANDLER_HPP_
