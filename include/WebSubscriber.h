/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-22
* Description:
* * * * * * * * * * * * * * * */

#ifndef WEB_SUBSCRIBER_H_
#define WEB_SUBSCRIBER_H_

#include <string>

#include "maraton-server.h"

class WebSubscriber
{
public:

    static WebSubscriber* instance( )
    {
        static WebSubscriber* inst = nullptr;
        if ( inst == nullptr )
        {
            static WebSubscriber web;
            inst = &web;
        }
        return inst;
    }

    void task_result( std::string task_id , 
                      size_t status );
    void task_done  ( std::string task_id ,  
                      size_t start_time , 
                      size_t cast_time );
    void task_fail  ( std::string task_id , size_t error_code);
    void task_stop  ( std::string task_id , size_t error_code);
    void task_start ( std::string task_id );

private:

    WebSubscriber   ( );
    ~WebSubscriber  ( );
    
    uptr<MRT::WebClient> create_web_client  ( );
    void post_data                          ( std::string url , std::string data );
    
};

#endif // !WEB_SUBSCRIBER_H_
