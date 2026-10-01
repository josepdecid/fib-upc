# SID-FIB-RiverAgents
River Agents Practice - Intelligent Distributed Systems

## Installation & Configuration

Set JDK 1.8.x as project SDK.

Run Maven to install all dependencies, by executing
```
mvn install
```
or just create a ``maven install`` run configuration.

If not already done, right click on ``src`` folder >
Mark Directory as > Sources Root (it will appear in blue).  

## Run

Create an application run configuration that uses ``jade.Boot`` as main class.
Set ``-gui`` as program arguments.

#### Example run usage

Following initialization can be used as test example:

```
jade.Boot -gui Besos:edu.upc.fib.sid.agents.RiverAgent;EDAR:edu.upc.fib.sid.agents.TreatmentPlantAgent(1000);F1:edu.upc.fib.sid.agents.FactoryAgent(factory_1,400,100,25);F2:edu.upc.fib.sid.agents.FactoryAgent(factory_2,100,50,10);snif:jade.tools.sniffer.Sniffer
```