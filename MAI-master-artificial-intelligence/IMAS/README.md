# Agent-based Decision Support System (A-DSS)

Introduction to Multiagent Systems project using JADE.

Authors:

- [Marta Barroso](https://github.com/martabarroso)
- [Arnau Canyadell](https://github.com/a-canya)
- [Josep de Cid](https://github.com/jdecid)
- [Gonzalo Recio](https://github.com/gonzalorecio)
- [Jana Reventós](https://github.com/jreventos)

We keep track of the project using [Trello](https://trello.com/b/KrmINhkV/imas-eportfolio) as an e-portfolio.

## Installation & Configuration

Download and install [JDK 1.8.x](https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html). 
Go to `File > Project Structure > Project SDK` and set the downloaded Java.

We assume the usage of [IntelliJ](https://www.jetbrains.com/idea/) as the project IDE to define its configurations. Steps:

1) Open project with IntelliJ
2) If `pom.xml` is not detected as Maven config (m icon doesn't appear), right click in 
`root folder > Add Framework Support... > Maven`
3) Create a maven configuration with `Add Configuration... > + Maven Configuration`. At `Command line:` write `install`
 and then press `OK`.

Maven dependencies can also be installed running `mvn install`

If not already done, right click on:
- `src > main > java` Mark Directory as > <span style="color:blue">Sources Root</span>
- `src > main > resources` Mark Directory as > <span style="color:yellow">Resources Root</span>
- `src > test` Mark Directory as > <span style="color:green">Test Sources Root</span>

## Run

Create an application run configuration that uses ``jade.Boot`` as main class.
Set ``-gui`` as program arguments.

#### Example run usage

Following parameters can be used in a basic run example:

```
-gui USER:edu.urv.mai.imas.agents.UserAgent(basicSimulation);MANAGER:edu.urv.mai.imas.agents.ManagerAgent;
```