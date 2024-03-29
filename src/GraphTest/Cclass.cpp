#include "Stdafx.h"
#include "Cclass.h"
#include "Globals.h"

void edge::PrintEdge() {
    if (ex == 1) {
        for (int i = 0; i < C.size(); i++)
            cout << setprecision(15) << C[i] << " ";
        cout << endl;
    }
    else
        cout << "empty edge" << endl;
}

/*
 * The following rules for calculations:
 * 0 <=> edge.C.empty() = true
 * 1 <=> edge.C.size() = 1
 */

edge operator *(edge x, edge y)
{
    edge F;
    if (!x.C.empty() && !y.C.empty()) {
        if (x.C.size() == 1) return y;
        if (y.C.size() == 1) return x;
        F.C.resize(x.C.size());
        F.power = 0;
        F.simple = 0;
        F.ex = true;

        if (x.simple > 0 && x.power != 1)
            cout << "Eror in Operator *" << endl;
        if (y.simple > 0 && y.power != 1)
            cout << "Eror in Operator *" << endl;

        // Parallel reduction for both edges x, y
        if (x.simple > 0) {
            x.power += x.simple;
            x = Bin[x.power];
            x.C[x.power] = 0;
        }

        if (y.simple > 0) {
            y.power += y.simple;
            y = Bin[y.power];
            y.C[y.power] = 0;
        }

        try {
            F.power = x.power + y.power;

            if (AppSettings.IsNumberComputation == 1) {
                F.value = x.value * y.value;
            }
            else {
                for (int i = 0; i<x.C.size(); i++)
                    for (int j = 0; j<y.C.size(); j++) {
                        if (x.C[i] != 0 && y.C[j] != 0) {
                            if (i + j >= F.C.size())
                                throw "Eror - vector is out of size";
                            F.C[i + j] += x.C[i] * y.C[j];
                        }
                    }
            }
        }
        catch (char *str) {
            cout << str << endl;
            for (int i = 0; i<x.C.size(); i++)
                cout << x.C[i] << " ";
            cout << endl << "*" << endl;;
            for (int i = 0; i<y.C.size(); i++)
                cout << y.C[i] << " ";
            cout << endl;
        }
    }
    return F;
}

edge operator +(edge x, edge y)
{
    edge F;
    if (!x.C.empty() && !y.C.empty()) {
        if (x.C.size() == 1 && y.C.size() != 1) {
            x.C.resize(y.C.size());
            x.power = 0;
            x.simple = 0;
        }

        if (x.C.size() != 1 && y.C.size() == 1) {
            y.C.resize(x.C.size());
            y.power = 0;
            y.simple = 0;
        }

        if (x.C.size() == 1 && y.C.size() == 1)
            cout << "Eror in Operator +" << endl;

        F.C.resize(x.C.size());
        F.simple = 0;
        F.ex = true;

        if (x.simple > 0 && x.power != 1)
            cout << "Eror in Operator +" << endl;
        if (y.simple > 0 && y.power != 1)
            cout << "Eror in Operator +" << endl;

        // Parallel reduction for both edges x, y
        if (x.simple > 0) {
            x.power += x.simple;
            x = Bin[x.power];
            x.C[x.power] = 0;
        }

        if (y.simple > 0) {
            y.power += y.simple;
            y = Bin[y.power];
            y.C[y.power] = 0;
        }

        // Multiply by a unit of the required degree, so that the degrees x and y coincide
        if (x.power != y.power) {
            edge I = Bin[abs(x.power - y.power)];
            if (x.power < y.power) x = x*I;
            if (y.power < x.power) y = y*I;
        }

        F.power = x.power;
        if (AppSettings.IsNumberComputation == 1) {
            F.value = x.value + y.value;
        }
        else {
            for (int i = 0; i<F.C.size(); i++)
                F.C[i] = x.C[i] + y.C[i];
        }
    }

    if (!x.C.empty() && y.C.empty()) F = x;
    if (x.C.empty() && !y.C.empty()) F = y;

    return F;
}

edge operator -(edge x, edge y)
{
    edge F;
    if (!x.C.empty() && !y.C.empty()) {
        if (x.C.size() == 1 && y.C.size() != 1) {
            x.C.resize(y.C.size());
            x.power = 0;
            x.simple = 0;
        }

        if (x.C.size() != 1 && y.C.size() == 1) {
            y.C.resize(x.C.size());
            y.power = 0;
            y.simple = 0;
        }

        if (x.C.size() == 1 && y.C.size() == 1)
            cout << "Eror in Operator -" << endl;

        F.C.resize(x.C.size());
        F.simple = 0;
        F.ex = true;

        if (x.simple > 0 && x.power != 1)
            cout << "Eror in Operator -" << endl;
        if (y.simple > 0 && y.power != 1)
            cout << "Eror in Operator -" << endl;

        // Parallel reduction for both edges x, y
        if (x.simple > 0) {
            x.power += x.simple;
            x = Bin[x.power];
            x.C[x.power] = 0;
        }

        if (y.simple > 0) {
            y.power += y.simple;
            y = Bin[y.power];
            y.C[y.power] = 0;
        }

        // Multiply by a unit of the required degree, so that the degrees x and y coincide
        if (x.power != y.power) {
            edge I = Bin[abs(x.power - y.power)];
            if (x.power < y.power) x = x*I;
            if (y.power < x.power) y = y*I;
        }

        F.power = x.power;
        if (AppSettings.IsNumberComputation == 1) {
            F.value = x.value - y.value;
        }
        else {
            for (int i = 0; i<F.C.size(); i++)
                F.C[i] = x.C[i] - y.C[i];
        }
    }

    if (!x.C.empty() && y.C.empty()) F = x;
    if (x.C.empty() && !y.C.empty()) {
        F = y;
        if (AppSettings.IsNumberComputation == 1) {
            F.value = -F.value;
        }
        else {
            for (int i = 0; i<F.C.size(); i++) F.C[i] = -F.C[i];
        }
    }

    return F;
}

edge operator ~(edge x)
{
    edge F;
    if (!x.C.empty()) {
        if (x.C.size() == 1) return F;
        F.C.resize(x.C.size());
        F.simple = 0;
        F.ex = true;

        if (x.simple > 0 && x.power != 1)
            cout << "Eror in Operator ~" << endl;

        // Parallel reduction for the edge x
        if (x.simple > 0) {
            x.power += x.simple;
            x = Bin[x.power];
            x.C[x.power] = 0;
        }

        // Subtract from unity the same degree as x
        F.power = x.power;
        edge I = Bin[F.power];
        if (AppSettings.IsNumberComputation == 1) {
            F.value = 1 - x.value;
        }
        else {
            for (int i = 0; i<F.C.size(); i++)
                F.C[i] = I.C[i] - x.C[i];
        }
    }
    else F.C.push_back(1);

    return F;
}

edge operator *(int x, edge y)
{
    edge F;
    if (!y.C.empty()) {
        F = y;
        if (AppSettings.IsNumberComputation == 1) {
            F.value = x*F.value;
        }
        else {
            for (int i = 0; i<F.C.size(); i++)
                F.C[i] = x*F.C[i];
        }
    }

    return F;
}

edge operator *(edge x, int y)
{
    edge F;
    if (!x.C.empty()) {
        F = x;
        if (AppSettings.IsNumberComputation == 1) {
            F.value = y*F.value;
        }
        else {
            for (int i = 0; i<F.C.size(); i++)
                F.C[i] = y*F.C[i];
        }
    }

    return F;
}