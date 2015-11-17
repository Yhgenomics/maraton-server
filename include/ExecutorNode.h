/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-17
* Description:
* * * * * * * * * * * * * * * */

#ifndef EXECUTOR_NODE_H_
#define EXECUTOR_NODE_H_

#include "maraton-framework.h"

class ExecutorNode : 
    public ClusterNode
{
public:

    ExecutorNode( Session* session );
    virtual ~ExecutorNode();

protected:
    virtual void on_message ( UPTR<Message> msg );
    virtual void on_close   ( );
};

#endif // !EXECUTOR_NODE_H_
