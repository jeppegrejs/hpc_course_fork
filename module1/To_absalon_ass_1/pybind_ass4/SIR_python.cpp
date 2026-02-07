#include <iostream>
#include <fstream>
#include <vector>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

// Function to take a step in the SIR model
// state: vector of S, I, R
// beta: infection rate
// gamma: recovery rate
// dt: time step
std::vector<float> take_step(std::vector<float> state, float beta, float gamma, float dt, float N){
    

    float S_new = -(beta * state[1] * state[0])*dt / N + state[0];
    float I_new = (
        beta * state[1] * state[0]/ N - gamma * state[1])* dt 
         + state[1];
    float R_new = gamma * state[1] * dt + state[2];
    std::vector<float> new_state{S_new, I_new, R_new};
    return new_state;
}

// Function simulating num_steps of the SIR model, saving the state every return_every steps and returning the results
// S0: initial number of susceptible individuals
// I0: initial number of infected individuals
// R0: initial number of recovered individuals
// beta: infection rate
// gamma: recovery rate
// dt: time step
// num_steps: number of steps to simulate
// return_every: save the state every return_every steps
pybind11::array integrate_system(float S0, float I0, float R0, float beta, float gamma, float dt, int num_steps, int return_every){
    std::vector<float> state{S0,I0,R0};
    std::vector<std::vector<float>> results;    

    for (int step = 0; step <= num_steps; ++step) { //using step as i had problems saving. First i increment time, but got 
        // floating precisions erros when i where at smalled t


        float t = step * dt; // now t is not incremented, but overwritten each iteration so the check should work

        if (step % return_every == 0) {//save every is created using dt so it will hit sometimes
             results.push_back({t, state[0], state[1], state[2]});

        }
        int N = state[0] + state[1] + state[2];
        state = take_step(state, beta, gamma, dt, N);
    }

    

    return pybind11::cast(results);
}

PYBIND11_MODULE(SIR_python, m) {
    m.doc() = "This is a Python binding for the SIR model";

    m.def("integrate_system", &integrate_system);
}
