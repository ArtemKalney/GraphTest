#pragma once

#include "stdafx.h"
#include "Cclass.h"

int Bin(int k,int l);
bool gconnected(vector<vector<edge>> &H);
void renumerate(vector<vector<edge>> &H, int s, int t);
edge procedure(vector<vector<edge>> &H, edge F, bool connected); 
vector<int> gnodepower(vector<vector<edge>> &H);
void delnode ( vector<vector<edge>> &H,int q);
void contractedge ( vector<vector<edge>> &H,int q, int w);
bool exis(vector<int> P, int x);
vector<int> fchain(vector<vector<edge>> &H, vector<int> &V);