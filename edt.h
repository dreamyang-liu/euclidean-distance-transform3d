#include <string>
#include <vector>
#include <cmath>
#include<iomanip>
#include <iostream>
using namespace std;

class Vec3{
public:
    int x;
    int y;
    int z;

    Vec3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    Vec3(): x(9990), y(9990), z(9990){}
    Vec3 operator+ (const Vec3& v) const {return Vec3(x + v.x, y + v.y, z + v.z);}
    Vec3 operator- (const Vec3& v) const {return Vec3(x - v.x, y - v.y, z - v.z);}
    Vec3 operator* (const Vec3& v) const {return Vec3(x * v.x, y * v.y, z * v.z);}
    Vec3& operator= (Vec3 v) {x = v.x; y = v.y; z = v.z; return *this;}

    friend istream& operator>>(istream &in, Vec3 &v) {
        in >> v.x >> v.y >> v.z;
        return in;
    }
    friend ostream& operator<<(ostream &out, Vec3 &v) {
        out << setw(4) << v.x << ' '<< setw(4) << v.y << ' '<< setw(4) << v.z;
        return out;
    }

    double norm(double* spacing=nullptr) {
        if(spacing==nullptr) {
            spacing = new double[3];
            spacing[0] = 1.0;
            spacing[1] = 1.0;
            spacing[2] = 1.0;
        }
         return sqrt(x * x * spacing[0] * spacing[0] + y * y * spacing[1] * spacing[1] + z * z * spacing[2] * spacing[2]);
    }

    static Vec3 max_via_norm(Vec3 v1, Vec3 v2) {
        return v1.norm() > v2.norm() ? v1 : v2;
    }

    void exchange_xz() {
        int tmp = x;
        x = z;
        z = tmp;
    }
};

