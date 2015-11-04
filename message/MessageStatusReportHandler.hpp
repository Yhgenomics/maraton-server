#ifndef MESSAGE_STATUS_REPORT_HANDLER_HPP_
#define MESSAGE_STATUS_REPORT_HANDLER_HPP_

#include "maraton-server.h"
#include "MessageStatusReport.hpp"
#include "ExecutorManager.h"

namespace Protocol
{
    static int MessageStatusReportHandler( MessageStatusReport msg )
    {
        // UserDefineHandler Begin
        // Your Codes here!
        auto exe = ExecutorManager::instance()->find( msg.owner()->id() );

        if ( exe == nullptr )
            return -1;

        exe->status( ( Executor::ExecutorStatus ) atoi( msg.reports().c_str() ) );

        std::string id( exe->id() + "\0" );
        std::string reports( msg.reports() + "\0" );

        Logger::sys( "Executor[%s] changed into %s " , id.c_str() , reports.c_str() );

        return 0;
        // UserDefineHandler End 
    }

} // End of namespace Protocol
#endif // !Message_Status_Report_HANDLER_HPP_
