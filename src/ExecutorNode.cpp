#include "ExecutorNode.h"
#include "MessagesHandler.hpp"

ExecutorNode::ExecutorNode( Session * session )
    : ClusterNode(session)
{
    UPTR<Protocol::MessageGreeting> msg = MAKE_UPTR( Protocol::MessageGreeting );
    this->send( MOVE( msg ) );
}

ExecutorNode::~ExecutorNode()
{

}

void ExecutorNode::on_message( UPTR<Message> msg )
{
    auto pmsg = msg.get();
    auto ret = Protocol::MessagesHandler::process( pmsg );
}

void ExecutorNode::on_close()
{

}
