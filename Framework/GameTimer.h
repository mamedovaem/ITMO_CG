#pragma once
#include "D3DUtil.h"

class GameTimer
{
public:
	GameTimer();

	float DeltaTime() const; // in seconds
	float TotalTime() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private: 
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};