#ifndef HTTPMESSAGE_EXECUTOR_LIST_HPP_
#define HTTPMESSAGE_EXECUTOR_LIST_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class HTTPMessageExecutorList : public Message
    {
    public:
    
        // Serilize Constructor
        HTTPMessageExecutorList()
            : Message( PROTOCOL_VERSION , 100000 , 0 )
        {
        }
        
        // Deserilize Constructor
        HTTPMessageExecutorList( Message* message )
            : Message( *message )
        {
        }
    
    private:
    
    }; // End of class define of HTTPMessageExecutorList

} // End of namespace Protocol
#endif // !HTTPMessage_Executor_List_HPP_
