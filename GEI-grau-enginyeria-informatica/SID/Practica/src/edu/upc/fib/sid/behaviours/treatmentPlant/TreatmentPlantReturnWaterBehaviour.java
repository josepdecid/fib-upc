package edu.upc.fib.sid.behaviours.treatmentPlant;

import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.helpers.MessageUtils;
import edu.upc.fib.sid.models.WaterTank;
import jade.core.Agent;
import jade.core.behaviours.WakerBehaviour;
import jade.lang.acl.ACLMessage;
import jade.util.Logger;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;

public class TreatmentPlantReturnWaterBehaviour extends WakerBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());

    public TreatmentPlantReturnWaterBehaviour(Agent agent, long timeout) {
        super(agent, timeout);
    }

    public void onStart() {
        log(logger, Logger.INFO, "EDAR is treating water...");
    }

    public void onWake() {
        WaterTank waterTank = (WaterTank) invokeMethod(myAgent, "getWasteWaterTank");
        waterTank.empty();

        invokeMethod(myAgent, "setWaitingClean", Boolean.FALSE);

        ACLMessage msg = MessageUtils.createMessage(ACLMessage.INFORM, Globals.RiverAID);
        log(logger, Logger.INFO, "EDAR returns water to the river");
        myAgent.send(msg);
    }
}
