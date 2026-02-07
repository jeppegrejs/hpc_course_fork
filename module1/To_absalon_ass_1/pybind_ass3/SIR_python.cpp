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
std::vector<double> take_step(std::vector<double> state, double beta, double gamma, double dt){
    

    double S_new = -(beta * state[1] * state[0])*dt + state[0];
    double I_new = (
        beta * state[1] * state[0] - gamma * state[1])* dt 
         + state[1];
    double R_new = gamma * state[1] * dt + state[2];
    std::vector<double> new_state{S_new, I_new, R_new};
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
pybind11::array integrate_system(double S0, double I0, double R0, double beta, double gamma, double dt, int num_steps, int return_every){
    std::vector<double> state{S0,I0,R0};
    std::vector<std::vector<double>> results;    

    for (int step = 0; step <= num_steps; ++step) { //using step as i had problems saving. First i increment time, but got 
        // double precisions erros when i where at smalled t


        double t = step * dt; // now t is not incremented, but overwritten each iteration so the check should work

        if (step % return_every == 0) {//save every is created using dt so it will hit sometimes
             results.push_back({t, state[0], state[1], state[2]});

        }
        state = take_step(state, beta, gamma, dt);
    }

    

    return pybind11::cast(results);
}

PYBIND11_MODULE(SIR_python, m) {
    m.doc() = "This is a Python binding for the SIR model";

    m.def("integrate_system", &integrate_system);
}
