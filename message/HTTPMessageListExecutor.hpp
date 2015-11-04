#ifndef HTTPMESSAGE_LIST_EXECUTOR_HPP_
#define HTTPMESSAGE_LIST_EXECUTOR_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class HTTPMessageListExecutor : public Message
    {
    public:
    
        // Serilize Constructor
        HTTPMessageListExecutor()
            : Message( PROTOCOL_VERSION , 10200 , 0 )
        {
        }
        
        // Deserilize Constructor
        HTTPMessageListExecutor( Message* message )
            : Message( *message )
        {
        }
    
    private:
    
    }; // End of class define of HTTPMessageListExecutor

} // End of namespace Protocol
#endif // !HTTPMessage_List_Executor_HPP_
