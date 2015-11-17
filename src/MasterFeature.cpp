#include "MasterFeature.h"
#include "ExecutorNode.h"

MasterFeature::MasterFeature( std::string host )
    : MasterBaseFeature( host)
{
    this->service_->listen( this->host_.c_str() , this->port_ );
}

MasterFeature::~MasterFeature()
{
}

SPTR<ClusterNode> MasterFeature::create_node( Session * session )
{
    return MAKE_SPTR(ExecutorNode,session);
}

void MasterFeature::on_new_clusternode( SPTR<ClusterNode> node )
{

}

void MasterFeature::on_close_clusternode( SPTR<ClusterNode> node )
{

}
