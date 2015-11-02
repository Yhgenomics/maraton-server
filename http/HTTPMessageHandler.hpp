/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */

#ifndef HTTP_MESSAGE_HANDLER_H_
#define HTTP_MESSAGE_HANDLER_H_ 

#include "maraton.h"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class HTTPMessageHandler
{
public:

    HTTPMessageHandler() {}
    void operator()( HTTPRequest* req, HTTPResponse* rep )
    {
        this->rep = rep;
        
        set_header( rep );
        on_request( req, rep );
    }; 

protected:
    
    virtual void set_header( HTTPResponse* rep ) 
    {
        rep->header( "Content-Type","application/json" );
    };

    virtual void on_request( HTTPRequest* req, HTTPResponse* rep ) = 0;

    void result_ok( nlohmann::json& json )
    {
        nlohmann::json result;
        result["error"] = 0;
        result["message"] = "";
        result["data"] = json;

        rep->content( result.dump() );
    }

    void result_fail(int error, std::string message )
    {
        nlohmann::json result;
        result["error"] = error;
        result["message"] = message;
        result["data"] = nullptr;

        rep->content( result.dump() );
    }


private:

    HTTPResponse* rep;

};

#endif //!HTTP_MESSAGE_HANDLER_H_ 