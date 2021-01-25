# Problem 13: Branching Light

__Problem Statement__

When a laser beam passes through a thin film (e.g., soap bubble film), random filaments of light are created in an effect known as branch flow.
1. Explain the phenomenon.
2. Can one design a medium to produce specific branching patterns?
3. Can it be extended to other wave phenomena (water waves or sound waves), etc?

[Source Video](https://youtu.be/UNCNp1tBqKY)

## 1. Explain the phenomenon
According to [1], branched flow happens because an internal reflection and spatial shift at the interface (Goos-Hänchen shift). This happens only with low power lasers, because with high power ones nonlinear effects can not be ignored.

However, Patasky et al. suggest that the phenomenon arises from changes in the medium's refractive index. I think that this explanation suits more this problem, given that it uses a simpler model for the soapy water surface. They propose that the waves in the medium follow the Helmholtz equation with an additional term.

In order to construct the model that allows us to explain the phenomenon, we'll need to test this two hypothesis, and work from there:

### To do:
1. Buy all the required materials and reproduce the fundamental version of the experiment: incident ray on soap film must exhibit branched flow.

2. Measure the refractive index (average and effective) of soapy water. Find critical angle needed for total internal reflection. What optical effects can you measure from a specific surface pattern? What other (relevant) optical parameters can be extracted from the system?

3. Is there a critical parameter that completely controls the branching phenomena? (i.e., that maximizes, minimizes or completely eliminates branched flow) How can you control it? Can you measure this effect quantitatively and how? (Ideas: "fractal dimension" of the surface pattern). Can a uniform (i.e., patternless) soap water be produced? If yes, can branched flow happen on it?

### Proposed experiments
1. __Simple branched flow:__ This experiment's aim is to reproduce the phenomenon. Basically everything else depends on being able to reproduce the phenomenon.

    __Resources:__
    * Soapy water
    * Laser pointer
    * Camera to record the phenomenon

2. __Patsky et al. model validation:__ This experiment aim is to validate Patsky's model for the branched flow. 

3. __Refractive index measurement:__ This experiment's aim is to measure the effective refractive index of the soapy water, based on the fact that wavelength (and by extension, color) of light change with the refractive index. This experiment follows the one proposed by Patsky et al. 

    __Resources:__
    * Soapy water
    * RGB source (ideally) or white light source
    * Camera
    * Image analysis software

4. __Critical parameter measurement:__ I agree with Patsky et al. on the explanation that the effective refractive index is the critical parameter of the system. Because of that, the first thing is to try to modify the refractive index of the soapy water, and then to show how it affects the branching pattern.

    __Resources:__
    * Soapy water
    * Laser pointer
    * RGB source (ideally) or white light source
    * Camera
    * Image analysis software
    * Various soaps and waters (distilled, etc.)
    * Heat and cold source

    __Exploratory cool things:__
    * Could you do this on oil or alcohol?


## 2. Can one design a medium to produce specific branching patterns?
1. How can you change the optical parameters of the system (refractive index and critical angle, overall surface pattern, etc.)? (Type of soap, bubble size, introducing air bubbles in the surface, etc.). Do they change with time? Is it random? Can they be fixed in time? How can you control them?

2. What optical parameters of the system change the branching pattern? Is this change consistent? Can it be measured quantitatively? 

3. Develop a simulation of branched flow using this information. Contrast it with experimental results.

### Proposed experiments
1. __Critical parameter variation:__ Same as experiment 1.3, but with different approach. Try to push the phenomenon to the maximum, trying to change as much as possible the components of the system.

    __Resources:__
    * Soapy water
    * Various laser pointers (different wavelengths)
    * RGB source (ideally) or white light source
    * Camera
    * Image analysis software
    * Various soaps and waters (distilled, etc.)
    * Heat and cold source
    * Various other liquids (Alcohol, Oil)

## 3. Can it be extended to other wave phenomena (water waves or sound waves), etc?
1. Find the theoretical analogues for critical parameters in fluids (surface and gravity waves) and sound.

2. Develop simulations of the branched flow in other media.

3. Try to reproduce branched flow on a fluid.

4. How can you measure experimentally branched flow on sound waves?
