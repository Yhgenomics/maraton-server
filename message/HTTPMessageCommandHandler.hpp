#ifndef HTTPMESSAGE_COMMAND_HANDLER_HPP_
#define HTTPMESSAGE_COMMAND_HANDLER_HPP_

#include <string.h>

#include "HTTPMessageCommand.hpp"
#include "ExecutorManager.h"
#include "MessageCommand.hpp"
#include "HTTPMessageResult.hpp"

namespace Protocol
{
    static int HTTPMessageCommandHandler( HTTPMessageCommand msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!

        HTTPMessageResult result;
        result.result( 0 );

        std::string ret_data = "";
        for ( std::string exe_id : msg.executors() )
        {
            auto exe = ExecutorManager::instance()->find( exe_id );

            if ( exe == nullptr )
            {
                ret_data += "Executor " + exe_id + " not found";
                continue;
            }

            if ( exe->status() != Executor::ExecutorStatus::kIdle )
            {
                ret_data += "Executor " + exe_id + " not kIdle";
                continue;
            }

            MessageCommand cmd_msg;
            cmd_msg.command_line( msg.cmd() );
            cmd_msg.uri_list( msg.uris() );
            cmd_msg.run_as( msg.runAsUser() );

            exe->session()->send( &cmd_msg );
            ret_data += "Executor " + exe_id + " send";
        } 

        result.message( ret_data );
        msg.owner()->send( &result );

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !HTTPMessage_Command_HANDLER_HPP_
