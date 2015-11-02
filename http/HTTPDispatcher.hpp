/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */

#ifndef HTTP_MESSAGE_H_
#define HTTP_MESSAGE_H_ 

#include "HTTPSession.h"
#include "HTTPMessageHandler.hpp"
#include "HTTPMessageExecutorListHandler.hpp"
#include "HTTPMessageTaskListHandler.hpp"
#include "HTTPMessageRootHandler.hpp"

class HTTPDispatcher
{
public:

    void operator()( HTTPSession * session )
    {
        session->handler()->router()->get( "/", HTTPMessageRootHandler() );
        
        session->handler()->router()->get( "/executor/list", HTTPMessageExecutorListHandler() );
        session->handler()->router()->get( "/executor/info", HTTPMessageExecutorListHandler() );
        session->handler()->router()->get( "/executor/stop", HTTPMessageExecutorListHandler() );

        session->handler()->router()->get( "/task/list", HTTPMessageTaskListHandler() );

    };

};

#endif //!HTTP_MESSAGE_H_ 