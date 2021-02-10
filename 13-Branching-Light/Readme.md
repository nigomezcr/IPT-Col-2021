# Problem 13: Branching Light

__Problem Statement__

When a laser beam passes through a thin film (e.g., soap bubble film), random filaments of light are created in an effect known as branch flow.
1. Explain the phenomenon.
2. Can one design a medium to produce specific branching patterns?
3. Can it be extended to other wave phenomena (water waves or sound waves), etc?

[Source Video](https://youtu.be/UNCNp1tBqKY)

## 1. Explain the phenomenon
Following Patsky's et al. theory, this phenomenon arises from differences in the thickness of the soapy water film. This affects the effective two dimensional refractive index that affects the waves along the film, which can be described by an effective potential. This potential must have a specific magnitude an autocorrelation function (which is in turn depends on wavelength) in order for the wave to exhibit branch flow.

Given the experimental difficulties for measuring the film thickness with materials found in a common household, we'll develop this problem via a numerical solution of the Helmholtz with the potential described by Patsky et al.

Also a theory explaining why the film changes thickness is under development using fluid mechanics. This theory is based on the fact that turbulent flow has different speeds, and therefore, by Bernoulli's law, pressure changes that ultimately change the thickness. Due to limited time, developing this theory won't be a priority. However the model will be developed just in case experiments end up being simple.

### Simulation to-do list
1. Find a way of numerically constructing an effective potential as described by Patsky et al. In principle, the first step wold be finding a way of doing this from the autocorrelation function.
2. Defining the method to be used for numerically reproducing branch flow. One option would be numerically solving Helmholtz equation on the potential found above. The other option would be using a Lattice-Boltzmann (I belive this would be an overkill).
3. Actually building the numerical solution, and getting results for different potentials and wave forms.

### Turbulence theory points to develop
* The film may be modeled as a two dimensional array of eddies, whose radius is determined mainly by temperature (which is held constant) and viscosity, that can be controlled in the experiments.
* What is the speed on each point of the eddy? Does it depend on the radius?
* Eddies may not be necessary, this can be developed further as it may be simpler then the array model.

## 2. Can one design a medium to produce specific branching patterns?
We propose three main parameters of the film that can affect the branch pattern: soap concentration, viscosity of the mix and shape. Along these parameters we propose two parameters of the branches to be studied: distance from the incidence point to first node, and average spread angle of the branches, measured from the first node. The first step is to show there is a correlation between these variables, and then study the effects of changing the film.

### Experimental to-do list
1. Measure the minimum amount of soap needed for a film to form, and for branch flow to happen. My guess is that this are the same.
2. Find a qualitative soap concentration, viscosity and shape that are optimum for branch flow.
3. Take about 100 different pictures of branched flow for the values found in 2 in order to find if there is a correlation between the proposed parameters.
4. If there is, start changing them. If not, find other set of parameters. Anyhow, at this point we should meet.

## 3. Can it be extended to other wave phenomena (water waves or sound waves), etc?
__This is not well developed yet.__

1. Find the theoretical analogues for critical parameters in fluids (surface and gravity waves) and sound.

2. Develop simulations of the branched flow in other media.

3. Try to reproduce branched flow on a fluid.

4. How can you measure experimentally branched flow on sound waves?
