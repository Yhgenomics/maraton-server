#include "ExecutorSession.h"
#include "MessagesHandler.hpp"

ExecutorSession::ExecutorSession( )
{
}

ExecutorSession::~ExecutorSession( )
{

}

void ExecutorSession::on_message( uptr<Message> message )
{
    Protocol::MessagesHandler::process( message.get() );
}
