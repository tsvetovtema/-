#pragma once
#include "TList.h"
struct TMonom
{
	int p_x;
	int p_y;
	int p_z;
	double coef;
public:
	bool operator <=(const TMonom &m);
	bool operator !=(const TMonom &m);
	bool operator ==(const TMonom &m);
	bool operator >(const TMonom &m);
	bool operator >=(const TMonom &m);
	bool operator <(const TMonom &m);
	friend istream& operator>>(istream& in, TMonom &m)
	{
		int pxyz;
		cout << "Enter coeff: ";
		in >> m.coef;
		cout <<  "Enter power: ";
		in >> pxyz;
		cout << endl;
		m.p_x = pxyz / 100;
		m.p_y = pxyz / 10 % 10;
		m.p_z = pxyz % 10;
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMonom &m)
	{
		out << m.coef << "(x^" << m.p_x << ")" << "(y^" << m.p_y << ")" << "(z^" << m.p_z << ")";
		return out;
	}
};

bool TMonom::operator==(const TMonom &m) {
	if (p_x == m.p_x && p_y == m.p_y&& p_z == m.p_z) {
		return true;
	}
	else
	{
		return false;
	}
}

bool TMonom::operator>(const TMonom &m) {
	int st_f, st_s;
	st_f = p_x * 100 + p_y * 10 + p_z;
	st_s = m.p_x * 100 + m.p_y * 10 + m.p_z;
	if (st_f > st_s)
	{
		return true;
	}
	else {
		return false;
	}
}

bool TMonom::operator>=(const TMonom &m) {
	int st_f, st_s;
	st_f = p_x * 100 + p_y * 10 + p_z;
	st_s = m.p_x * 100 + m.p_y * 10 + m.p_z;
	if (st_f >= st_s)
	{
		return true;
	}
	else {
		return false;
	}
}

bool TMonom::operator<(const TMonom &m) {
	int st_f, st_s;
	st_f = p_x * 100 + p_y * 10 + p_z;
	st_s = m.p_x * 100 + m.p_y * 10 + m.p_z;
	if (st_f < st_s)
	{
		return true;
	}
	else {
		return false;
	}
}

bool TMonom::operator<=(const TMonom &m) {
	int st_f, st_s;
	st_f = p_x * 100 + p_y * 10 + p_z;
	st_s = m.p_x * 100 + m.p_y * 10 + m.p_z;
	if (st_f <= st_s)
	{
		return true;
	}
	else {
		return false;
	}
}

bool TMonom::operator!=(const TMonom &m) {
	if (*this == m)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



class TPolynom :public THeadList<TMonom> {
public:
	TPolynom() :THeadList<TMonom>() {
		pHead->val.coef = 0;
		pHead->val.p_x = 0;
		pHead->val.p_y = 0;
		pHead->val.p_z = -1;
	}
	TPolynom(int monoms[][2], int n) :THeadList<TMonom>() {
		pHead->val.coef = 0;
		pHead->val.p_x = 0;
		pHead->val.p_y = 0;
		pHead->val.p_z = -1;
		TMonom M;
		for (int i = 0; i < n; i++)
		{
			M.coef = monoms[i][0];
			M.p_x = monoms[i][1] / 100;
			M.p_y = monoms[i][1] / 10 % 10;
			M.p_z = monoms[i][1] % 10;
			AddMonom(M);
		}
	}
	TPolynom(TPolynom & P) : THeadList<TMonom>() {
		pHead->val.coef = 0;
		pHead->val.p_x = 0;
		pHead->val.p_y = 0;
		pHead->val.p_z = -1;
		TMonom M;
		for (P.Reset(); !P.IsEnd(); P.GoNext())
		{
			M = P.pCurr->val;
			InsLast(M);
		}
	}
	void AddMonom(const TMonom &M) {
		int flag = 0;
		for (Reset(); !IsEnd(); GoNext()) {
			if (pCurr->val == M)
			{
				pCurr->val.coef += M.coef;
				if (pCurr->val.coef == 0)
				{
					DelCurr();
					flag = 1;
				}
				break;
			}
			else {
				if (pCurr->val < M) {
					InsCurr(M);
					break;
				}
			}
		}
		if (IsEnd() && flag == 0) InsCurr(M);
	}
	TPolynom operator* (double a) {
		TPolynom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext())
		{
			res.pCurr->val.coef *= a;
			if (res.pCurr->val.coef == 0)
			{
				res.DelCurr(); 
				break;
			}
		}
		return res;
	}
	void operator*=(double a) {

		for (Reset(); !IsEnd(); GoNext())
		{
			pCurr->val.coef *= a;
			if (pCurr->val.coef == 0)
			{
				DelCurr(); break;
			}
		}

	}
	void operator*=(TMonom M) {
		for (Reset(); !IsEnd(); GoNext())
		{
			pCurr->val.coef *= M.coef;
			pCurr->val.p_x += M.p_x;
			pCurr->val.p_y += M.p_y;
			pCurr->val.p_z += M.p_z;
		}
	}
	TPolynom operator *(TMonom M) {
		TPolynom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext()) {
			res.pCurr->val.p_x += M.p_x;
			res.pCurr->val.p_y += M.p_y;
			res.pCurr->val.p_z += M.p_z;
			res.pCurr->val.coef *= M.coef;
		}
		return res;
	}

	void operator +=(TPolynom& Q) {
		TMonom pm, qm, rm;
		Reset();
		Q.Reset();
		while (!Q.IsEnd())
		{
			pm = pCurr->val;
			qm = Q.pCurr->val;
			if (pm > qm)
			{
				GoNext();
			}
			else
			{
				if (pm < qm)
				{
					InsCurr(qm);
					Q.GoNext();
				}
				else {
					rm = pm;
					rm.coef += qm.coef;
					if (rm.coef == 0)
					{
						DelCurr();
						Q.GoNext();
					}
					else
					{
						pCurr->val = rm;
						if (&Q == this) {
							GoNext();
						}
						else
						{
							GoNext();
							Q.GoNext();
						}
					}
				}
			}

		}

	}

	friend istream& operator>>(istream &in, TPolynom &p) {
		TMonom m;
		in >> m;
		while (m.coef != 0) {
			p.AddMonom(m);
			in >> m;
		}
		return in;
	}
	friend ostream& operator<<(ostream &out, TPolynom &p)
	{
		for (p.Reset(); !p.IsEnd(); p.GoNext()) {
			if (p.pCurr->val.coef < 0 || p.pCurr == p.pFirst)
				out << p.pCurr->val;
			else
				out << " + " << p.pCurr->val;
		}
		if (p.pFirst == p.pStop)
		{
			out << "0";
		}
		return out;
	}
};