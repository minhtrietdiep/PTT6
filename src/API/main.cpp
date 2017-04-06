#include "Thread.h"
#include "CommunicationServer.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    CommunicationServer *com = new CommunicationServer(4244);
    std::cout << "Press any key to exit" << std::endl;
    getchar();
    delete com;
    printf("asdad");

    pthread_exit(NULL);
    return 0;
}