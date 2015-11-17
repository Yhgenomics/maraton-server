/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-17
* Description:
* * * * * * * * * * * * * * * */

#ifndef MASTER_FEATURE_H_
#define MASTER_FEATURE_H_

#include <string>
#include "maraton-framework.h"

class MasterFeature : 
    public MasterBaseFeature
{
public:

    MasterFeature( std::string host );
    virtual ~MasterFeature();

protected:

    virtual SPTR<ClusterNode> create_node( Session * session ) override;
    virtual void on_new_clusternode( SPTR<ClusterNode> node ) override;
    virtual void on_close_clusternode( SPTR<ClusterNode> node ) override;
};

#endif // !MASTER_FEATURE_H_
