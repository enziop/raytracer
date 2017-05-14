#include "ppmio.h"

using namespace std;

void PpmIO::test(unsigned w, unsigned h) {
        ofstream f;
        f.open("out.ppm");
        f << "P3\n" << w << " " << h << "\n255\n";
        for (unsigned y = 0; y < w; ++y) {
            for (unsigned x = 0; x < w; ++x) {
                if ((x + y) % 2 == 0) {
                    f << "255 255 255 ";
                }
                else {
                    f << "0 0 0 ";
                }
            }
            f << "\n";
        }
        f.close();
        return;
}
