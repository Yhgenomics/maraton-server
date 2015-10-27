#include "maraton.h"

#include "SessionManager.hpp"
#include "ExecutorSession.h"
#include "UVSockService.h"
#include "HTTPSession.h"
#include "MessagesHandler.hpp"
#include "ExecutorManager.h"

using namespace std;

void timer_callback( uv_timer_t* timer )
{
    ExecutorManager::instance()->run();
    //uv_timer_stop( timer );
}

int main()
{
    SessionManager<ExecutorSession>::instance()->on_create( 
        [] (ExecutorSession* session) {

            session->on_message([] (Message* msg) {
                    Protocol::MessagesHandler::process( msg );
            } );

            session->on_close( [] (ClusterSession* session) { 
                auto executor = ExecutorManager::instance()->find( session );
                ExecutorManager::instance()->pop( executor );
                SAFE_DELETE( executor );
            } );

            ExecutorManager::instance()->push( new Executor( session ) ); 

            printf( "Session %d connected \r\n", session->id() );
        } 
    );

    SessionManager<HTTPSession>::instance()->on_create(
        [] ( HTTPSession* session ) {
            session->handler()->router()->get( "/", 
                [] (HTTPRequest* req, HTTPResponse* rep) { 
                    rep->content_type( "application/json" );
                    rep->content( "<body><h1>Hello World!!!</h1></body>" );
                } );
            session->handler()->router()->post( "/",
                [] ( HTTPRequest* req, HTTPResponse* rep ) {
                rep->content_type( "application/json" );
                rep->content( "<body><h1>Hello POST!!!</h1></body>" );
            } );
        }
    );

    

    UVSockService srv;
    srv.listen( "0.0.0.0", 80 );
    srv.listen( "0.0.0.0", 90 );

    uv_timer_t timer;
    uv_timer_init( uv_default_loop(), &timer );
    uv_timer_start( &timer, timer_callback , 0, 1 );

    srv.run();

    return 0;
}
