#include <queue>
#include <boost/thread.hpp>  

template <typename T>
class SynchronisedQueue
{
public:

    SynchronisedQueue()
    {
        RequestToEnd = false;  
        EnqueueData = true;
    }
    void Enqueue(const T& data)
    {
        boost::unique_lock<boost::mutex> lock(m_mutex);

        if(EnqueueData)
        {
            m_queue.push(data);
            m_cond.notify_one();
        }

    } 


    bool TryDequeue(T& result)
    {
        boost::unique_lock<boost::mutex> lock(m_mutex);

        while (m_queue.empty() && (! RequestToEnd)) 
        { 
            m_cond.wait(lock);
        }

        if( RequestToEnd )
        {
             DoEndActions();
             return false;
        }

        result= m_queue.front(); m_queue.pop();

        return true;
    }

    void StopQueue()
    {
        //RequestToEnd =  true;
        //Enqueue(NULL); 
        boost::unique_lock<boost::mutex> lock(m_mutex);
        RequestToEnd =  true;
        m_cond.notify_one();          
    }

    int Size()
    {
        boost::unique_lock<boost::mutex> lock(m_mutex);
        return m_queue.size();

    }

private:

    void DoEndActions()
    {
        EnqueueData = false;

        while (!m_queue.empty())  
        {
            m_queue.pop();
        }
    }



    std::queue<T> m_queue;              // Use STL queue to store data
    boost::mutex m_mutex;               // The mutex to synchronise on
    boost::condition_variable m_cond;            // The condition to wait for

    bool RequestToEnd;
    bool EnqueueData;
};