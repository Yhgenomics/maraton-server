#include "Executor.h"
#include "ExecutorSession.h"

#include "MessagesHandler.hpp"

Executor::Executor( ExecutorSession * session )
{
    this->session_ = session;

    //say hello to client
    Protocol::MessageGreeting msg;
    session->send( &msg );

    this->refresh();
}

Executor::~Executor()
{

}

void Executor::operator()( ExecutorSession * session )
{
     
}

void Executor::run()
{

    if ( !this->connected() ) return;

    if ( this->check_timeout() ) return;

}

ExecutorSession * Executor::session()
{
    return this->session_;
}

bool Executor::check_timeout()
{
    int delta = Timer::tick() - this->last_update_time_;

    if ( delta > 5000)
    {
        this->last_update_time_ = Timer::tick();
        this->connected_ = false;
        this->session_->close();
        printf( "Kick %ld\r\n", this->session()->id() );
        return true;
    }

    return false;
}
