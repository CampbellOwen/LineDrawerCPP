#pragma once

struct Colour {
	int r;
	int g;
	int b;

	bool operator==(const Colour &other) const
	{
		return (r == other.r
			&& g == other.g
			&& b == other.b);
	}
};

struct ColourComp {
	bool operator()( Colour const & lhs, Colour const & rhs )
	{
		return (lhs.r < rhs.r)
			|| ((lhs.r == rhs.r) && (lhs.g < rhs.g))
			|| ((lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b < rhs.b));
	}
};

struct ColourHasher
{
	std::size_t operator()(const Colour& k) const
	{
		using std::hash;

		return ((hash<int>()(k.r)
			^ (hash<int>()(k.g) << 1)) >> 1)
			^ (hash<int>()(k.b) << 1);
	}
};
