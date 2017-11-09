#include "server.h"

const char* ClientMessageType_str(enum ClientMessageType clientMessageType)
{
  switch(clientMessageType)
  {
    case GET_JOB:            return "Get Job";
    case NORMAL_TERMINATOIN: return "Normal Termination";
    case FAIL_TERMINATION:   return "Fail Termination";
    case QUIT_PROGRAM:       return "Quit Program";
    default:                 return "Unknown";
    }
}
