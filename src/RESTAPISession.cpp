#include "RESTAPISession.h"
#include "MessagesHandler.hpp"
#include "Message.h"

RestAPISession::RestAPISession( )
{
}

RestAPISession::~RestAPISession( )
{
}

void RestAPISession::send_message( uptr<Message> message )
{
    MRT::HTTPResponse rep;
    rep.status( 200 );
    rep.header( "Server" , WEB_SERVER_NAME );
    rep.header( "Connection" , "Close" );

    auto content = message->to_bytes( );
    rep.content( move_ptr( content ) );

    auto head = rep.build_header( );
    auto body = rep.build_body( );

    this->send( move_ptr( head ) );
    this->send( move_ptr( body ) );

    this->close( );
}

void RestAPISession::response_404( )
{
    MRT::HTTPResponse rep;
    rep.status( 200 );
    rep.header( "Server" , WEB_SERVER_NAME );
    rep.header( "Connection" , "Close" );
    rep.content( make_uptr(MRT::Buffer , "<html><body><h1>Welcome to Maraton Server</h1></body></html>" ));
    auto head = rep.build_header( );
    auto body = rep.build_body( );

    this->send( move_ptr( head ) );
    this->send( move_ptr( body ) );

    this->close( );
}

void RestAPISession::on_message( uptr<Message> message )
{
    Protocol::MessagesHandler::process( message.get( ) );
}

void RestAPISession::on_connect( )
{

}

void RestAPISession::on_read( uptr<MRT::Buffer> data )
{
    req.parse( move_ptr( data ) );
    this->try_handle_message( );
}

void RestAPISession::on_write( uptr<MRT::Buffer> data )
{
}

void RestAPISession::on_close( )
{

}

void RestAPISession::try_handle_message( )
{
    if ( req.content_length( ) <= 0 )
    {
        this->response_404( );
        return;
    }

    auto body = req.content( );

    if ( body == nullptr )
    {
        this->response_404( );
        return;
    }

    try
    {
         uptr<Message> msg = make_uptr( Message , std::string( body->data( ) , body->size( ) ) );
         msg->owner( this );
         this->on_message( move_ptr( msg ) );
    }
    catch(...)
    {
        this->response_404( );
    }
   
}
