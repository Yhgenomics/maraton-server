#include "WebSubscriber.h"

uptr<MRT::WebClient> WebSubscriber::create_web_client( )
{
    uptr<MRT::WebClient> result = make_uptr( MRT::WebClient );

    result->header ( "Server" , WEB_SERVER_NAME );

    return move_ptr( result );
}

void WebSubscriber::post_data( std::string url , std::string data )
{
&    auto web_cli    = this->create_web_client( );
    auto host       = MRT::Configuration::instance( )->get( CONF_KEY_CALLBACK );
     
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
    std::string url = "task/update";

    MRT::json j;
    j["task_id"] = task_id;
    j["status"]  = status;

    this->post_data( url , j.dump( ) );
}
