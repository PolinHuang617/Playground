import socket
import os

RUN_TIMES = 1000000
BUFFER_LEN = 10240

# 64bytes
MESSAGE = "QWERTY123456789qwertyuiopasdfghjklzxcvbnm,./';\\][=-+_)(*&^%$#@!~"

with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as sock:
    address = "/tmp/UDS_SOCKET"
    sock.bind(address)
    sock.listen(1)
    connection, clientAddr = sock.accept()
    with connection:
        print("Connected by", clientAddr)
        iSignal = 0
        data = MESSAGE * int(BUFFER_LEN / len(MESSAGE) - 1)

        counter = 0
        while counter < RUN_TIMES:
            if iSignal != 1:
                iSignal = 1
                connection.sendall(data.encode("utf-8"))
                # print("[{0}] write text ({1} bytes) to pipe".format(counter, len(data)))
                # print("text: {0}".format(data))

                counter += 1
            iSignal = connection.recv(BUFFER_LEN)

os.remove(address)
