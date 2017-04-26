#pragma once

#include "stdafx.h"

struct edge
{
	vector<double> C;
	int power;
	int node1;
	int node2;
	int simple;
	bool ex;
	void printedge();
};

edge operator *(edge x, edge y);
edge operator +(edge x, edge y);
edge operator -(edge x, edge y);
edge operator ~(edge x);
edge operator *(int x, edge y);
edge operator *(edge x, int y);