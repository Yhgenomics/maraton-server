#include <stdio.h>

#include "maraton.h"

#include "SessionManager.hpp"
#include "ExecutorSession.h"
#include "UVSockService.h"
#include "HTTPSession.h"
#include "MessagesHandler.hpp"
#include "ExecutorManager.h"
#include "Executor.h" 
#include "RESTSession.h"
#include "TaskManager.h"
#include "HTTPMessageResult.hpp"

#include "uv.h"

using namespace std;

#define STDIN   0
#define STDOUT  1
#define STDERR  2

void timer_callback( uv_timer_t* timer )
{
    ExecutorManager::instance()->run();
    TaskManager::instance()->run();
}
static void on_process_exit( uv_process_t* process , int64_t exit_status , int term_signal )
{
    printf( "Process exited with status %lld, signal %d\n" , exit_status , term_signal );
    uv_close( ( uv_handle_t* ) process , NULL );
}

static char stdio_buffer[1024] = { 0 };

static void on_alloc(
    uv_handle_t* handle ,
    size_t suggested_size ,
    uv_buf_t* buf )
{
    buf->base = stdio_buffer;
    buf->len = 1024;
}
static void on_read( 
    uv_stream_t* stream ,
    ssize_t nread ,
    const uv_buf_t* buf )
{
    printf( "%s\r\n" , buf->base );
}

static uv_process_t process;
static uv_process_options_t process_options;
static uv_stdio_container_t child_stdio[3];

int main(int argc,char** argv)
{ 
   char *args[3] = { "dir", NULL };

    memset( &process , 0 , sizeof( process ) );
    memset( &process_options , 0 , sizeof( process_options ) );

    uv_stdio_container_t child_stdio[3];
    child_stdio[STDIN].flags = UV_IGNORE;
    child_stdio[STDOUT].flags = UV_IGNORE;
    child_stdio[STDERR].flags = UV_INHERIT_FD;
    child_stdio[STDERR].data.fd = STDERR;

    process_options.file = "cmd.exe";
    process_options.args = args;
    process_options.exit_cb = on_process_exit;
    process_options.stdio_count = 3;
    process_options.stdio = child_stdio;


    auto r = uv_spawn( uv_default_loop() , &process , &process_options );
    //uv_read_start( container.data.stream , on_alloc , on_read );
    if ( r )
    {
        printf( "Execute errors!....\r\n" );
    }


    return uv_run( uv_default_loop() , UV_RUN_DEFAULT );

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
                Logger::sys( "TCPSession %d closed", session->id() );
            } );

            auto executor = new Executor( session );
            ExecutorManager::instance()->push( executor );

            Logger::sys( "TCPSession %d connected", session->id() );
        } 
    );

    SessionManager<RESTSession>::instance()->on_create(
        [] ( RESTSession* session ) {

            Logger::sys( "RESTSession %d connected", session->id() );
        
			session->on_message( [] ( Message* msg ) {
                
                if ( Protocol::MessagesHandler::process( msg ) < 0 )
                {
                    Protocol::HTTPMessageResult result;
                    result.result( 1 );
                    result.message( "failed" );
                    msg->owner()->send( &result );
                }
                //msg->owner()->close();
            } );

            session->on_close( [] ( ClusterSession* session ) {
             
                Logger::sys( "RESTSession %d closed", session->id() );
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
