#ifndef HTTPMESSAGE_TASK_LIST_HANDLER_HPP_
#define HTTPMESSAGE_TASK_LIST_HANDLER_HPP_

#include "HTTPMessageTaskList.hpp"
#include "HTTPMessageResult.hpp"
#include "TaskManager.h"

namespace Protocol
{
    static int HTTPMessageTaskListHandler( HTTPMessageTaskList msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!
        HTTPMessageResult result;
        result.result( 0 );

        //auto list = TaskManager::instance()->
        //nlohmann::json json;

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Task_List_HANDLER_HPP_
 