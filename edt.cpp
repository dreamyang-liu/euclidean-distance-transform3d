#include "edt.h"
#include <iostream>
#include <vector>


Vec3 dis_vec(int i, int j, int k, std::vector<Vec3> offsets, const std::vector<std::vector<std::vector<Vec3>>>& father, double* spacing=nullptr) {
    Vec3 res(8880, 8880, 8880);
    for(auto offset : offsets) {
        int di = i + offset.x;
        int dj = j + offset.y;
        int dk = k + offset.z;
        if((father[di][dj][dk] + offset).norm(spacing) < res.norm(spacing)) {
            res = father[di][dj][dk] + offset;
        }
    }
    return res;
}

void edt3d(std::vector<std::vector<std::vector<int>>> src, std::vector<std::vector<std::vector<Vec3>>>& father) {
    // dim = [dim_i, dim_j, dim_k]
    std::vector<Vec3> filter1 = {
        Vec3(1, 1, 1),
        Vec3(1, -1, 1),
        Vec3(1, 0, 1),
        Vec3(-1, 1, 1),
        Vec3(-1, -1, 1),
        Vec3(-1, 0, 1),
        Vec3(0, 1, 1),
        Vec3(0, -1, 1),
        Vec3(0, 0, 1),

        Vec3(-1, -1, 0),
        Vec3(-1, 0, 0),
        Vec3(-1, 1, 0),
        Vec3(0, -1, 0),
        Vec3(0, 0, 0)
    };


    std::vector<Vec3> filter2 = {
        Vec3(0, 1, 0),
        Vec3(0, 0, 0)
    };


    std::vector<Vec3> filter3 = {
        Vec3(1, -1, 0),
        Vec3(1, 0, 0),
        Vec3(1, 1, 0),
        Vec3(0, 1, 0),
        Vec3(0, 0, 0)
    };

    std::vector<Vec3> filter4 = {
        Vec3(0, -1, 0),
        Vec3(0, 0, 0)
    };

    // forward
    for(int i = 3; i >= 1; i--) { // 4 3 2 1 0
        for(int k = 4; k >= 1; k--) { // 5 4 3 2 1 0
            for(int j = 1; j <= 4; j++) { // 0 1 2 3 4 5
                    father[i][j][k] = dis_vec(i, j, k, filter1, father);
            }
            for(int j=4;j>=1;j--) { // 5 4 3 2 1 0
                    father[i][j][k] = dis_vec(i, j, k, filter2, father);
            }
        }
        for(int k=1;k<=4; k++) { // 0 1 2 3 4 5
            for(int j=4;j>=1; j--) { // 5 4 3 2 1 0
                    father[i][j][k] = dis_vec(i, j, k, filter3, father);
            }
            for(int j=1; j<=4; j++) { // 0 1 2 3 4 5
                    father[i][j][k] = dis_vec(i, j, k, filter4, father);
            }
        }
    }






    std::vector<Vec3> filter5 = {
        Vec3(1, 1, -1),
        Vec3(1, -1, -1),
        Vec3(1, 0, -1),
        Vec3(-1, 1, -1),
        Vec3(-1, -1, -1),
        Vec3(-1, 0, -1),
        Vec3(0, 1, -1),
        Vec3(0, -1, -1),
        Vec3(0, 0, -1),

        Vec3(1, -1, 0),
        Vec3(1, 0, 0),
        Vec3(1, 1, 0),
        Vec3(0, 1, 0),
        Vec3(0, 0, 0)
    };




    std::vector<Vec3> filter6 = {
        Vec3(0, -1, 0),
        Vec3(0, 0, 0)
    };

    std::vector<Vec3> filter7 = {
        Vec3(-1, -1, 0),
        Vec3(-1, 0, 0),
        Vec3(-1, 1, 0),
        Vec3(0, -1, 0),
        Vec3(0, 0, 0)
    };

    std::vector<Vec3> filter8 = {
        Vec3(0, 1, 0),
        Vec3(0, 0, 0)
    };



    // backward
    for(int i = 1; i <= 3; i++) { // 0 1 2 3 4 
        for(int k = 1; k <= 4; k++) { // 5 4 3 2 1 0
            for(int j = 4; j >= 1; j--) { // 0 1 2 3 4 5
//                if(src[i][j][k] == 0)
                    father[i][j][k] = dis_vec(i, j, k, filter5, father);
            }
            for(int j = 1;j <= 4;j++) { // 5 4 3 2 1 0
//                if(src[i][j][k] == 0)
                    father[i][j][k] = dis_vec(i, j, k, filter6, father);
            }
        }
        for(int k=4;k>=1; k--) { // 0 1 2 3 4 5
            for(int j=1;j<=4; j++) { // 5 4 3 2 1 0
//                if(src[i][j][k] == 0)
                    father[i][j][k] = dis_vec(i, j, k, filter7, father);
            }
            for(int j=4; j>=1; j--) { // 0 1 2 3 4 5
//                if(src[i][j][k] == 0)
                    father[i][j][k] = dis_vec(i, j, k, filter8, father);
            }
        }
    }
}


int main () {
    std::vector<std::vector<int>> slice1 = {
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
    };
    std::vector<std::vector<int>> slice2 = {
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
    };
    std::vector<std::vector<int>> slice3 = {
        {1,1,1,1,0,1},
        {1,1,1,1,1,1},
        {1,1,0,0,1,1},
        {1,1,0,0,1,1},
        {1,1,1,1,0,1},
        {1,1,1,1,1,1},
    };
    std::vector<std::vector<int>> slice4 = {
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
    };
    std::vector<std::vector<int>> slice5 = {
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
    };
    std::vector<std::vector<std::vector<int>>> volume = {
        slice1, slice2, slice3, slice4, slice5
    };


    std::vector<std::vector<Vec3>> father_slice1 = {
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
    };
    std::vector<std::vector<Vec3>> father_slice2 = {
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
    };
    std::vector<std::vector<Vec3>> father_slice3 = {
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(0, 0, 0), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
    };
    std::vector<std::vector<Vec3>> father_slice4 = {
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
    };
    std::vector<std::vector<Vec3>> father_slice5 = {
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
        {Vec3(), Vec3(), Vec3(), Vec3(), Vec3(), Vec3()},
    };

    std::vector<std::vector<std::vector<Vec3>>> father = {
        father_slice1, father_slice2,father_slice3,father_slice4, father_slice5
    };

    edt3d(volume, father);

    for(int i=0;i<father.size();i++) {
        for(int j=0;j<father[0].size();j++) {
            for(int k=0;k<father[0][0].size();k++) {
                father[i][j][k].exchange_xz();
                std::cout <<father[i][j][k] << '|';
            }
            std::cout<<std::endl;
        }
        std::cout << std::endl;
    }
    return 0;

}
