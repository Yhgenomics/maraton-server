#ifndef HTTPMESSAGE_TASK_START_HANDLER_HPP_
#define HTTPMESSAGE_TASK_START_HANDLER_HPP_

#include "HTTPMessageTaskStart.hpp"
#include "TaskManager.h"
#include "ExecutorManager.h"
#include "MRT.h"

namespace Protocol
{
    static int HTTPMessageTaskStartHandler( HTTPMessageTaskStart msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        uptr<HTTPMessageResult> result = make_uptr( HTTPMessageResult );
          
        TaskDescripter* task = new TaskDescripter();
        task->aligner( msg.aligner() );
        task->args( msg.args() );
        task->fastq( msg.fastq() );
        task->id( msg.id() );
        task->executor( msg.executor() );
        task->reference( "hg19.fa" );

        auto err = TaskManager::instance()->launch( task );
       
        result->result( static_cast< int >( err.code() ) );
        result->message( err.message() );

        msg.owner()->send_message( move_ptr(result) );

        return 0;

        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Task_Start_HANDLER_HPP_
