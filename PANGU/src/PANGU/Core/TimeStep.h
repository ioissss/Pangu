#pragma once

namespace PANGU {
	class TimeStep {
	public:
		TimeStep(float time) :time(time) {}
		
		operator float()const { return time; }
		operator float() { return time; }
		float GetSeconds()const { return time; }
		float GetMilliseconds()const { return time * 1000.0f; }
	private:
		float time = 0.0f;
	};
}