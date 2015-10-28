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
#include "HTTPMessageListExecutorHandler.hpp"

class HTTPMessage
{
public:

    void operator()( HTTPSession * session )
    {
        session->handler()->router()->get( "/executor/list", HTTPMessageListExecutorHandler() );
        session->handler()->router()->get( "/executor/info", HTTPMessageListExecutorHandler() );
        session->handler()->router()->get( "/executor/stop", HTTPMessageListExecutorHandler() );
    }
};

#endif //!HTTP_MESSAGE_H_ 