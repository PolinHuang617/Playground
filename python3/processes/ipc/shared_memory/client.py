from multiprocessing.shared_memory import SharedMemory
import struct
import time

# RUN_TIMES = 1000000
RUN_TIMES = 10
BUFFER_LEN = 1024
SERIAL_FORMAT = "!i{0}s".format(BUFFER_LEN)

counter = 0
iSignal = 0
start = time.time()
while counter < RUN_TIMES:
    data = sock.recv(BUFFER_LEN)
    if len(data) > 0:
        # print("[{0}] Current text ({1} bytes)".format(counter, len(data)))
        sock.send(str(doneSignal).encode("utf-8"))
        data = ""
        counter += 1
end = time.time()
print("Process {0} times in {1} sec".format(counter, end - start))



