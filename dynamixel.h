#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define PARAM_LEN 4
#define PACKET_SIZE 10
typedef struct dynamixel
{
    uint8_t header_1;
    uint8_t header_2;
    uint8_t id;
    uint8_t length;
    uint8_t instruction;
    uint8_t parameters[PARAM_LEN];
    uint8_t checksum;
} dynamixel;

dynamixel create(uint8_t id,uint8_t instruction, uint8_t *params);

void create_packet(uint8_t* buf,dynamixel packet);

dynamixel parse_packet(uint8_t* rx_buffer, uint8_t size_buffer);

int execute_action();

uint8_t calculate_checksum(uint8_t packet_id, uint8_t len, uint8_t instruction, uint8_t *params);
