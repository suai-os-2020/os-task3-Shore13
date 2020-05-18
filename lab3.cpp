#include "lab3.h"
#include <windows.h>
#include <iostream>

#define THREADS_COUNT 11
#define LETTERS_COUNT 3

DWORD ThreadID;
// идентификаторы потоков
HANDLE hThread[THREADS_COUNT];
// мьютекс для синхронизации доступа в критическую секцию
HANDLE hLock;
// семафоры для синхронизации последовательного вывода
HANDLE hSemaphore_F, hSemaphore_G, hSemaphore_H, hSemaphore_interval, hSemaphore_continue;

unsigned int lab3_thread_graph_id()
{
    return 17;
}

const char *lab3_unsynchronized_threads()
{
    return "bcd";
}

const char *lab3_sequential_threads()
{
    return "fgh";
}

DWORD WINAPI thread_a(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "a" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i <LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "b" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "b" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "e" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hSemaphore_F, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemaphore_G, 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hSemaphore_G, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemaphore_H, 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hSemaphore_H, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemaphore_F, 1, NULL);
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam)
    {
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "i" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "k" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemaphore_interval, 1, NULL);
    WaitForSingleObject(hSemaphore_continue, INFINITE);

    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "k" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < LETTERS_COUNT; ++i)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "m" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

int lab3_init()
{
    // создание семафоров
    hSemaphore_F = CreateSemaphore(
            NULL,           // аттрибуты безопасности по умолчанию
            1,  // начальное значение счетчика
            1,  // максимаьлное значение счетчика
            NULL);          // безымянный семафор
    hSemaphore_H = CreateSemaphore(NULL, 0, 1, NULL);
    hSemaphore_G = CreateSemaphore(NULL, 0, 1, NULL);
    hSemaphore_interval = CreateSemaphore(NULL, 0, 2, NULL);
    hSemaphore_continue = CreateSemaphore(NULL, 0, 2, NULL);

    // создание мьютекса
    hLock = CreateMutex(NULL, FALSE, NULL);
    if (hLock == NULL)
    {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }

    ///                               ШАГ 1
    // запуск потоков А, B, D
    hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (hThread[0] == NULL)
    {
        std::cerr << "Can't create thread A. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (hThread[1] == NULL)
    {
        std::cerr << "Can't create thread B. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (hThread[3] == NULL)
    {
        std::cerr << "Can't create thread D. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // ожидание окончания потока А
    WaitForSingleObject(hThread[0], INFINITE);
    // ожидание завершения одного цикла потоков B, D
    WaitForSingleObject(hSemaphore_interval, INFINITE);
    WaitForSingleObject(hSemaphore_interval, INFINITE);

    ///                               ШАГ 2
    // Продолжение работы потоков B, D
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    // запуск потока C
    hThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (hThread[2] == NULL)
    {
        std::cerr << "Can't create thread C. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // ожидание окончания потоков С, B
    WaitForSingleObject(hThread[2], INFINITE);
    WaitForSingleObject(hThread[1], INFINITE);
    // ожидание окончания одного цикла потока D
    WaitForSingleObject(hSemaphore_interval, INFINITE);

    ///                               ШАГ 3
    // Продолжение работы потока D
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    // запуск потоков E, F, H
    hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (hThread[4] == NULL)
    {
        std::cerr << "Can't create thread E. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (hThread[5] == NULL)
    {
        std::cerr << "Can't create thread F. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (hThread[7] == NULL)
    {
        std::cerr << "Can't create thread H. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // ожидание окончания птоков Е, D
    WaitForSingleObject(hThread[4], INFINITE);
    WaitForSingleObject(hThread[3], INFINITE);
    // ожидание завершения одного цикла потоками H, F
    WaitForSingleObject(hSemaphore_interval, INFINITE);
    WaitForSingleObject(hSemaphore_interval, INFINITE);

    ///                               ШАГ 4
    // Продолжение работы потоков H, F
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    // запуск потока G
    hThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[6] == NULL)
    {
        std::cerr << "Can't create thread G. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // ожидание окончания птоков F, G
    WaitForSingleObject(hThread[5], INFINITE);
    WaitForSingleObject(hThread[6], INFINITE);
    // ожидание завершения одного цикла потоком H
    WaitForSingleObject(hSemaphore_interval, INFINITE);

    ///                               ШАГ 5
    // Продолжение работы потока H
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    // запуск потоков I, K
    hThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (hThread[8] == NULL)
    {
        std::cerr << "Can't create thread I. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (hThread[9] == NULL)
    {
        std::cerr << "Can't create thread K. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // ожидание окончания птоков I, H
    WaitForSingleObject(hThread[7], INFINITE);
    WaitForSingleObject(hThread[8], INFINITE);
    // ожидание завершения одного цикла потоком K
    WaitForSingleObject(hSemaphore_interval, INFINITE);

    ///                               ШАГ 6
    // Продолжение работы потока K
    ReleaseSemaphore(hSemaphore_continue, 1, NULL);
    // запуск потока M
    hThread[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
    if (hThread[10] == NULL)
    {
        std::cerr << "Can't create thread M. Error: " << GetLastError() << std::endl;
        return 1;
    }
    // ожидание окончания птоков K, M
    WaitForSingleObject(hThread[9], INFINITE);
    WaitForSingleObject(hThread[10], INFINITE);

    // освобождение ресурсов
    for (int i = 0; i < THREADS_COUNT; ++i)
        CloseHandle(hThread[i]);
    CloseHandle(hLock);
    // close semaphores
    CloseHandle(hSemaphore_F);
    CloseHandle(hSemaphore_G);
    CloseHandle(hSemaphore_H);
    CloseHandle(hSemaphore_interval);
    CloseHandle(hSemaphore_continue);
    std::cout << std::endl;
    return 0;
}
