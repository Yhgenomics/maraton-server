/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */
#ifndef HTTP_MESSAGE_ROOT_HANDLER_H_
#define HTTP_MESSAGE_ROOT_HANDLER_H_ 

#include "HTTPMessageHandler.hpp"

class HTTPMessageRootHandler
    : public HTTPMessageHandler
{
public:

    virtual void on_request( HTTPRequest * req, HTTPResponse * rep ) override
    {
        nlohmann::json result;
        result = "RESTAPI Successfully load!";


        result_ok( result );
    }
};

#endif //!HTTP_MESSAGE_ROOT_HANDLER_H_ 