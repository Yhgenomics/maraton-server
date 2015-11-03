#ifndef HTTPMESSAGE_TASK_START_HANDLER_HPP_
#define HTTPMESSAGE_TASK_START_HANDLER_HPP_

#include "HTTPMessageTaskStart.hpp"
#include "TaskManager.h"

namespace Protocol
{
    static int HTTPMessageTaskStartHandler( HTTPMessageTaskStart msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!
        HTTPMessageResult result;

        TaskDescripter* task = new TaskDescripter();
        task->aligner( msg.aligner() );
        task->args( msg.args() );
        task->fastq( msg.fastq() );
        task->id( msg.id() );
        task->executor( msg.executor() );

        if ( !TaskManager::instance()->launch( task ) )
        {
            result.result( 1 );
            result.message( TaskManager::instance()->error()  );
        }

        result.result( 0 );
        msg.owner()->send( &result );

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Task_Start_HANDLER_HPP_
