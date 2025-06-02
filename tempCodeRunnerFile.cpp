
    for (int i = 0; i < numLines; ++i)
    {
        cout << dance[i % numDanceMoves] << '\r';
        this_thread::sleep_for(chrono::milliseconds(delayMilliseconds));
    }
}

// Hàm thực thi lệnh