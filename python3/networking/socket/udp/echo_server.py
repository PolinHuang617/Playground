import socket
import time

address = ("127.0.0.1", 8000)
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as serverSocket:
    serverSocket.bind(address)
    serverSocket.settimeout(10)

    while True:
        try:
            now = time.time()
            receiveData, clientSocket = serverSocket.recvfrom(1024)
            print(time.strftime("%Y-%m-%d %H:%H:%S", time.localtime(now)))
            print("From client {0}, data: {1}".format(clientSocket,
                receiveData))

            if receiveData.decode() == "Quit" or receiveData.decode() == "quit":
                break

        except socket.timeout:
            print("Time out")
            
