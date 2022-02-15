# Fast Fractal Generation

This repository provides a quick way to generate fractals using a various number of methods.

## Starting Out
The `mandelbrot.ipynb` file provides a solid starting place to generate fractals, using python and numpy in a notebook environment.
To run the file, simply connect to the jupyter kernel and run the code.

However, this quickly becomes prohibitively slow for large image widths, for example anything above image widths of 1024 takes multiple minutes to run.

## Much faster fractal generation
Given the slowness of the fractal generating program and the necessity for it to scale well to larger image sizes, C++ is a good candidate to improve the speed of our program.  However, only the computational aspects of the fractal generation are done in C++.
At the end of the program, values in the image array are serialized to a text file and then we use a simple python script to read the deserialize the array into numpy and display it using matplotlib.

The results are impressive.  The 1024 width image runs almost instantly and the program was tested on sizes of up to 16384 with no issues and ran in a few minutes.

To run the C++ version, execute the following commands
```bash
make
./fractal
python3 parse_file.py fractal.txt <image-width>
```
where `<image-width>` is the size of the image width and height specified in `mandelbrot.cpp`

## Methodology
Fractals such as the Mandelbrot Set are defined as the set of points that are bounded while repeatedly applying some complex transformation.  More formally, a complex number $c$ is in the Mandelbrot Set if the transformation $z_{n+1} = z_n^2 + c$ is bounded for all $n$, where $z_0 = 0$.  This manifests itself quite easily in code, and from a mathematical theorem we know that if the norm of a point exceeds 2, then it will diverge and hence isn't in the Mandelbrot set.  In theory we can't run this algorithm forever, so we just have to define a number of steps that we'll run this iteration and if it hasn't diverged at the end of the algorithm, then we'll just say that the point is in the set.

Due to the finite precision of computers, we're unable to have to run this algorithm for every point in the complex plane.  Instead we define a constant, `image width` that represents the number of pixels that we'll check on the width and height.  This gives us a finite number of points to check.

## Results
Here are some generated fractals using the C++ generation.

<center>
    <figure class="image">
        <img src="images/mandelbrot-4096.png" alt="Mandelbrot Set 4096 width">
        <figcaption>Mandelbrot Set with image width 4096</figcaption>
    </figure>
</center>

<center>
    <figure class="image">
        <img src="images/mandelbrot-16384.png" alt="Mandelbrot Set 16384 width">
        <figcaption>Mandelbrot Set with image width 16384</figcaption>
    </figure>
</center>

It might be hard to tell in the browser, but the 16384 has a lot more detail when zooming into the image and in general looks less fuzzy to the eye.

In the future I would like to investigate parallelizing the C++ generation algorithm, since it's massively parallel and could introduce great speedups, enabling us to generate even more detailed images.  It would also be interesting to try rendering the image directly in C++ as well, since that would stop us from having to serialize the array and run the separate python program to generate the image.