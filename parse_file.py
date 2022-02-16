import numpy as np
import matplotlib.pyplot as plt
import sys
from tqdm import tqdm

def main():
    file = sys.argv[1]
    shape = int(sys.argv[2])

    lines = None
    with open(file) as f:
        lines = f.readlines()

    X = np.empty((shape, shape))

    for idx, line in tqdm(enumerate(lines)):
        parsed_line = line.split("\n")[0].split(" ")
        new_line = []
        for num in parsed_line:
            if num != "":
                new_line.append(int(num))
        X[idx, :] = new_line

    fig = plt.figure(figsize=(10, 10))
    ax = plt.axes()

    ax.imshow(X.T, interpolation="bilinear", cmap='magma')
    ax.axis("off")
    plt.savefig(f"./images/mandelbrot-{shape}.png", dpi=1200)

    plt.show()


if __name__ == "__main__":
    main()
