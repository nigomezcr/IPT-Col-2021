# Unit conversion

We start with the direction perpendicular to the initial propagation (in my model I call this the y axis). On this axis we have three independent parameters:

* $$l$$: The real life length of the y axis. Dimensions: L
* Ly: Number of divisions in the x axis. Dimensions: 1
* $$\Delta y_c$$: Computational size of the step in the y axis. Dimensions: 1/L

From these three parameters we may find the conversion unit between computational and real length. We star by defining the real life ste size $$\Delta y = l / \mathrm{Ly}$$. Using this value we compute the conversion factor $$a$$:

\begin{equation}
a = \frac{\Delta y_c}{\Delta y_r} = \frac{\Delta y_c \mathrm{Ly} }{l}
\end{equation}

As we can see, the conversion factor dimensions are 1/L, just as we expected.

From these values we can calculate tha value of $$\lambda_c$$ and $h$, both needed for calculating the solution.

\begin{equation}
\lambda_c = \lambda_r \times a = \lambda_r \frac{\Delta y_c \mathrm{Ly} }{l}
\end{equation}

\begin{equation}
h = \frac{\Delta y_c^2}{2c_1} = \frac{\Delta y_c^2}{2} (2 k_0 n_0) = \frac{4 \pi n_0 \Delta y_c^2}{\lambda}
\end{equation}
where $$c_1$$ is given by the paraxial equation

## Notes
The subscript "c" denotes computational units, the subscript "r" denotes real units.