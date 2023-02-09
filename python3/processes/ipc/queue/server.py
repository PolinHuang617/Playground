from multiprocessing import Process
from multiprocessing import Queue
import struct
import time

# RUN_TIMES = 1000000
RUN_TIMES = 10
BUFFER_LEN = 1024
SERIAL_FORMAT = "!i{0}s".format(BUFFER_LEN)

# 64bytes
MESSAGE = "QWERTY123456789qwertyuiopasdfghjklzxcvbnm,./';\\][=-+_)(*&^%$#@!~"

def write(queue):
    iSignal = 0
    data = MESSAGE * int(BUFFER_LEN / len(MESSAGE) - 1)

    counter = 0
    while counter < RUN_TIMES:
        if iSignal != 1:
            iSignal = 1
            package = struct.pack(SERIAL_FORMAT, iSignal, data.encode("utf-8"))
            queue.put(package)
            print("[{0}] write text ({1} bytes) to pipe".format(counter, len(data)))
            print("text: {0}".format(data))

            counter += 1
        package = queue.get(True)
        iSignal = int(struct.unpack_from("!i", buffer=package, offset=0))

def read(queue):
    counter = 0
    start = time.time()
    while counter < RUN_TIMES:
        data = queue.get(True)
        doneSignal, data = struct.unpack(SERIAL_FORMAT, data)
        if len(data) > 0:
            print("[{0}] Current text ({1} bytes)".format(counter, len(data)))
            print("text: {0}".format(data.decode("utf-8")))
            doneSignal = 0
            package = struct.pack("!i", doneSignal)
            queue.put(package)

            counter += 1
    end = time.time()
    print("Process {0} times in {1} sec".format(counter, end - start))

queue = Queue()
writer = Process(target=write, args=(queue,))
reader = Process(target=read, args=(queue,))

writer.start()
reader.start()

writer.join()
reader.join()
