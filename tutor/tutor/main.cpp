#ifdef __linux
#include <iostream>
#include <sys/stat.h>
#include <tutor_linux.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#endif

#ifdef WIN32 || WIN64
#include <windows.h>
#include <stdio.h>
#include"Tutor_windows.h"
#include <conio.h>
#include <iostream>
#endif

using namespace std;

#define FIFO_NAME "/tmp/named_pipe"
#define STUDENTS_COUNT 3

int main()
{
    #ifdef __linux

    vector<string> subjects;
    subjects.push_back("spovm");
    subjects.push_back("cpp");
    Tutor_linux tutor(subjects);

    if(!tutor.connectToPipe(string(FIFO_NAME))){    // try to connect to pipe
        return -1;
    }
    // check labs and wait for students
    for(int i = 0; i < STUDENTS_COUNT; i++)
    {
        sleep(2);
        tutor.checkLabs();
    }
    tutor.closeConnectionToPipe();
    #endif

    #ifdef WIN32 || WIN64
    char c;
    Tutor_windows tutor;

    cout << "tutor procces" << endl;
    tutor.connectToPipe("\\\\.\\pipe\\demo_Pipe");
    tutor.setAnsTutorEvent("ansTutorEvent");
    tutor.setCheckLabsEvent("checkLabsEvent");
    tutor.setSemaphore("semaphore");
    while(1)
    tutor.checkLabs();
    #endif

    return 0;
}

