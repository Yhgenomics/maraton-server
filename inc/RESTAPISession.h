/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-22
* Description:
* * * * * * * * * * * * * * * */

#ifndef REST_API_SESSION_H_
#define REST_API_SESSION_H_

#include "MRT.h"
#include "ClusterSession.h"

class Message;

class RestAPISession : 
    public ClusterSession
{
public:

    RestAPISession( );
    ~RestAPISession( );

    virtual void send_message ( uptr<Message> message ) override;

protected:

    void response_404( );

    virtual void on_message ( uptr<Message> message )   override;
    virtual void on_connect ( )                         override;
    virtual void on_read    ( uptr<MRT::Buffer> data )  override;
    virtual void on_write   ( uptr<MRT::Buffer> data )  override;
    virtual void on_close   ( )                         override;

private:

    MRT::HTTPRequest req;
    
    void try_handle_message( );

};

#endif // !REST_API_SESSION_H_
