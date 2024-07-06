#pragma once
#pragma once
#include <memory>
// ����Ʈ �����ͷ� ����� �Ҹ� ������ ������ ���� �� �ְ�
// ��ü ���α׷� �Ⱓ ���� �����Ǿ�� �ϱ� ������ 
// ���� ���� ��갰�� �߰� ������带 �߻���ų �ʿ䰡 ����

template<typename T>
class ISingleton
{
protected:
    ISingleton() = default;
    virtual ~ISingleton() {}

public:
    static T* GetInstance()
    {
        if (m_pInstance == nullptr)
            m_pInstance = new T;
        return m_pInstance;
    }

private:
    static T* m_pInstance;
};

template<typename T>
T* ISingleton<T>::m_pInstance = nullptr;