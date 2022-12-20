import socket
import time

address = ("127.0.0.1", 8000)
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as clientSocket:
    while True:
        start = time.time()
        print(time.strftime("%Y-%m-%d %H:%H:%S", time.localtime(start)))
        message = input("Client 127.0.0.1, input message to send:")
        clientSocket.sendto(message.encode("utf-8"), address)

        if message == "Quit" or message == "quit":
            break

        now = time.time()
        runTime = now - start
        print(time.strftime("%Y-%m-%d %H:%H:%S", time.localtime(now)))
        print("Run time: {0} sec\n".format(runTime))

