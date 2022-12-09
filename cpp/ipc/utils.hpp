#pragma once

#include <cstdlib>
#include <cstring>

#include <string>

// constexpr size_t RUN_TIMES = 32768;  // 当RUN_TIMES > 32767时，sem使用SEM_UNDO会无法set
// constexpr size_t RUN_TIMES = 2;
constexpr size_t RUN_TIMES = 1000000;
constexpr size_t BUFFER_LEN = 10240;
constexpr size_t PORT = 8000;

// 64bytes
const std::string message = "QWERTY123456789qwertyuiopasdfghjklzxcvbnm,./';\\][=-+_)(*&^%$#@!~";

struct Data {
    size_t iSignal;
    char buffer[BUFFER_LEN];

    // Data() {
    //     iSignal = 0;
    //     buffer = new char[BUFFER_LEN];
    //     memset(buffer, 0, BUFFER_LEN);
    // }

    // ~Data() {
    //     delete buffer;
    // }
};
