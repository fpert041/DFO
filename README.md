# DFO
Dispersive Flies Optimisation implementation in C++

### Original Algorithm: Copyright (C) 2014 Mohammad Majid al-Rifaie
#### Present C++ Porting by Francesco Perticarari

### License: This is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License.

[link to the original paper](http://doc.gold.ac.uk/mohammad/DFO/)

## What is DFO?

Dispersive Flies Optimisation Research (DFO) [1] is a swarm intelligence algorithm. That is, it is an algorithm where individual agents follow simple instructions to search for a solution in in a matrix representing an N-dimensional search space [2]. The agents are set up so that they can communicate with one another and adapt their search trajectory based on the behaviour of their neighbours.

The algorithm aims to exploit the emergent adaptive intelligence of the swarm to find an optimal solution to a given search problem. Its behaviour is inspired by the swarming behaviour of flies hovering over food sources and it has been shown to find optimal or “good enough” solutions [3] faster than randomness and of the standard versions of the well-known Particle Swarm Optimisation, Genetic Algorithm (GA) as well as Differential Evolution (DE) algorithms on an extended set of benchmarks over three performance measures of error, efficiency and reliability [4].

The algorithm was first proposed by Mohammad Majid al-Rifaie, a computing lecturer at Goldsmiths, University of London, in his paper published in 2014. For a more detailed description, please see [this blog post](http://francescoperticarari.com/dispersive-flies-optimisation/) on my website.

#### Visualisation of the Algorithm in action:

![alt text](https://i1.wp.com/upload.wikimedia.org/wikipedia/commons/e/ec/ParticleSwarmArrowsAnimation.gif "Visualisation of the Algorithm in action")

## Technical Notes

The algorithm is being showcased within an openFrameworks project to better visualise its action. The algorithm itself is not dependent on the framework and its cpp and header files can be used in any program. However, the xCode project that I included here and needs to be run within openframeworks (just place it inside apps/myApps or any folder 3 levels down from the root folder of OF). Tested with of_v0.9.8_osx_release.
