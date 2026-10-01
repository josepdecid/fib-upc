package edu.upc.fib.sid.behaviours.factories;

import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.helpers.MessageUtils;
import edu.upc.fib.sid.models.WaterTank;
import jade.core.behaviours.OneShotBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.util.Logger;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;
import static jade.lang.acl.MessageTemplate.*;

public class FactoryPourWaterBehaviour extends OneShotBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());
    private Boolean messageSent = false;

    @Override
    public void action() {
        WaterTank waterTank = (WaterTank) invokeMethod(myAgent, "getWasteWaterTank");
        Boolean isRaining = (Boolean) invokeMethod(myAgent, "getRaining");
        Integer currentLevel = waterTank.getCurrentLevel();

        if (isRaining) {
            ACLMessage msg = MessageUtils.createMessage(ACLMessage.INFORM, Globals.RiverAID);
            msg.setContent(String.valueOf(currentLevel));
            myAgent.send(msg);

            invokeMethod(myAgent, "pourWaterToPlant");
            log(logger, Logger.INFO, String.format(
                    "Factory %s pours %dL directly to the river",
                    myAgent.getLocalName(), currentLevel));
            return;
        }

        if (!messageSent) {
            ACLMessage msg = MessageUtils.createMessage(ACLMessage.QUERY_IF, Globals.TreatmentPlantAID);
            msg.setContent(String.valueOf(currentLevel));
            myAgent.send(msg);

            messageSent = true;
            log(logger, Logger.INFO, String.format(
                    "Factory %s queries to pour %dL. through the sewage system",
                    msg.getSender().getLocalName(), currentLevel));
        }

        MessageTemplate mt = and(MatchSender(Globals.TreatmentPlantAID),
                or(MatchPerformative(ACLMessage.CONFIRM), MatchPerformative(ACLMessage.DISCONFIRM)));
        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        if (msg.getPerformative() == ACLMessage.CONFIRM) {
            ACLMessage reply = MessageUtils.createMessage(ACLMessage.INFORM, msg.getSender());
            reply.setContent(String.valueOf(currentLevel));
            myAgent.send(reply);

            invokeMethod(myAgent, "pourWaterToPlant");
            log(logger, Logger.INFO, String.format(
                    "Factory %s pours %dL through the sewage system",
                    myAgent.getLocalName(), currentLevel));
        } else if (msg.getPerformative() == ACLMessage.DISCONFIRM) {
            invokeMethod(myAgent, "setWaitingWaterPouring", Boolean.FALSE);
            log(logger, Logger.INFO, String.format(
                    "Factory %s can't pour water through the sewage system",
                    myAgent.getLocalName()));
        }
    }
}
