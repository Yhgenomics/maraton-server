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

        exe->status( static_cast< Executor::ExecutorStatus >( msg.reports( ) ) );

        LOG_DEBUG( "%lld changed status to %ld " , exe->session( )->id( ) , msg.reports( ) );

        return 0;
        // UserDefineHandler End 
    }

} // End of namespace Protocol
#endif // !Message_Status_Report_HANDLER_HPP_
