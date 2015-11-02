/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */

#ifndef HTTP_MESSASGE_TASK_LIST_HANDLER_H_
#define HTTP_MESSASGE_TASK_LIST_HANDLER_H_ 

#include "maraton.h"
#include "HTTPMessageHandler.hpp"

class HTTPMessageTaskListHandler :
    public HTTPMessageHandler
{
public:
    
    virtual void on_request( HTTPRequest * req, HTTPResponse * rep ) override
    {

    };

};


#endif //!HTTP_MESSASGE_TASK_LIST_HANDLER_H_ 