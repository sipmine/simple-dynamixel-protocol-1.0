#include "../dynamixel.h"


int main(){
    uint8_t parametrs[] = {0x01, 0x02,0x00, 0xA0};
    uint8_t size =sizeof(parametrs)/sizeof(uint8_t);
    uint8_t *tx_buffer = create_packet(0x01, 0x03, parametrs, size );
    if (tx_buffer != NULL){
        for (int i = 0; i < get_package_size(get_payload_length(size));i++){
            printf("| %hhu ", tx_buffer[i]);
        }
        printf("|\n");
    } else{
        printf("tx_buffer empty\n");
    }
    free(tx_buffer);
    return 0;
}