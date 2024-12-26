#include"dynamixel.h"



uint8_t* write(uint8_t packet_id, uint8_t instruction, uint8_t* parameters, uint8_t param_len) {
    uint8_t payload_size = payload_length(param_len);
    uint8_t crc = checksum(packet_id,payload_size ,param_len, instruction, parameters);

    uint8_t packet_size = param_len + 5;

    uint8_t* packet = (uint8_t*)malloc(packet_size * sizeof(uint8_t));
    if (packet == NULL) {
       perror("Packet is's null\n");
    }

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = packet_id;
    packet[3] = payload_size;  
    packet[4] = instruction;

    for (int i = 0; i < param_len; i++) {
        packet[i + 5] = parameters[i];
    }

    packet[packet_size] = crc;
    return packet;  // Возвращаем указатель на динамически выделенную память
}



dynamixel read(uint8_t* buffer)
{
    struct dynamixel result;
    result.header_1 = buffer[0];
    result.header_2 = buffer[1];
    result.id = buffer[2];
    result.lenght = buffer[3];
    result.error = buffer[4];
    result.parameters = &buffer[5];
    result.checksum = buffer[result.lenght + 3];
    return result;
}

//  id  + Lenght + instruction / error
uint8_t checksum(uint8_t packet_id, uint8_t len, uint8_t param_len, uint8_t instruction, uint8_t *params)
{
    uint8_t checksum = packet_id + len + instruction;  // Начинаем с суммы id, длины и инструкции

    // Добавляем все параметры к сумме
    for (int i = 0; i < param_len; i++) {
        checksum += params[i];
    }

    checksum = ~checksum;  // Инвертируем биты для получения финального значения

    return checksum;  // Возвращаем вычисленный контрольный знак
}
uint8_t payload_length(uint8_t  param_len){
    return param_len + 2;

}

uint8_t package_size(uint8_t size)
{
    return size + 4;
}