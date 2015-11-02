/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       :
* Description:
* * * * * * * * * * * * * * * */

#ifndef HTTP_MESSAGE_EXECUTOR_LIST_H_
#define HTTP_MESSAGE_EXECUTOR_LIST_H_ 

#include "maraton.h"
#include "HTTPMessageHandler.hpp"
#include "ExecutorManager.h"

class HTTPMessageExecutorListHandler :
    public HTTPMessageHandler
{
protected:

    virtual void on_request( HTTPRequest * req, HTTPResponse * rep ) override
    {
        auto list = ExecutorManager::instance()->list();
        nlohmann::json result = nlohmann::json::array();

        for ( auto exe : list )
        {
            nlohmann::json json;
            json["id"] = exe->id();
            json["status"] = exe->status();
            json["mem"] = exe->memory_size();
            json["disk"] = exe->disk_size();
            json["ability"] = exe->ability();
            json["host"] = "";
            json["task_id"] = "";
            json["task_percent"] = 0;
            result.push_back( json );
        }
        
        result_ok( result );
    };
};

#endif //!HTTP_MESSAGE_EXECUTOR_LIST_H_ 