#ifndef MESSAGE_TASK_RESULT_HANDLER_HPP_
#define MESSAGE_TASK_RESULT_HANDLER_HPP_

#include "MessageTaskResult.hpp"
#include "ExecutorManager.h"
#include "TaskManager.h"
#include "maraton-server.h"

namespace Protocol
{
    static int MessageTaskResultHandler( MessageTaskResult msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!
        auto exe = ExecutorManager::instance( )->find( msg.owner( )->id( ) );
        auto task = TaskManager::instance( )->find( msg.task_id( ) );

        if ( nullptr == task )
        {
            return 0;
        }

        if ( nullptr == exe )
        {
            return 0;
        }

        switch ( msg.error( ) )
        {
            case 0:
                {
                    task->finish( exe );
                    exe->current_task( nullptr );
                }
                break;
            default:
                break;
        }

        return 0;
        // UserDefineHandler End 
    }
} // End of namespace Protocol
#endif // !Message_Task_Result_HANDLER_HPP_
