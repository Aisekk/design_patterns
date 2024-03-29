#pragma once

#include <vector>

class Object
{
public:
    Object() {}
};

class ObjectPool
{
private:
    struct PoolRecord
    {
        Object* instance;
        bool    in_use;
    };

    std::vector<PoolRecord> m_pool;

public:
    Object* createNewObject()
    {
        for (size_t i = 0; i < m_pool.size(); ++i)
        {
            if (!m_pool[i].in_use)
            {
                m_pool[i].in_use = true; // ��������� ������ � ������ ������������
                return m_pool[i].instance;
            }
        }
        // ���� �� ����� ��������� ������, �� ��������� ���
        PoolRecord record;
        record.instance = new Object;
        record.in_use = true;

        m_pool.push_back(record);

        return record.instance;
    }

    void deleteObject(Object* object)
    {
        // � ���������� �� �������, � ���� ��������, ��� ������ ��������
        for (size_t i = 0; i < m_pool.size(); ++i)
        {
            if (m_pool[i].instance == object)
            {
                m_pool[i].in_use = false;
                break;
            }
        }
    }

    virtual ~ObjectPool()
    {
        // ������ ��� "��-����������" ������� �������
        for (size_t i = 0; i < m_pool.size(); ++i)
            delete m_pool[i].instance;
    }
};


void objectPool()
{
    ObjectPool pool;
    for (size_t i = 0; i < 1000; ++i)
    {
        Object* object = pool.createNewObject();
        // ...
        pool.deleteObject(object);
    }
}