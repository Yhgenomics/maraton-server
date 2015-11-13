#ifndef MESSAGES_HANDLER_HPP_
#define MESSAGES_HANDLER_HPP_

#include "stdlib.h"
#include "HTTPMessageCommandHandler.hpp"
#include "HTTPMessageListExecutorHandler.hpp"
#include "HTTPMessageResultHandler.hpp"
#include "HTTPMessageTaskStartHandler.hpp"
#include "HTTPMessageTaskStopHandler.hpp"
#include "MessageAbilityQueryHandler.hpp"
#include "MessageAbilityQueryACKHandler.hpp"
#include "MessageCommandHandler.hpp"
#include "MessageExceptionReportHandler.hpp"
#include "MessageGreetingHandler.hpp"
#include "MessageHeartBeatHandler.hpp"
#include "MessageIntroHandler.hpp"
#include "MessageResourcesQueryHandler.hpp"
#include "MessageResourcesQueryACKHandler.hpp"
#include "MessageStatusReportHandler.hpp"
#include "MessageTaskCancelHandler.hpp"
#include "MessageTaskContinueHandler.hpp"
#include "MessageTaskDeliverHandler.hpp"
#include "MessageTaskDeliverACKHandler.hpp"
#include "MessageTaskPauseHandler.hpp"
#include "MessageTaskProgressHandler.hpp"
#include "MessageTaskQueryHandler.hpp"
#include "MessageTaskQueryACKHandler.hpp"
#include "MessageTaskRestartHandler.hpp"
#include "MessageTaskResultHandler.hpp"

using namespace std;
namespace Protocol
{
    class MessagesHandler
    {
    public:
    
        static int process( Message* message )
        {
            switch ( message->command() )
            {
                case 10100:
                    return HTTPMessageCommandHandler( HTTPMessageCommand( message ) );
                    break;
                
                case 10200:
                    return HTTPMessageListExecutorHandler( HTTPMessageListExecutor( message ) );
                    break;
                
                case 19999:
                    return HTTPMessageResultHandler( HTTPMessageResult( message ) );
                    break;
                
                case 10000:
                    return HTTPMessageTaskStartHandler( HTTPMessageTaskStart( message ) );
                    break;
                
                case 10001:
                    return HTTPMessageTaskStopHandler( HTTPMessageTaskStop( message ) );
                    break;
                
                case 101:
                    return MessageAbilityQueryHandler( MessageAbilityQuery( message ) );
                    break;
                
                case 102:
                    return MessageAbilityQueryACKHandler( MessageAbilityQueryACK( message ) );
                    break;
                
                case 166:
                    return MessageCommandHandler( MessageCommand( message ) );
                    break;
                
                case 151:
                    return MessageExceptionReportHandler( MessageExceptionReport( message ) );
                    break;
                
                case 91:
                    return MessageGreetingHandler( MessageGreeting( message ) );
                    break;
                
                case 161:
                    return MessageHeartBeatHandler( MessageHeartBeat( message ) );
                    break;
                
                case 92:
                    return MessageIntroHandler( MessageIntro( message ) );
                    break;
                
                case 111:
                    return MessageResourcesQueryHandler( MessageResourcesQuery( message ) );
                    break;
                
                case 112:
                    return MessageResourcesQueryACKHandler( MessageResourcesQueryACK( message ) );
                    break;
                
                case 141:
                    return MessageStatusReportHandler( MessageStatusReport( message ) );
                    break;
                
                case 144:
                    return MessageTaskCancelHandler( MessageTaskCancel( message ) );
                    break;
                
                case 143:
                    return MessageTaskContinueHandler( MessageTaskContinue( message ) );
                    break;
                
                case 131:
                    return MessageTaskDeliverHandler( MessageTaskDeliver( message ) );
                    break;
                
                case 132:
                    return MessageTaskDeliverACKHandler( MessageTaskDeliverACK( message ) );
                    break;
                
                case 142:
                    return MessageTaskPauseHandler( MessageTaskPause( message ) );
                    break;
                
                case 134:
                    return MessageTaskProgressHandler( MessageTaskProgress( message ) );
                    break;
                
                case 121:
                    return MessageTaskQueryHandler( MessageTaskQuery( message ) );
                    break;
                
                case 122:
                    return MessageTaskQueryACKHandler( MessageTaskQueryACK( message ) );
                    break;
                
                case 145:
                    return MessageTaskRestartHandler( MessageTaskRestart( message ) );
                    break;
                
                case 133:
                    return MessageTaskResultHandler( MessageTaskResult( message ) );
                    break;
                
                default:
                    return -1;
                    break;
            } // End of switch
            
        } // End of static int process
        
    }; // End of class define of MessagesHandler
    
} // End of namespace Protocol
#endif
