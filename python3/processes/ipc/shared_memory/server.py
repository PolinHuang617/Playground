from multiprocessing.shared_memory import SharedMemory
import struct

# RUN_TIMES = 1000000
RUN_TIMES = 10
BUFFER_LEN = 1024
SERIAL_FORMAT = "!i{0}s".format(BUFFER_LEN)

# 64bytes
MESSAGE = "QWERTY123456789qwertyuiopasdfghjklzxcvbnm,./';\\][=-+_)(*&^%$#@!~"

iSignal = 0
data = MESSAGE * int(BUFFER_LEN / len(MESSAGE) - 1)
package = struct.pack(SERIAL_FORMAT, iSignal, data.encode("utf-8"))

counter = 0

shm = SharedMemory(name="TestSHM", create=True, size=struct.calcsize(SERIAL_FORMAT))
while counter < RUN_TIMES:
    if iSignal != 1:
        iSignal = 1
        shm.buf = package
        # print("[{0}] write text ({1} bytes) to pipe".format(counter, len(data)))
        # print("text: {0}".format(data))

        counter += 1

