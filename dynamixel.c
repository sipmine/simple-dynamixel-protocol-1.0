#include "dynamixel.h"

uint8_t *create_packet(uint8_t packet_id, uint8_t instruction, uint8_t *parameters, uint8_t param_len)
{
    uint8_t payload_size = get_payload_length(param_len);
    uint8_t crc = calculate_checksum(packet_id, payload_size, param_len, instruction, parameters);

    uint8_t packet_size = param_len + 6;

    uint8_t *packet = (uint8_t *)malloc(packet_size * sizeof(uint8_t));
    if (packet == NULL)
    {
        return NULL;
    }

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = packet_id;
    packet[3] = payload_size;
    packet[4] = instruction;

    for (int i = 0; i < param_len; i++)
    {
        packet[i + 5] = parameters[i];
    }

    packet[packet_size-1] = crc;
    return packet; 
}

dynamixel parse_packet(uint8_t *rx_buffer, uint8_t size_buffer)
{
    uint8_t crc_sum = calculate_checksum(rx_buffer[2]+1, rx_buffer[3], get_param_length(rx_buffer[3]),rx_buffer[4], &rx_buffer[5] ) ;
    dynamixel result;
    
    result.header_1 = rx_buffer[0];
    result.header_2 = rx_buffer[1];
    result.id = rx_buffer[2];
    result.length = rx_buffer[3];
    result.instruction = rx_buffer[4];
    for (int i = 0; i < get_param_length(rx_buffer[3]); i++)
    {
        result.parameters[i] = rx_buffer[i+5];
    }
    result.checksum = rx_buffer[size_buffer-1];

    return result;
}

uint8_t calculate_checksum(uint8_t packet_id, uint8_t len, uint8_t param_len, uint8_t instruction, uint8_t *params)
{
    uint8_t checksum = packet_id + len + instruction;

    for (int i = 0; i < param_len; i++)
    {
        checksum += params[i];
    }

    checksum = ~checksum;

    return checksum;
}
uint8_t get_payload_length(uint8_t param_len)
{
    return param_len + 2;
}

uint8_t get_package_size(uint8_t payload_size)
{
    return payload_size + 4;
}

uint8_t get_param_length(uint8_t payload_length){
    return payload_length - 2;
}

void free_structure(dynamixel *dynamixel_cast)
{
    free(dynamixel_cast->parameters);
    free(dynamixel_cast);
}