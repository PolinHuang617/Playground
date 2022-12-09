#pragma once

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <cstdio>
#include <cstdlib>

union semun {
    int              val;    // Value for SETVAL
    struct semid_ds* buf;    // Buffer for IPC_STAT, IPC_SET
    unsigned short*  array;  // Array for GETALL, SETALL
};

int getSem(int semKey) {
    int semID = semget(semKey, 1, IPC_CREAT | 0666);

    if (semID == -1) {
        perror("Get sem failed.\n");
        exit(-1);
    } else {
        printf("sem id = %d\n", semID);
        return semID;
    }
}

bool setSem(int semID) {
    union semun semUnion;
    semUnion.val = 0;
    if (semctl(semID, 0, SETVAL, semUnion) == -1) {
        perror("Set sem failed.\n");
        return false;
    }
    return true;
}

void delSem(int semID) {
    union semun semUnion;
    if (semctl(semID, 0, IPC_RMID, semUnion) == -1) {
        perror("Delete sem failed.\n");
    }
}

void semDown(int semID) {
    struct sembuf P = {0, -1, IPC_NOWAIT};
    // struct sembuf P = {0, -1, SEM_UNDO};
    if (semop(semID, &P, 1) == -1) {
        perror("Lock sem failed.\n");
    }
}

void semUp(int semID) {
    struct sembuf V = {0, 1, IPC_NOWAIT};
    // struct sembuf V = {0, 1, SEM_UNDO};
    if (semop(semID, &V, 1) == -1) {
        perror("Unlock sem failed.\n");
    }
}

