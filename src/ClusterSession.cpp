#include "ClusterSession.h"
#include "Message.h"

ClusterSession::ClusterSession( )
    : Session( )
{
    static size_t cluster_session_id = 10000;
    this->id_ = cluster_session_id;
    cluster_session_id = ( cluster_session_id + 1 ) % MAX_UINT;
}

size_t ClusterSession::id( )
{
    return this->id_;
}

void ClusterSession::send_message( uptr<Message> message )
{
    uptr<MRT::Buffer> header  = make_uptr( MRT::Buffer , "YH" );
    uptr<MRT::Buffer> length  = make_uptr( MRT::Buffer , 4 );
    uptr<MRT::Buffer> body    = message->to_bytes( );

    short* pshort = ( short* ) ( length->data( ) );
    *pshort = scast<short>( body->size( ) );
    ++pshort;
    *pshort = scast<short>( body->size( ) );

    this->send( move_ptr( header ) );
    this->send( move_ptr( length ) );
    this->send( move_ptr( body ) );
}

void ClusterSession::on_connect( )
{

}

void ClusterSession::on_read( uptr<MRT::Buffer> data )
{
    this->buffer_.push( move( data ) );
    this->try_pop_message( );
}

void ClusterSession::on_write( uptr<MRT::Buffer> data )
{

}

void ClusterSession::on_close( )
{

}

void ClusterSession::try_pop_message( )
{
    while ( true )
    {
        switch ( this->state_ )
        {
            case MessageParseState::Header:
                {
                    auto tmp = this->buffer_.pop( 2 );
                    if ( tmp == nullptr ) return;


                    auto kf = ( *tmp )[0];
                    auto ks = ( *tmp )[1];

                    if ( kf == 'Y' && ks == 'H' )
                    {
                        this->state_ = MessageParseState::Length;
                    }
                    else
                    {
                        this->close( );
                        return;
                    }
                }
                break;
            case MessageParseState::Length:
                {
                    auto tmp = this->buffer_.pop( 4 );

                    if ( tmp == nullptr ) return;

                    short* pshort           = ( short* ) ( tmp->data( ) );
                    this->oringal_size_     = *pshort;
                    ++pshort;
                    this->compressed_size_  = *pshort;

                    if ( this->compressed_size_ < MAX_CIRCLE_BUFFER_SIZE &&
                         this->oringal_size_ < MAX_CIRCLE_BUFFER_SIZE )
                    {
                        this->state_ = MessageParseState::Body;
                    }
                    else
                    {
                        this->state_ = MessageParseState::Header;
                        this->close( );
                        return;
                    }
                }
                break;
            case MessageParseState::Body:
                {
                    auto tmp = this->buffer_.pop( this->compressed_size_ );

                    if ( tmp == nullptr ) return;

                    try
                    {
                        auto msg = make_uptr( Message , std::string( tmp->data( ) , tmp->size( ) ) );
                        msg->owner( this );
                        this->on_message( move_ptr( msg ) );
                    }
                    catch ( ... )
                    {

                    }

                    this->state_ = MessageParseState::Header;
                }
                break;
            default:
                break;
        }
    }
}