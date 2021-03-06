#include "XorIntervalTree.h"

XorIntervalTree::XorIntervalTree (int arrayLength)
	: _nodes(_GetSizeOfTree(arrayLength), 0)
{
}

int XorIntervalTree::_GetSizeOfTree (int minimumNumberOfLeaves) const
{
	return _NearestPowerOf2NotLowerThan(minimumNumberOfLeaves) * 2 - 1;
}

int XorIntervalTree::_NearestPowerOf2NotLowerThan (int x) const
{
	int res = x;

	res |= (res >> 1);
	res |= (res >> 2);
	res |= (res >> 4);
	res |= (res >> 8);
	res |= (res >> 16);
	++res;

	return (res >> 1) == x ? x
						   : res;
}

void XorIntervalTree::Insert (int leafNumber, int val)
{
	int ind = leafNumber + this->NumberOfLeaves();
	
	_nodes[ind] ^= val;

	while (ind > 0)
	{
		ind /= 2;
		_nodes[ind] = (_nodes[ind * 2] ^ _nodes[ind * 2 + 1]);
	}
}

int XorIntervalTree::Query (const Interval& interval) const
{
	int beg = interval.Begin + this->NumberOfLeaves();
	int end = interval.End + this->NumberOfLeaves();
	int res = _nodes[beg];

	if (beg != end)
		res ^= _nodes[end];

	while ((beg / 2) != (end / 2))
	{
		if (beg % 2 == 0)
			res ^= _nodes[beg + 1];
		if (end % 2 == 1)
			res ^= _nodes[end - 1];
		
		beg /= 2;
		end /= 2;
	}

	return res;
}

int XorIntervalTree::NumberOfLeaves () const
{
	return _nodes.size() / 2 + _nodes.size() % 2;
}

