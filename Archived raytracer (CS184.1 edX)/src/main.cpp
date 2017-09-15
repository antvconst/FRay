#include <iostream>
#include "fmath.h"
#include "fray.h"
#include "frenderer.h"
#include <ctime>
#include <thread>

using namespace std;

int main()
{
    int time_start = time(NULL);
    std::ios::sync_with_stdio(false);

    auto scene = new FRay::Scene("scenes/scene6.test");

    FRenderer renderer;
    renderer.setScene(scene);
    renderer.render();

    int time_finish = time(NULL);

    std::cout << "DONE IN " << time_finish - time_start << " SECS" << std::endl;
    //system("pause");

    return 0;
}
