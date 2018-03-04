#pragma once
struct Colour {
	int r;
	int g;
	int b;
};

struct ColourComp {
	bool operator()( Colour const & lhs, Colour const & rhs )
	{
		return (lhs.r < rhs.r)
			|| ((lhs.r == rhs.r) && (lhs.g < rhs.g))
			|| ((lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b < rhs.b));
	}
};
