#ifndef HTTPMESSAGE_TASK_START_HANDLER_HPP_
#define HTTPMESSAGE_TASK_START_HANDLER_HPP_

#include "HTTPMessageTaskStart.hpp"
#include "TaskManager.h"
#include "ExecutorManager.h"

namespace Protocol
{
    static int HTTPMessageTaskStartHandler( HTTPMessageTaskStart msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        DEF_UPTR( HTTPMessageResult , result );

        TaskDescripter* task = new TaskDescripter();
        task->aligner( msg.aligner() );
        task->args( msg.args() );
        task->fastq( msg.fastq() );
        task->id( msg.id() );
        task->executor( msg.executor() );

        auto err = TaskManager::instance()->launch( task );
       
        result->result( static_cast< int >( err.code() ) );
        result->message( err.message() );

        msg.owner()->send( MOVE(result) );

        return 0;

        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Task_Start_HANDLER_HPP_
