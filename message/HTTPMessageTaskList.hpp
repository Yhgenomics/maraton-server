#ifndef HTTPMESSAGE_TASK_LIST_HPP_
#define HTTPMESSAGE_TASK_LIST_HPP_

#include "Message.h"
#include "json.hpp"
#include <string>
using namespace std;

namespace Protocol
{
    class HTTPMessageTaskList : public Message
    {
    public:
    
        // Serilize Constructor
        HTTPMessageTaskList()
            : Message( PROTOCOL_VERSION , 200000 , 0 )
        {
        }
        
        // Deserilize Constructor
        HTTPMessageTaskList( Message* message )
            : Message( *message )
        {
        }
    
    private:
    
    }; // End of class define of HTTPMessageTaskList

} // End of namespace Protocol
#endif // !HTTPMessage_Task_List_HPP_
