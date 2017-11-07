#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdint.h>

//enum MessageType
//{
//	STATUS=0,
//	CONFIG,
//	TYPE_INVALID
//};

/*
 * Used for sending a message from Client to Server using tcp socket.
 *
 * msg_id     : dsp core sending the message
 * msg_type   : Describes the content of the message. see UdpMessageType
 * msg_length : Length of payload (msg) in bytes
 * msg        : The message
 */
struct ClientMessage
{
	uint32_t msg_id;
    uint32_t msg_type;
    uint32_t header_length;
    uint32_t msg_length;
    uint8_t  msg[4096];
};

typedef struct ClientMessage* ClientMessagePtr;

/*
 * Used for sending a message from Server to Client using tcp socket.
 *
 * msg_id     : dsp core sending the message
 * msg_type   : Describes the content of the message. see UdpMessageType
 * msg_length : Length of payload (msg) in bytes
 * msg        : The message
 */
struct ServerMessage
{
	uint32_t msg_id;
    uint32_t msg_type;
    uint32_t header_length;
    uint32_t msg_length;
    uint8_t  msg[4096];
};

typedef struct ServerMessage* ServerMessagePtr;

#endif
