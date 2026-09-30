package edu.upc.fib.sid.behaviours.factories;

import edu.upc.fib.sid.helpers.DFUtils;
import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.models.WaterTank;
import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.TickerBehaviour;
import jade.util.Logger;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;

public class FactoryMainBehaviour extends TickerBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());
    private boolean ready = false;

    public FactoryMainBehaviour(Agent agent, long period) {
        super(agent, period);
    }

    @Override
    protected void onTick() {
        if (!ready) {
            getAgentsAIDs();
            if (!ready) return;
        }

        Boolean waitingWaterRequest = (Boolean) invokeMethod(myAgent, "getWaitingWaterRequest");
        Boolean waitingWaterPouring = (Boolean) invokeMethod(myAgent, "getWaitingWaterPouring");

        if (!waitingWaterRequest && !waitingWaterPouring) {
            WaterTank wasteWaterTank = (WaterTank) invokeMethod(myAgent, "getWasteWaterTank");
            if (wasteWaterTank.isFull()) {
                invokeMethod(myAgent, "setWaitingWaterPouring", Boolean.TRUE);
                myAgent.addBehaviour(new FactoryPourWaterBehaviour());
                return;
            }

            WaterTank cleanWaterTank = (WaterTank) invokeMethod(myAgent, "getCleanWaterTank");
            if (!cleanWaterTank.isEmpty()) {
                Integer cost = (Integer) invokeMethod(myAgent, "getProcessCost");
                cleanWaterTank.subtractWater(cost);
                wasteWaterTank.addWater(cost);
                log(logger, Logger.INFO, String.format(
                        "Factory %s uses %d in his procedures (cleanL = %d | wasteL = %d)",
                        myAgent.getLocalName(), cost, cleanWaterTank.getCurrentLevel(), wasteWaterTank.getCurrentLevel()));
                return;
            }

            invokeMethod(myAgent, "setWaitingWaterRequest", Boolean.TRUE);
            myAgent.addBehaviour(new FactoryRequestWaterBehaviour());
        }
    }

    private void getAgentsAIDs() {
        if (Globals.RiverAID == null)
            Globals.RiverAID = DFUtils.getRiverAID(myAgent);
        if (Globals.TreatmentPlantAID == null)
            Globals.TreatmentPlantAID = DFUtils.getTreatmentPlantAID(myAgent);

        AID currentAID = myAgent.getAID();
        if (!Globals.isFactoryRegistered(currentAID))
            Globals.FactoriesAIDs.add(currentAID);

        if (Globals.RiverAID != null && Globals.TreatmentPlantAID != null) ready = true;
    }
}
