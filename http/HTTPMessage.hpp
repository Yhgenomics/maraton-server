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

class HTTPMessage
{
public:

    void operator()( HTTPSession * session )
    {
        session->handler()->router()->get( "/executor/list", HTTPMessageExecutorListHandler() );
        session->handler()->router()->get( "/executor/info", HTTPMessageExecutorListHandler() );
        session->handler()->router()->get( "/executor/stop", HTTPMessageExecutorListHandler() );
    };

};

#endif //!HTTP_MESSAGE_H_ 