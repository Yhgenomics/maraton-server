#include "RESTAPIListener.h"
#include "RESTAPISession.h"

RestAPIListener::RestAPIListener( std::string ip )
    : Listener( ip , RESTAPI_PORT )
{
}

RestAPIListener::~RestAPIListener( )
{
}

MRT::Session * RestAPIListener::create_session( )
{
    return new RestAPISession( );
}

void RestAPIListener::on_session_open( MRT::Session * session )
{

}

void RestAPIListener::on_session_close( MRT::Session * session )
{

}
