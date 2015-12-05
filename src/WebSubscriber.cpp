#include "WebSubscriber.h"
#include "WebSubscriberPathDefine.h"

uptr<MRT::WebClient> WebSubscriber::create_web_client( )
{
    uptr<MRT::WebClient> result = make_uptr( MRT::WebClient );

    result->header ( "Server" , WEB_SERVER_NAME );

    return move_ptr( result );
}

void WebSubscriber::post_data( std::string url , std::string data )
{
    auto web_cli    = this->create_web_client( );
    auto host       = MRT::Configuration::instance( )->get( CONF_KEY_WEBSUBSCRIBER );

    if ( host.empty( ) )
    {
        return;
    }

    if ( host[host.size( ) - 1] != '/' )
    {
        host += '/';
    }

    web_cli->post( host + url ,
                   data ,
                   nullptr );
}

WebSubscriber::WebSubscriber( )
{

}

WebSubscriber::~WebSubscriber( )
{

}

void WebSubscriber::task_result( std::string task_id , size_t status )
{
    std::string url = WS_TASK_RESULT;

    MRT::json j;
    j["task_id"] = task_id;
    j["status"]  = status;

    this->post_data( url , j.dump( ) );
}

void WebSubscriber::task_done( std::string task_id ,
                               size_t start_time ,
                               size_t cast_time )
{
    std::string url = WS_TASK_DONE;

    MRT::json j;
    j["task_id"]    = task_id;
    j["start_time"] = start_time;
    j["time_cast"]  = cast_time;

    this->post_data( url , j.dump( ) );
}

void WebSubscriber::task_fail( std::string task_id , size_t error_code )
{
    std::string url = WS_TASK_FAIL;

    MRT::json j;
    j["task_id"]    = task_id;
    j["error_code"] = error_code;
    this->post_data( url , j.dump( ) );
}

void WebSubscriber::task_stop( std::string task_id , size_t error_code )
{
    std::string url = WS_TASK_STOP;

    MRT::json j;
    j["task_id"]    = task_id;
    j["error_code"] = error_code;
    this->post_data( url , j.dump( ) );
}

void WebSubscriber::task_start( std::string task_id )
{
    std::string url = WS_TASK_START;

    MRT::json j;
    j["task_id"]    = task_id;
    this->post_data( url , j.dump( ) );
}
