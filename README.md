# Tinkerkit Braccio 5 DOF control with Simulink
Modeling, Simulation and Implementation of Arm Manipulator with 5 DOF.

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
4. Generate stand-alone code for `Tinkerkit Braccio` model.
5. Design of `TrajectoryTracking` Task.
6. Design of `Pick&Place` Task.

### Directories Layout
```
├── +classes                                # Classes definitions files
│   ├── Joint.m
│   ├── Link.m
│   ├── oIKINSolver.m
│   ├── oKINSolver.m
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
│   ├── hardware                            # Hardware code-generator models
│   │   ├── mBraccioHWblocks.slx
│   │   ├── mBraccioHW.slx                  # HW phase
│   │   ├── mHelloBraccio.slx               # To test Platform
│   │   ├── mReadMask.slx
│   │   ├── mRescue.slx
│   │   └── mWriteMask.slx
│   ├── kinematics                          # Kinematics models
│   │   ├── mIkinBlock.slx
│   │   ├── mIkinValidator.slx
│   │   └── mKinBlock.slx
│   ├── simulation                          # Robotics Toolbox models
│   │   ├── mBraccioSimulation.slx          # Simulation Phase
│   │   ├── mFK.slx
│   │   └── mIK.slx
│   └── tasks                               # Task models
│       ├── mRobotArm_PickAndPlace.slx      # P&P model
│       └── mTrackingSignalBased.slx        # TrajectoryTracking model
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
├── IK_trajectory_tracking.m                # Script to start TT task
└── README.md
```

## Modeling
The development platform is the Arduino Braccio Tinkerkit model with its workspace
<p align=center>
    <img src=docs/imgBraccio/BraccioDescr.png width="300"> <img src=docs/imgBraccio/ws.png width="400">
</p>
and the follow forward kinematics mapping.
<p align=center>
    <img src=docs/imgBraccio/kinBraccio.png width="300">
</p>


## Simulation
In this phase, we used the ```Robotics Toolbox``` to compute Forward Kinematics and Inverse Kinematics. ```VR Sink``` to simulate movements in virtual world. 
<p align=center>
    <img src=docs/imgBraccio/detailsBraccio6dofee.png width="600">
</p>
the resulting model is the following
<p align=center>
    <img src=docs/imgBraccio/simTTmodel.png width="600">
</p>

## HW Implementation
We have implemented two solutions to compute KIN and IKIN problems.
<p align=center>
    <img src=docs/imgBraccio/kin_ikin_solutions.png width="600">
</p>

### With Simulink Block - visual programming
in this case we have used the ```Commonly Used Block```, ``` Math Operations ```, ```Ports Subsystem```, ``` Sink``` libraries.
<p align=center>
    <img src=docs/imgBraccio/mIKINblock_sub1.png width="600">
</p>

### With System Objects - OOP
In this case, the software developed is shown in UML below.
<p align=center>
    <img src=docs/imgBraccio/uml.png width="600">
</p>

## Authors
- <a href=https://github.com/AngeloDamante> Angelo D'Amante </a>
- <a href=https://github.com/LorisYo> Lorenzo Falai </a>
