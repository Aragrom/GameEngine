#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();


	void start();
	void togglePause();
	void stop();
	void update();
	int getCurrentTime()
	{
		return m_CurrentTime;
	};

	float getCurrentFPS()
	{
		return (float)m_CurrentFrameCount / m_DeltaTime;
	}
    
    float getDeltaTime()
    {
        return m_DeltaTime;
    }
    
    static Timer& getTimer()
    {
        static Timer time;
        return time;
    }
    
private:
	int m_CurrentTime;
	int m_LastTime;
	int m_CurrentFrameCount;
	float m_DeltaTime;
	bool m_Paused;
	bool m_Started;
};



#endif