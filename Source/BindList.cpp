#include "BindList.h"

BindList::BindList() {
    for (int i = 0; i < maxBinds; ++i) {
        m_binds[i] = -1;
    }
}

void BindList::bind(const int& value) {
    unbind(value);

    int writeLocation = 0;
    for (int i = 0; i < maxBinds; ++i) {
        writeLocation = i;
        if (m_binds[i] == -1)
            break;
    }
    m_binds[writeLocation] = value;
}

void BindList::unbind(const int& value) {
    for (int i = 0; i < maxBinds; ++i) {
        if (m_binds[i] == value) {
            m_binds[i] = -1;
        }
    }
}
