<!-- ![Hopf Fibration](Misc/hopf-fibration.png) -->


                                       _____ __            __  _
                                      / __(_) /  _______ _/ /_(_)__  ___
                                     / _// / _ \/ __/ _ `/ __/ / _ \/ _ \
                                    /_/ /_/_.__/_/  \_,_/\__/_/\___/_//_/
                                            FOSS Modular Synth Framework

Open source modular synthesizer embedded software framework [WIP]

# Feature
- written in C++
- based on STM32 (F303xx atm) 
- based on FreeRTOS and interfaced over [ccp_freertos](https://github.com/michaelbecker/freertos-addons) wrapper
- DMA/I2S driven audio streamer for easy external ADC/DAC interfacing
- hardware FPU enabled CMSIS DSP support
- thread-safe and DSP oriented peripheral hardware resource manager (In progress)
- Common synth component high-level implementations (pot, slider, button, led, rotary encoder... TBD)
- lightweight command shell and logger over UART (nice for experimenting and debugging)
- *Tracealyzer* support (TBD)

# Framework

        +------------+     +-----------+     +------------+     +-------------+     +-----------+   
        | Modular    |     | Module #1 |     | Module # 2 |     | Module #... |     | Module #N |   
        | Synth      |     +----+------+     +-----+------+     +------+------+     +-----+-----+   
        | apps       |          |                  |                   |                  |         
        | (hardware) |          +------------------+---------+---------+------------------+         
        |            |                                       |                                      
        +------------+  +------------+-----------+-----------+------------+------------+-----------+
        | component  |  |  Audio In  | Audio Out |   CV In   |   CV Out   |  Gate In   | Gate Out  |
        | drivers    |  +------------+-----------+-----------+------------+------------+-----------+
        |            |  |  Clock In  |Clock Out  |  Button   |    Knob    |   Slider   |    LED    |
        |            |  +------------+-----------+-----------+------------+------------+-----------+
        |            |  |  Display   |  microSD  |    Mic    |    and     |    more    |    ...    |
        +------------+  +------------+----+------+-----------+------------+------+-----+-----------+
        | services,  |  |   Shell/Logger  |   AudioStream    |    CMSIS DSP      |     Variable    |
        | streams    |  |                 |                  |    Q-aritmetic    |                 |
        +------------+  +-----------------+------------------+-------------------+-----------------+
        | core,      |  |         Resources Manager          |     third-party libs (FAT32, etc.)  |
        | peripheral |  +------------------------------------+-------------------------------------+
        | hardware,  |  |               FreeRTOS / ccp_freertos / SYSTEMVIEW(opt.)                 |
        | interface  |  +-----------------+------------------+-------------------+-----------------+
        |            |  |    DMA / UART   |    DMA / I2S     |       HW FPU      |    ADC / GPIO   |
        +------------+  +-----------------+------------------+-------------------+-----------------+
        |            |  |                                STM32 HAL                                 |
        |  BSP/MSP   |  +--------------------------------------------------------------------------+
        |  hardware  |  |                               STM32F303XX                                |
        +------------+  +--------------------------------------------------------------------------+

# Modules

> Particle physics themed modular system ...heh

        +=========+=================================+    +=========================================+
        | Name    | Feature Set                     |    |           The Standard Model            |
        +=========+=================================+    +=========================================+
        | Higgs   |                ?                |    |           | Scalar  | Higgs Boson       |
        +---------+---------------------------------+    |           +---------+-------------------+
        | Photon  |                ?                |    |           |         | Photon            |
        +---------+---------------------------------+    |           |         +-------------------+
        | Gluon   |                ?                |    |  Bosons   |         | Gluon             |
        +---------+---------------------------------+    |           |  Gauge  +-------------------+
        | Wiggs   |                ?                |    |           |         | W Boson           |
        +---------+---------------------------------+    |           |         +-------------------+
        | Ziggs   |                ?                |    |           |         | Z Boson           |
        +---------+---------------------------------+    +-----------+---------+-------------------+
        | Quarp   |                ?                |    |           |         | Up                |
        +---------+---------------------------------+    |           |         +-------------------+
        | Charm   |                ?                |    |           |         | Charm             |
        +---------+---------------------------------+    |           | Quarks  +-------------------+
        | Fermit  |                ?                |    |           |         | Top               |
        +---------+---------------------------------+    |           |         +-------------------+
        | Dark    |                ?                |    |           |         | Down              |
        +---------+---------------------------------+    |           |         +-------------------+
        | Strange |                ?                |    |           |         | Strange           |
        +---------+---------------------------------+    |           +---------+-------------------+
        | Leptron |                ?                |    | Fermions  |         | Lepton            |
        +---------+---------------------------------+    |           |         +-------------------+
        | Muon    |                ?                |    |           |         | Muon              |
        +---------+---------------------------------+    |           |         +-------------------+
        | Tau     |                ?                |    |           |         | Tau               |
        +---------+---------------------------------+    |           | Leptons +-------------------+
        | Leptro  |                ?                |    |           |         | Tau Neutrino      |
        +---------+---------------------------------+    |           |         +-------------------+
        | Mutro   |                ?                |    |           |         | Muon Neutrino     |
        +---------+---------------------------------+    |           |         +-------------------+
        | Etro    |                ?                |    |           |         | Electron Neutrino |
        +---------+---------------------------------+    +-----------+---------+-------------------+

# Status
Unreleased, still very much work in progress.

# Development Enviroment

Started and mostly continued on Raspberry Pi4 (Raspbian OS) remotely using VSCode "Remote - WSL" extension
(ms-vscode-remote.remote-wsl) from Windows PC. Yes, that is a pretty weird setup.

## Windows
Windows WSL (Ubuntu enviroment on Windows) can be used to build the project. Unfortunately flashing/debugging target 
device is not possible because WSL does not support USB. Although there's a workaround:

1. Remove `st-*` tools if already installed on WSL: `sudo apt remove stlink-tools`
2. Download [st-link toolset binaries for windows](https://github.com/stlink-org/stlink/releases) manually
(`stlink-X.X.X-x86_64-w64-*.zip`).
3. Unzip `st-*.exe` binaries into a directory, for example `C:/User/<user>/bin`.
4. Add directory path into `Path` global variable.
5. Rename `st-*.exe` by removing extension `.exe` suffix (`st-info`, st-flash`, etc.). 
6. Now you should be able to use `st-*` executables from within Windows WSL. `Utils\flash.sh` and other bash scripts should work now.

## Linux

Development works best on linux enviroment.

## Dependencies
`gcc-arm-none-eabi cmake cmake stlink-tools`


> TBD: building natively on Windows (minGW/Cygwin)

# License
- software GNU GPL-3.0
- hardware CERN OHL-2.0

