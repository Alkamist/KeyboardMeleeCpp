#pragma once

class BindList
{
public:
    BindList();

    void bind(const int& value);
    void unbind(const int& value);

    const int* getBinds() const { return m_binds; }

    static const int maxBinds = 4;

private:
    int m_binds[maxBinds];
};