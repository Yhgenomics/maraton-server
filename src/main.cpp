#include "maraton.h"

#include "SessionManager.hpp"
#include "ExecutorSession.h"
#include "UVSockService.h"
#include "HTTPSession.h"
#include "MessagesHandler.hpp"
#include "ExecutorManager.h"
#include "Executor.h"
#include "HTTPMessage.hpp"

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
                auto result = Protocol::MessagesHandler::process( msg );
                if ( result < 0 )
                {
                    msg->owner()->close();
                }
            } );

            session->on_close( [] (ClusterSession* session) { 
                auto executor = ExecutorManager::instance()->find( session );
                ExecutorManager::instance()->pop( executor );
                SAFE_DELETE( executor );
            } );

            auto executor = new Executor( session );
            ExecutorManager::instance()->push( executor );

            printf( "Session %d connected \r\n", session->id() );
        } 
    );

    SessionManager<HTTPSession>::instance()->on_create( HTTPMessage() );

    UVSockService srv;
    srv.listen( "0.0.0.0", 80 );
    srv.listen( "0.0.0.0", 90 );

    uv_timer_t timer;
    uv_timer_init( uv_default_loop(), &timer );
    uv_timer_start( &timer, timer_callback , 0, 1 );

    srv.run();

    return 0;
}
