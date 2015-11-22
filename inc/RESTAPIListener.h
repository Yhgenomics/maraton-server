/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-22
* Description:
* * * * * * * * * * * * * * * */

#ifndef REST_API_LISTENER_H_
#define REST_API_LISTENER_H_

#include "MRT.h"
#include "maraton-server.h"

class RestAPIListener :
    public MRT::Listener
{
public:

    RestAPIListener ( std::string ip );
    ~RestAPIListener( );

protected:

private:
    
    virtual MRT::Session * create_session( ) override;

    virtual void on_session_open( MRT::Session * session ) override;

    virtual void on_session_close( MRT::Session * session ) override;

};

#endif // !REST_API_LISTENER_H_
