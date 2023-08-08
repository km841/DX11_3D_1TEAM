#pragma once
class TimerObject
{
public:
	TimerObject();
	~TimerObject() = default;

public:

	void Update();
	void Start();
	void Stop();
	bool IsFinished();
	float GetProgress();

private:
	float mEndTime;
	float mCurTime;
	bool  mbIsFinished;
	bool  mbIsRunning;

};

