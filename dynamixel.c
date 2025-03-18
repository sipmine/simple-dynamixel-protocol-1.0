#include "dynamixel.h"


dynamixel create(uint8_t id,uint8_t instruction, uint8_t *params){
    dynamixel result;
    result.header_1 = 0xFF;
    result.header_2 = 0xFF;
    result.id = id;
    result.length = PARAM_LEN+2;
    result.instruction = instruction;
    for (uint8_t i = 0; i < PARAM_LEN; i++){
        result.parameters[i] = params[i];
    }
    result.checksum =0;
    return result;
}

void create_packet(uint8_t *buf,dynamixel packet)
{
    uint8_t crc = calculate_checksum(packet.id,packet.length, packet.instruction, packet.parameters);
    buf[0] = packet.header_1;
    buf[1] = packet.header_2;
    buf[2] = packet.id;
    buf[3] = packet.length;
    buf[4] = packet.instruction;

    for (uint8_t i = 0; i < PARAM_LEN; i++)
    {
       buf[i + 5] = packet.parameters[i];
    }

    buf[PACKET_SIZE-1] = crc;
}

dynamixel parse_packet(uint8_t *rx_buffer, uint8_t size_buffer)
{
    dynamixel result;
    
    result.header_1 = rx_buffer[0];
    result.header_2 = rx_buffer[1];
    result.id = rx_buffer[2];
    result.length = rx_buffer[3];
    result.instruction = rx_buffer[4];
    for (uint8_t i = 0; i < PARAM_LEN; i++)
    {
        result.parameters[i] = rx_buffer[i+5];
    }

    result.checksum = rx_buffer[size_buffer-1];

    return result;
}

uint8_t calculate_checksum(uint8_t packet_id, uint8_t len, uint8_t instruction, uint8_t *params)
{
    uint8_t checksum = packet_id + len + instruction;

    for (u_int8_t i = 0; i < PARAM_LEN; i++)
    {
        checksum += params[i];
    }

    checksum = ~checksum;

    return checksum;
}