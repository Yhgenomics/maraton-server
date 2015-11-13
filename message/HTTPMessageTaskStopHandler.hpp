#ifndef HTTPMESSAGE_TASK_STOP_HANDLER_HPP_
#define HTTPMESSAGE_TASK_STOP_HANDLER_HPP_

#include "HTTPMessageTaskStop.hpp"
#include "ExecutorManager.h"
#include "HTTPMessageResult.hpp"

#include "TaskDescripter.h"

namespace Protocol
{
    static int HTTPMessageTaskStopHandler( HTTPMessageTaskStop msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        HTTPMessageResult result;

        do
        { 
            auto exes = ExecutorManager::instance()->find_by_taskid( msg.id() );

            if ( exes.size() == 0 )
            {
                result.result( 1 );
                result.message( "task don't exist" );
                break;
            }

            for ( auto e : exes )
            {
                e->stop_task();
            }
           
            result.result( 0 ); 
        }
        while ( false );
     
        msg.owner()->send( &result );
        
        return 0;

        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Task_Stop_HANDLER_HPP_
