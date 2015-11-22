/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-22
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_LISTENER_H_
#define EXECUTOR_LISTENER_H_

#include <string>

#include "maraton-server.h"
#include "ExecutorSession.h"

class ExecutorListener :
    public MRT::Listener
{
public:

    ExecutorListener( std::string ip );
    ~ExecutorListener( );

protected:

private:

    virtual MRT::Session * create_session( ) override;

    virtual void on_session_open( MRT::Session * session ) override;

    virtual void on_session_close( MRT::Session * session ) override;

};

#endif // !EXECUTOR_LISTENER_H_
