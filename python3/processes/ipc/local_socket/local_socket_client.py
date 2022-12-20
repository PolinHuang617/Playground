import socket
import time

RUN_TIMES = 1000000
BUFFER_LEN = 10240

# 64bytes
MESSAGE = "QWERTY123456789qwertyuiopasdfghjklzxcvbnm,./';\\][=-+_)(*&^%$#@!~"

with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as sock:
    address = "/tmp/UDS_SOCKET"
    sock.connect(address)
    counter = 0
    doneSignal = 0
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


