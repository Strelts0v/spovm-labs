#ifdef __linux
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>        //mkfile
#include <student_linux.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#endif

#ifdef WIN32 || WIN64
#include"Student_windows.h"
#include<Windows.h>
#include<conio.h>
#endif

#include<iostream>
using namespace std;

#define FIFO_NAME "/tmp/named_pipe"
#define SEMAPHORE_NAME "/my_named_semaphore"

int main()
{
    #ifdef __linux

    sem_t *mutex;                                       // declare semaphore structure

    // initialize existing semaphore
    mutex = sem_open(SEMAPHORE_NAME,0,0644,0);
    if(mutex == SEM_FAILED)
    {
        perror("reader:unable to execute semaphore");
        sem_close(mutex);
        exit(-1);
    }

    // waiting for access according semaphore logic,
    // if semaphore is busy process will wait, while another process will hold it
    sem_wait(mutex);

    Student_linux student;                              // declare student object
    if(!student.connectToPipe(string(FIFO_NAME)))       // try connect to pipe
    {
        return -1;
    }

    vector<string> labs;
    labs.push_back("spovm");                            // uploading labs
    labs.push_back("apk");
    labs.push_back("cpp");
    student.completeLab(labs);
    student.closeConnectionToPipe();

    // free semaphore for other processes
    sem_post(mutex);

    #endif

    #ifdef WIN32
    char c;

    HANDLE hSemServer = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemServer"));
    HANDLE hSemClient = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemClient"));
    HANDLE hOutEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("event"));
    cout << "Studen procces" << endl;

    Sleep(5000);
    Student_windows student;
    student.setAnsTutorEvent("ansTutorEvent");
    student.setCheckLabsEvent("checkLabsEvent");
    student.setSemaphore("semaphore");
    cout << "Hello baby" << endl;
    student.connectToPipe("\\\\.\\pipe\\demo_Pipe");
    vector<string> labs;
    labs.push_back("apc");
    labs.push_back("cpp");
    student.completeLab(labs);

    cout << "The data are read by the server." << endl;
    cout << "Press any char to finish the server: ";
    cin >> c;
    #endif

    return 0;
}
