# Arm Manipulator 6 DOF Control with Arduino and Simulink
Implementation of Arm Manipulator 6 DOF with Simulink, Stateflow for Arduino.

### Requirements
```
> Arduino Mega 2560
> Tinkerkit Braccio Model
> Robotics System Toolbox
> Simulation 3D Animation 9.2
```

### Getting Started
Best Practise to maintain clean code,
```
>> cfg.CacheFolder = fullfile(eval(['pwd']), 'cacheDir');
>> cfg.CodeGenFolder = fullfile(eval(['pwd']),'codeDir');
>> Simulink.fileGenControl('setConfig', 'config', cfg,'createDir',true);
```
set the baudrate for arduino model mega 2560,
```
codertarget.arduinobase.registry.setBaudRate('simulink_model_name', 9600)
```
set paths data in matlab workspace
```
>> addpath(genpath('data'))
>> addpath(genpath('functions'))
```

## Project
This project consists in:
1. Designing of Robot Model with URDF.
2. Simulation KIN and Inverse KIN for target acquisition.
3. Design of Controller for Arm Manipulator 6 DOF.
4. Generate stand-alone code for `Tinkerkit Braccio` model.
5. Connect `PixyCam` to acquire the waypoints. 

### Directories Layout
```
├── modelBraccioHWImplementation.slx        # Simulation Phase
├── modelBraccioSimulation.slx              # HW Implementation Phase
├── RobotArmControl.slx                     # Test to connect Tinkerkit Shield
├── Braccio_trajectory_tracking.slx         # Test to generate trajectory
├── FK_IK.slx                               # Test FK and IK
├── IK_trajectory_tracking.m                # Script to test path generator
├── functions                               # Matlab functions files
│   └── ...
├── data                                    # Ws data collectors
│   └── ...
├── graphics                                # wrl and x3d files
│   └── ...
├── Tinkerkit_model                         # URDF and stl files 
│   └── ...
├── docs
│   └── ...
└── README.md
```
<!-- Forse sarebbe meglio suddividere in cartelle gli script e i modelli -->

## Simulation
<i> Work in progress... </i>

## HW Implementation
<i> Work in progress... </i>

## Authors
- <a href=https://github.com/AngeloDamante> Angelo D'Amante </a>
- <a href=https://github.com/LorisYo> Lorenzo Falai </a>
