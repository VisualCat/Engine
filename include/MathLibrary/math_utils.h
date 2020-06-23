#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__ 1

class MathUtils {
	public:
		static float MathUtils::Clamp(float value, float minVal, float maxVal);

	private:
		MathUtils();
		MathUtils(const MathUtils& copy);
		~MathUtils();
};
inline MathUtils::MathUtils() {}
inline MathUtils::MathUtils(const MathUtils& copy) {}
inline MathUtils::~MathUtils(){}

inline float MathUtils::Clamp(float value, float minVal, float maxVal) {
	float result;
	if (minVal > maxVal) {
		result = minVal;
		minVal = maxVal;
		maxVal = result;
	}
	result = value;
	if (value < minVal)
	{
		result = minVal;
	}
	else if (value > maxVal) 
	{
		result = maxVal;
	}
	return result;
}
#endif