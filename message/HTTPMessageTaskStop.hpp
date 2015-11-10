#ifndef HTTPMESSAGE_TASK_STOP_HPP_
#define HTTPMESSAGE_TASK_STOP_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class HTTPMessageTaskStop : public Message
    {
    public:
    
        // Getter of id_
        string id()
        {
            return id_;
        }
        
        // Setter of id_
        void id( string value )
        {
            id_ = value;
            raw_data_[ "data" ][ "id" ] = value;
        }
        
        // Serilize Constructor
        HTTPMessageTaskStop()
            : Message( PROTOCOL_VERSION , 10001 , 0 )
        {
            id( "" );
        }
        
        // Deserilize Constructor
        HTTPMessageTaskStop( Message* message )
            : Message( *message )
        {
            this->id_ = raw_data_[ "data" ][ "id" ].get<string>();
        }
    
    private:
    
        string id_;
    
    }; // End of class define of HTTPMessageTaskStop

} // End of namespace Protocol
#endif // !HTTPMessage_Task_Stop_HPP_
