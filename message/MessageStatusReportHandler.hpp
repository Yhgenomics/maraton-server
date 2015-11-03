#ifndef MESSAGE_STATUS_REPORT_HANDLER_HPP_
#define MESSAGE_STATUS_REPORT_HANDLER_HPP_

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

        printf( "Executor[%s] changed into %s " , exe->id() , msg.reports() );

        return 0;
        // UserDefineHandler End 
    }
    
} // End of namespace Protocol
#endif // !Message_Status_Report_HANDLER_HPP_
