import time
from multiprocessing import Process
from multiprocessing import Pipe


RUN_TIMES = 1000000
BUFFER_LEN = 10240

# 64bytes
MESSAGE = "QWERTY123456789qwertyuiopasdfghjklzxcvbnm,./';\\][=-+_)(*&^%$#@!~"

def producer(dataConnection, ctrlConnection):
    iSignal = 0
    data = MESSAGE * int(BUFFER_LEN / len(MESSAGE) - 1)

    counter = 0
    while counter < RUN_TIMES:
        if iSignal != 1:
            iSignal = 1
            dataConnection.send(data)
            # print("[{0}] write text ({1} bytes) to pipe".format(counter, len(data)))
            # print("text: {0}".format(data))

            counter += 1
        iSignal = ctrlConnection.recv()

def consumer(dataConnection, ctrlConnection):
    counter = 0
    doneSignal = 0
    start = time.time()
    while counter < RUN_TIMES:
        data = dataConnection.recv()
        if len(data) > 0:
            # print("[{0}] Current text ({1} bytes)".format(counter, len(data)))
            ctrlConnection.send(doneSignal)
            data = ""
            counter += 1
    end = time.time()
    print("Process {0} times in {1} sec".format(counter, end - start))


dataConn1, dataConn2 = Pipe(duplex=True)  # 1 for read, 2 for write
ctrlConn1, ctrlConn2 = Pipe(duplex=True)
sender = Process(target=producer, args=(dataConn2, ctrlConn1))
recver = Process(target=consumer, args=(dataConn1, ctrlConn2))

sender.start()
recver.start()

sender.join()
recver.join()

