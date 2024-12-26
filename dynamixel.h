#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct dynamixel
{
    uint8_t header_1;
    uint8_t header_2;
    uint8_t id;
    uint8_t length;
    uint8_t instruction;
    uint8_t parameters[4];
    uint8_t checksum;
} dynamixel;

uint8_t* create_packet(uint8_t packet_id, uint8_t instruction, uint8_t *parameters, uint8_t len);

dynamixel parse_packet(uint8_t* rx_buffer, uint8_t size_buffer);

int execute_action();

uint8_t calculate_checksum(uint8_t packet_id, uint8_t len, uint8_t param_len, uint8_t instruction, uint8_t *params);

uint8_t get_payload_length(uint8_t length_pack);

uint8_t get_package_size(uint8_t payload_size);

uint8_t get_param_length(uint8_t payload_length);

void free_structure(dynamixel*  dynamixel_cast);
