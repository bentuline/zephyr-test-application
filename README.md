# Zephyr Test Application

Quick-start steps for building and flashing this sample with the accompanying manifest repository `zephyr-test-manifest` (pins Zephyr via west). Follow these steps if you have never run Zephyr before.

## Host prerequisites (Ubuntu/Debian)
Install the core build tools and Python venv support:
```sh
sudo apt update
sudo apt install --no-install-recommends \
  git cmake ninja-build gperf ccache dfu-util device-tree-compiler wget \
  python3.12-venv python3-dev python3-pip xz-utils file make gcc g++ libsdl2-dev
```

## Documentation

- Zephyr Getting Started Guide (official): https://docs.zephyrproject.org/latest/develop/getting_started/index.html

Run the getting started, and make sure to do a global install. It's recommended to install to home (~) to avoid permissions issue. Once setup.sh has succesffully then you can continue. 

## Set up the workspace
```sh
cd /home/dev/zephyr-workspace

# Python virtual environment (recommended)
python3.12 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install west

# Initialize west with the local manifest
west init -m git@github.com:bentuline/zephyr-test-manifest.git
west update


## Build and flash this application
Replace `<board>` with your target (e.g., `nrf52840dk_nrf52840`). Use `west boards` to list supported boards.
```sh
cd /home/dev/zephyr-workspace
west build -p always -b <board> zephyr-test-application
west flash  # optional: flash to connected hardware
```

### Rebuilding cleanly
```sh
rm -rf build
west build -p always -b <board> zephyr-test-application
```

