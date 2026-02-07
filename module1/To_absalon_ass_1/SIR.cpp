#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>


// Function to take a step in the SIR model
// state: vector of S, I, R
// beta: infection rate
// gamma: recovery rate
// dt: time step
std::vector<float> take_step(std::vector<float> state, float beta, float gamma, float dt){

    float S_new = - (beta * state[0] * state[1]) * dt + state[0];
    float I_new = (beta * state[0] * state[1] - gamma * state[1]) * dt + state[1];
    float R_new = (gamma * state[1]) * dt + state[2];

    std::vector<float> new_state{S_new, I_new, R_new};
    
    //todo: implement the SIR model
    return new_state;
}

float vector_add(std::vector<float> vec) {
    float s = 0;
    for (float x : vec) {
        s += x;
    }
    return s;
}

//======================================================================================================
//======================== Main function ===============================================================
//======================================================================================================
int main(int argc, char* argv[]){    
    // TODO: Define the parameters of the SIR model
    float S = atof(argv[1]);
    float I = atof(argv[2]);
    float R = atof(argv[3]);

    float beta = atof(argv[4]);
    float gamma = atof(argv[5]);
    
    float dt = atof(argv[6]);
    float tmax = atof(argv[7]);
    
    std::vector<float> state{S, I, R};

    float N = vector_add(state);
    float t = 0;

    std::ofstream SIR_file(argv[8]);
    SIR_file << t << " " << state[0] << " " << state[1] << " " << state[2] <<  " " << N << "\n";

    while(t <= tmax) {
        // TODO: Implement the SIR model
        state = take_step(state, beta, gamma, dt);
        N = vector_add(state);

        // TODO: Save the Results to a file
        SIR_file << t << " " << state[0] << " " << state[1] << " " << state[2] <<  " " << N << "\n";
        t += dt;
    }

    SIR_file.close();
}
