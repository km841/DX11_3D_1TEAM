#pragma once
class TimerObject
{
public:
	TimerObject(float _endTime  = 1.0f);
	~TimerObject() = default;

public:

	void Update();
	void Start();
	void Stop();
	bool IsFinished();
	float GetProgress();

	void SetEndTime(float _endTime) { mEndTime = _endTime; }
	float GetCurTime() { return mCurTime; }
	bool GetIsRun() { return mbIsRunning; }
private:
	float mEndTime;
	float mCurTime;
	bool  mbIsFinished;
	bool  mbIsRunning;

};

