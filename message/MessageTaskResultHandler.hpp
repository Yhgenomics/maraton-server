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

        switch ( msg.stage( ) )
        {
            // Alignment finish
            case 1:
                {
                    task->alignment_finish( exe );
                }
                break;
            // Merge finish
            case 2:
                {
                    task->merge_finish( msg.error( ) );
                }
                break;
            default:
                {
                     task->fail( msg.error( ) );
                }
                break;
        }

        return 0;
        // UserDefineHandler End 
    }
} // End of namespace Protocol
#endif // !Message_Task_Result_HANDLER_HPP_
