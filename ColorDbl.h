#pragma once
#include <vector>
class ColorDbl
{
	public:
		ColorDbl();
		~ColorDbl();
	private: 

		struct floatPrecisionColor
		{
			float R, G, B;
		};
		std::vector<floatPrecisionColor> floatColor;
	
};

