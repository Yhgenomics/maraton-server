#include "maraton.h"

#include "SessionManager.hpp"
#include "ExecutorSession.h"
#include "UVSockService.h"
#include "HTTPSession.h"
#include "MessagesHandler.hpp"
#include "ExecutorManager.h"
#include "Executor.h"
#include "HTTPDispatcher.hpp"
#include "RESTSession.h"

using namespace std;

void timer_callback( uv_timer_t* timer )
{
    ExecutorManager::instance()->run();
}

int main()
{
    SessionManager<ExecutorSession>::instance()->on_create( 
        [] (ExecutorSession* session) {

            //=======================================
            session->on_message([] (Message* msg) {
               
                if ( Protocol::MessagesHandler::process( msg ) < 0 )
                {
                    msg->owner()->close();
                }

            } );

            //=======================================
            session->on_close( [] (ClusterSession* session) { 
                auto executor = ExecutorManager::instance()->find( session );
                ExecutorManager::instance()->pop( executor );
                printf( "Session %d closed \r\n", session->id() );
            } );

            auto executor = new Executor( session );
            ExecutorManager::instance()->push( executor );

            printf( "Session %d connected \r\n", session->id() );
        } 
    );

    SessionManager<RESTSession>::instance()->on_create(
        [] ( RESTSession* session ) {
            printf( "Rest Session %d connected \r\n", session->id() );
            session->on_message( [] ( Message* msg ) {
                Protocol::MessagesHandler::process( msg );
                msg->owner()->close();
            } );

            session->on_close( [] ( ClusterSession* session ) {
             
                printf( "Rest Session %d closed \r\n", session->id() );
            } ); 
    });

    UVSockService srv;
    srv.listen( "0.0.0.0", 80 );
    srv.listen( "0.0.0.0", 90 );

    uv_timer_t timer;
    uv_timer_init( uv_default_loop(), &timer );
    uv_timer_start( &timer, timer_callback , 0, 1 );

    srv.run();

    return 0;
}
