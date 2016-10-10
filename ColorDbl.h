#pragma once
#include <vector>
class ColorDbl
{
	public:
		float r_, g_, b_;

		ColorDbl();
		ColorDbl(int r, int g, int b);
		~ColorDbl();
	private: 
		
		struct floatPrecisionColor
		{
			float R, G, B;
		};
		std::vector<floatPrecisionColor> floatColor;
	
};

