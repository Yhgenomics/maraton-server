/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */

#ifndef HTTP_MESSAGE_HANDLER_H_
#define HTTP_MESSAGE_HANDLER_H_ 

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class HTTPMessageHandler
{
public:

    HTTPMessageHandler() {}
    void operator()( HTTPRequest* req, HTTPResponse* rep )
    {
        set_header( rep );
        on_request( req, rep );
    };

protected:
    
    virtual void set_header( HTTPResponse* rep ) 
    {
    };

    virtual void on_request( HTTPRequest* req, HTTPResponse* rep ) = 0;
};

#endif //!HTTP_MESSAGE_HANDLER_H_ 