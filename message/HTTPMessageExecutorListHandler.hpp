#ifndef HTTPMESSAGE_EXECUTOR_LIST_HANDLER_HPP_
#define HTTPMESSAGE_EXECUTOR_LIST_HANDLER_HPP_

#include "HTTPMessageExecutorList.hpp"
#include "RESTSession.h"

namespace Protocol
{
    static int HTTPMessageExecutorListHandler( HTTPMessageExecutorList msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        RESTSession* session = static_cast< RESTSession* >( msg.owner() );

        Message m("1.0.0",10002,0);
        session->send( &m );

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Executor_List_HANDLER_HPP_
