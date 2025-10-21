import os
import time
import logging
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, FFMpegWriter


logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    datefmt="%H:%M:%S"
)

logging.getLogger("matplotlib").setLevel(logging.WARNING)

SIZE = 100
FRAMES = 200
SPEED = 0.2
DAMPING = 0.996
INITIAL_AMPLITUDE = 2.0
OUT_DIR = "/app/out"
FILENAME = "wave.mp4"


def prepare_grid(size):
    z = np.zeros((size, size))
    z_prev = np.zeros_like(z)
    c = size // 2
    z[c - 2:c + 3, c - 2:c + 3] = INITIAL_AMPLITUDE
    return z, z_prev


def setup_plot(z):
    fig, ax = plt.subplots(figsize=(6, 6))
    im = ax.imshow(z, cmap="seismic", vmin=-1, vmax=1, animated=True)
    ax.axis("off")

    cb = fig.colorbar(im, ax=ax, shrink=0.75, pad=0.03)
    cb.set_label("Amplitude da Onda", fontsize=10)

    return fig, ax, im


def step(z, z_prev, speed, damping):
    laplacian = (
        np.roll(z, 1, axis=0) + np.roll(z, -1, axis=0) +
        np.roll(z, 1, axis=1) + np.roll(z, -1, axis=1) -
        4 * z
    )
    return (2 * z - z_prev + speed * laplacian) * damping


def run_simulation():
    os.makedirs(OUT_DIR, exist_ok=True)
    z, z_prev = prepare_grid(SIZE)
    fig, ax, im = setup_plot(z)

    def update(frame):
        nonlocal z, z_prev
        z_new = step(z, z_prev, SPEED, DAMPING)
        z, z_prev = z_new, z
        im.set_array(z)
        ax.set_title(f"Onda — Frame {frame}", fontsize=12)
        return [im]


    ani = FuncAnimation(fig, update, frames=FRAMES, interval=30, blit=True)
    output_path = os.path.join(OUT_DIR, FILENAME)
    ani.save(output_path, writer=FFMpegWriter(fps=30))

    logging.info(f"Animação salva em: {output_path}")


if __name__ == "__main__":
    logging. info(f"SIZE={SIZE}|FRAMES={FRAMES}|SPEED={SPEED}|DAMPING={DAMPING}|INITIAL_AMPLITUDE={INITIAL_AMPLITUDE}")
    logging.info("Iniciando simulação de onda...")
    start_time = time.time()
    run_simulation()
    logging.info(f"Simulação concluída em {time.time() - start_time:.2f} segundos.")
