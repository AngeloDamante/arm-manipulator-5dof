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
>> codertarget.arduinobase.registry.setBaudRate('simulink_model_name', 9600)
```
prepare the matlab and simulink environment
```
>> initSim.m       # To start simulation env with Robotics Toolbox
>> initHW.m        # To start HW with code generation and Unit Test
```
remember: <b>you can only start in real robot model with all</b> ```successful tests``` as the following output. 
```
Ut: PASS ---- carnotRule
Ut: PASS ---- computeT
UT: PASS ---- Robot builded in 0.43 ms:
UT: PASS ---- IK computed in 1.89 ms:
UT: PASS ---- FK computed in 0.01 ms:
Ut: PASS ---- FK_IK class works fine
```

## Project
This project consists in:
1. Designing of Robot Model with URDF.
2. Simulation KIN and Inverse KIN for target acquisition.
3. HW Implementation of KIN and Inverse KIN for target acquisition.
4. Design of Controller for Arm Manipulator 6 DOF.
5. Generate stand-alone code for `Tinkerkit Braccio` model.
6. Connect `PixyCam` to acquire the waypoints. 

### Directories Layout
```
├── +classes                                # Classes definitions files
│   ├── Joint.m
│   ├── Link.m
│   └── Robot5Dof.m
├── +functions                              # Matlab functions files
│   ├── computeT.m
│   ├── carnotRule.m
│   ├── evaluateUsageMemory.m
│   ├── isInsideWorkspace.m
│   └── makeWS.m
├── +unittests                              # UT files
│   ├── utCarnot.m
│   ├── utComputeT.m
│   ├── utEstimateMemory.m
│   └── utFkIk.m
├── models         
│   ├── simulation                          # Robotics Toolbox models
│   │   ├── mBraccioSimulation.slx          # Simulation Phase
│   │   └── ...
│   └── hardware                            # Hardware code-generator models
│       ├── mHelloBraccio.slx               # To test tinkerkit shield
│       ├── mBraccioHW.slx                  # HW phase
│       └── ...
├── data                                    # Ws data collectors
│   └── ...
├── graphics                                # wrl and x3d files
│   └── ...
├── Tinkerkit_model                         # URDF and stl files 
│   └── ...
├── docs                                    # utils docs
│   └── ...
├── initSim.m                               # Script to start simulation
├── initHW.m                                # Script to start HW implementation
└── README.md
```

## Simulation
<i> Work in progress... </i>

## HW Implementation
<i> Work in progress... </i>

## Authors
- <a href=https://github.com/AngeloDamante> Angelo D'Amante </a>
- <a href=https://github.com/LorisYo> Lorenzo Falai </a>
