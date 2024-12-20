## Rendering the Mandelbrot Set on СPU
Project version [GitHub](https://github.com/your_username/CudaMandelbrotSet) implemented only on CPU.
### How It Works
1. **Parallel computing CPU**: The CPU calculates the color of the pixels in parallel. An exit time algorithm is used to determine whether a pixel is part of the Mandelbrot set and its color.
2. **Rendering**: The result is rendered in the SDL2 window in real-time, with potential for smooth zooming and navigation.
---
