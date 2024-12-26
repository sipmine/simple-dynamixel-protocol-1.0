#include "../dynamixel.h"

int main()
{
    uint8_t tx_buffer[10];
    dynamixel tx_str = create(0x01, 0x03, (uint8_t[PARAM_LEN]){0x01, 0x02, 0x00, 0xA0});

    create_packet(tx_buffer, tx_str);
    for (int i = 0; i < PACKET_SIZE; i++)
    {
        printf("| %hhu ", tx_buffer[i]);
    }
    printf("|\n");
    return 0;
}