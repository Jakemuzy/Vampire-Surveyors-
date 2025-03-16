#include <cmath>
#include <ctime>



bool gamble(float p) {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if(r<p){
            return true;
        }
        return false;
}


double get_upgrade_prob(int level) {
        double exponent = 0.05 * level;
        return std::min(1.0, std::max(0.001, 1.0 - 0.005 * pow(level, 1.1)));
    }

double get_BIN_upgrade_cost(int level) {
    double successProb = get_upgrade_prob(level);
    return 1.2 * (1.0 / successProb);
}



