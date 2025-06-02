// #include <stdio.h>
// #include "unistd.h"
// #include <string.h>
// #include <windows.h>
// #include <bits/stdc++.h>
// using namespace std;
// void clearScreen()
// {
//     printf("\033[H\033[J");
// }

// void dancing()
// {
//     const char *dance[] = {
//         " ~~(^-^~~)",
//         " ~~(^-^)~~",
//         " (~~^-^)~~" };

//     const int numDanceMoves = sizeof(dance) / sizeof(dance[0]);
//     const int numLines = 30;
//     const int delayMilliseconds = 500;

//     for (int i = 0; i < numLines; ++i)
//     {
//         cout << dance[i % numDanceMoves] << '\r';
//         this_thread::sleep_for(chrono::milliseconds(delayMilliseconds));
//     }
// }

// void usleep1(unsigned int usec)
// {
// 	HANDLE timer;
// 	LARGE_INTEGER ft;

// 	ft.QuadPart = -(10 * (__int64)usec);

// 	timer = CreateWaitableTimer(NULL, TRUE, NULL);
// 	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
// 	WaitForSingleObject(timer, INFINITE);
// 	CloseHandle(timer);
// }

// int main()
// {
//    dancing();
//    usleep1(100000);
//    return 0;
// }
