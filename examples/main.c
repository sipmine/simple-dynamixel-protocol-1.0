#include"dynamixel.h"


int main()
{
    uint8_t params[] = {0x01, 0x02, 0x03};
    uint8_t *tx_buff;
    tx_buff  = write(0x01, 0x03, params, 3);
    
    for (int i = 0; i < package_size(lenght(3)); i++)
    {
        printf("ind %d: ", i);
        printf("%hhu ||", tx_buff[i]);
    }
    printf("\n");
    return 0; 
}