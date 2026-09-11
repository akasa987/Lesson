#pragma once

namespace HOhara
{
    template<typename T>
    void SafeDelete(T*& p)
    {
        delete p;
        p = nullptr;
    }

    template<typename T>
    void SafeDeleteArray(T*& p)
    {
        delete[] p;
        p = nullptr;
    }
}