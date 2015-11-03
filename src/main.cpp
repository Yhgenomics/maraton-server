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
#include "TaskManager.h"
#include "HTTPMessageResult.hpp"

using namespace std;

void timer_callback( uv_timer_t* timer )
{
    ExecutorManager::instance()->run();
    TaskManager::instance()->run();
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
                printf( "TCPSession %d closed \r\n", session->id() );
            } );

            auto executor = new Executor( session );
            ExecutorManager::instance()->push( executor );

            printf( "TCPSession %d connected \r\n", session->id() );
        } 
    );

    SessionManager<RESTSession>::instance()->on_create(
        [] ( RESTSession* session ) {

            printf( "RESTSession %d connected \r\n", session->id() );
        
			session->on_message( [] ( Message* msg ) {
                
                if ( Protocol::MessagesHandler::process( msg ) < 0 )
                {
                    Protocol::HTTPMessageResult result;
                    result.result( 1 );
                    result.message( "failed" );
                    msg->owner()->send( &result );
                }
                msg->owner()->close();
            } );

            session->on_close( [] ( ClusterSession* session ) {
             
                printf( "RESTSession %d closed \r\n", session->id() );
            } ); 
    });

    UVSockService srv;
    srv.listen( "0.0.0.0", SESSIONTYPE::RESTAPI );
    srv.listen( "0.0.0.0", SESSIONTYPE::EXECUTOR );

    uv_timer_t timer;
    uv_timer_init( uv_default_loop(), &timer );
    uv_timer_start( &timer, timer_callback , 0, 1 );

	while (true)
	{
		try
		{
			srv.run();
		}
		catch (exception ee)
		{

		}
	}

    return 0;
}
