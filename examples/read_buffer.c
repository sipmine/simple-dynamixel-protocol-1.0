#include "dynamixel.h"
#include <stdlib.h>

int main()
{
    uint8_t rx_buff[] = {0xFF, 0xFF, 0x01, 0x06, 0x03, 0x01, 0x02, 0x00, 0xA0, 0x52};

    uint8_t crc_sum = calculate_checksum(rx_buff[2], rx_buff[3], get_param_length(rx_buff[3]),rx_buff[4], &rx_buff[5] ) ;
    if (crc_sum == rx_buff[9]){
    dynamixel rx_st = parse_packet(rx_buff, 10);
    printf("Struct\n");
    printf("h1: %hhu\n", rx_st.header_1);
    printf("h2: %hhu\n", rx_st.header_1);
    printf("id: %hhu\n", rx_st.id);
    printf("leng: %hhu\n", rx_st.length);
    printf("inst/err: %hhu\n", rx_st.instruction);
    printf("params: ");
    for (int i = 0; i < get_param_length(rx_st.length); i++)
    {
        printf("%hhu ", rx_st.parameters[i]);
    }
    printf("\n");
    printf("checksum: %hhu\n", rx_st.checksum);
    } else {
        printf("sum note correct\n");
    }
    return 0;
}