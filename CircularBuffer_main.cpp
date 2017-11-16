#include <iostream>
#include<iomanip>
#include<vector>

using namespace std;

template<class T> class CircularBuffer{
private:
    unsigned int m_nSize;
    vector<T> m_vec_genElements;
    unsigned int m_nReadIndex;
    unsigned int m_nWriteIndex;
    int m_nPassCnt;

public:
    CircularBuffer(int nSize)
    {
        m_nSize = nSize;
        m_vec_genElements.assign(m_nSize, 0);
        m_nReadIndex = 0;
        m_nWriteIndex = 0;
        m_nPassCnt = 0;
    }

    int Read(T& genTemp)
    {
        if(m_nReadIndex == m_nWriteIndex && m_nPassCnt == 0)
        {
            return 0;
        }
        else
        {
            genTemp = m_vec_genElements[m_nReadIndex];
            m_nReadIndex++;
            if(m_nReadIndex == m_nSize)
            {
                m_nReadIndex = 0;
            }
            if(m_nReadIndex == m_nWriteIndex)
            {
                m_nPassCnt = 0;
            }
            return 1;
        }
    }

    int Write(T& genTemp)
    {
        if((m_nWriteIndex == m_nReadIndex) && m_nPassCnt == 1)
        {
            return 0;
        }
        else
        {
            m_vec_genElements[m_nWriteIndex] = genTemp;
            m_nWriteIndex++;
            if(m_nWriteIndex == m_nSize)
            {
                m_nWriteIndex = 0;
            }
            if(m_nReadIndex == m_nWriteIndex)
            {
                m_nPassCnt = 1;
            }
            return 1;
        }
    }
};

int main()
{
    int nLength = 10;
    CircularBuffer<char> obj_cCircBuf(nLength);
    CircularBuffer<int> obj_nCircBuf(nLength);

    for(int nCnt = 0; nCnt < nLength; nCnt++)
    {
        char cTemp = 'a' + nCnt;
        int nTemp = 'a' + nCnt;
        if(!obj_cCircBuf.Write(cTemp))
        {
            cout<<"Buffer full"<<endl;
        }
        if(!obj_nCircBuf.Write(nTemp))
        {
            cout<<"Buffer full"<<endl;
        }
    }

    for(int nCnt = 0; nCnt < nLength; nCnt++)
    {
        int nTemp;
        char cTemp;

        if(obj_nCircBuf.Read(nTemp))
        {
            cout<<nTemp<<"\t";
        }
        else
        {
            cout<<"Buffer empty\t";
        }

        if(obj_cCircBuf.Read(cTemp))
        {
            cout<<cTemp<<endl;
        }
        else
        {
            cout<<"Buffer empty"<<endl;
        }
    }
}
