#ifndef HTTPMESSAGE_LIST_EXECUTOR_HANDLER_HPP_
#define HTTPMESSAGE_LIST_EXECUTOR_HANDLER_HPP_

#include "HTTPMessageListExecutor.hpp"
#include "ExecutorManager.h"
#include "json.hpp"
#include "HTTPMessageResult.hpp"

namespace Protocol
{
    static int HTTPMessageListExecutorHandler( HTTPMessageListExecutor msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        HTTPMessageResult result;
        result.result( 0 );

        auto list = ExecutorManager::instance()->list();
        nlohmann::json json;

        for ( auto exe : list )
        {
            nlohmann::json json_exe;
            json_exe["id"] = exe->id();
            json_exe["status"] = exe->status();
            json_exe["mem"] = exe->memory_size();
            json_exe["disk"] = exe->disk_size();
            json_exe["ability"] = exe->ability();
            json_exe["task_id"] = exe->current_task() == nullptr ? "" : exe->current_task()->id();
            json.push_back( json_exe );
        }

        result.object( json.dump() );
        msg.owner()->send( &result );

        return 0;

        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_List_Executor_HANDLER_HPP_
