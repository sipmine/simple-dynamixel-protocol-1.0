#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct dynamixel
{
    uint8_t header_1;
    uint8_t header_2;
    uint8_t id;
    uint8_t lenght;
    uint8_t instruction;
    uint8_t error;
    uint8_t *parameters;
    uint8_t checksum;
} dynamixel;

/*
 *  Instruction list
 * */



uint8_t *write(uint8_t packet_id, uint8_t instruction, uint8_t *parameters, uint8_t len);

dynamixel read();

int action();


uint8_t checksum(uint8_t packet_id, uint8_t len,uint8_t param_len, uint8_t instruction, uint8_t *params);


uint8_t payload_length(uint8_t  lenght_pack);

uint8_t package_size(uint8_t size);