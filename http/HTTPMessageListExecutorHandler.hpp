/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef HTTP_MESSAGE_LIST_EXECUTOR_H_
#define HTTP_MESSAGE_LIST_EXECUTOR_H_ 

#include "HTTPMessageHandler.hpp"

class HTTPMessageListExecutorHandler :
    public HTTPMessageHandler
{
protected:

    virtual void on_request( HTTPRequest * req, HTTPResponse * rep ) override
    {
        rep->content( "{\"abd\":1}" );
    };
};

#endif //!HTTP_MESSAGE_LIST_EXECUTOR_H_ 