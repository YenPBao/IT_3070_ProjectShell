#include <iostream>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
void clearScreen()
{
    // ANSI escape code để xóa màn hình, tương tự system("cls")
    std::cout << "\033[H\033[J";
}

void printHeart(bool filled)
{
char heartChar = 3;               // mã ASCII 3 (♥)
std::string ch = filled ? std::string(1, heartChar) : " ";

  // Dòng 1   (hai “đỉnh” trái tim)
    cout << "     " 
         << ch << ch << ch << "      "    // đỉnh trái
         << ch << ch << ch << "      "    // đỉnh phải
         << "\n";

    // Dòng 2
    cout << "    " 
         << ch << ch << ch << ch << ch << ch    // phần bầu trái
         << "  " 
         << ch << ch << ch << ch << ch << ch    // phần bầu phải
         << "    \n";

    // Dòng 3
    cout << "  " 
         << ch << ch << ch << ch << ch << ch << ch << ch << ch << ch    // phần giữa trái
         << ch << ch << ch << ch << ch << ch << ch << ch     // phần giữa phải
         << "  \n";

    // Dòng 4
    cout << "  "
         << ch << ch << ch << ch << ch << ch << ch << ch << ch << ch    // phần giữa trái (ý: in y hệt Dòng 3 để tạo form “đầy”)
         << ch << ch << ch << ch << ch << ch << ch << ch    // phần giữa phải
         << "  \n";

    // Dòng 5   (hình đáy trái tim phía trên)
    cout << "    "
         << ch << ch << ch << ch << ch << ch << ch << ch << ch << ch << ch << ch <<ch<<ch    // phần dưới hẹp lại
         << "    \n";

    // Dòng 6   (hình đáy trái tim phía dưới)
    cout << "      "
         << ch << ch << ch << ch << ch << ch << ch << ch<<ch<<ch    // nhỏ hơn chút
         << "      \n";

    // Dòng 7
    cout << "        "
         << ch << ch << ch << ch <<ch<<ch    // càng nhỏ hơn nữa
         << "        \n";

    // Dòng 8
    cout << "         "
         << ch << ch <<ch <<ch             // chỉ còn 2 ký tự
         << "          \n";
		 cout << "          "
          << ch<<ch               // chỉ còn 2 ký tự
         << "          \n";
}

// Tạo hàm usleep1 giống duck.cpp (dùng WaitableTimer)
void usleep1(unsigned int usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * (__int64)usec); // Đơn vị là 100ns => 10 * usec

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

int main()
{
    while (true)
    {
        clearScreen();
        printHeart(true);
        usleep1(300000); // 300ms
        clearScreen();
        printHeart(false);
        usleep1(200000); // 200ms
    }

    return 0;
}
