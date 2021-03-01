
# __Hybrid controller__ 
## _Course of Compliance Design of Automotive Systems_
### _a.y. 2020/2021_

## __Description__
This repository contains a MATLAB/Simulink project about the Model-Based Design of a controller for a PHEV. The objective is to implement a control strategy for the allocation of the acceleration demanded by the driver to the IC engine and electric motor, depending on the current state of the vehicle, battery charge and fuel level. Similarly, the controller is in charge of managing the repartition of the braking demand between the regenerative braking and standard braking. 

## __Repository structure__
``` bash
├───Docs
│   └───Test reports
└───Hybrid-controller
    ├───Code
    │   └───GenerationReport
    ├───Controller
    ├───Plant
    ├───Simulation
    │   ├───MIL
    │   ├───PIL
    │   └───SIL
    └───Test
        ├───ControllerTest
        │   ├───Baselines
        │   ├───Test Reports
        │   └───testScenarios
        ├───FSM Test
        │   ├───Baselines
        │   ├───Inputs
        │   └───Test Reports
        └───Integration Test
            └───Inputs
```

## __Installation__
### Requirements
- MATLAB R2020b
- Simulink v10.2
#### Simulink Add-Ons 
- Vehicle Dynamics Blockset
- Simulink Test
- Simulink Requirements
- Powertrain Blockset
- Embedded Coder
- Control System Toolbox
- Simulink Coder

### Setup
1. Clone the code or download the _.zip_ file. 
2. Open the MATLAB project file `Hybrid-controller/HybridController.prj`

## Usage
The Simulink model `Hybrid-controller/Simulation/MIL/HybridVehicle.slx` contains the PHEV plant in which has been integrated the controller (with default drive cycle is the WLTP Class 3).

## Reports
This repository is provided with the following reports:
- Project report `Docs`
- Test reports `Docs/Test reports`
- MISRA check (HTML format) `Hybrid-controller/Code/MisraCheck.html`
- Code generation report `Hybrid-controller/Code/GenerationReport/Controller_contents.html`

## Authors
 - Gallina Giuseppe
 - Gargano Ivan Enzo 
 - Mirabella Michele 
 - Prignoli Francesco 
 - Rubbini Nicolò 

## License
MIT


