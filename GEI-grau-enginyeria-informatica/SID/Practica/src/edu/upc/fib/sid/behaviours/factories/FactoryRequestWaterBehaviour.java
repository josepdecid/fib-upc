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

public class FactoryRequestWaterBehaviour extends OneShotBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());
    private Boolean messageSent = false;

    @Override
    public void action() {
        WaterTank waterTank = (WaterTank) invokeMethod(myAgent, "getCleanWaterTank");

        if (!messageSent) {
            ACLMessage msg = MessageUtils.createMessage(ACLMessage.REQUEST, Globals.RiverAID);
            msg.setContent(String.valueOf(waterTank.getCapacity()));
            myAgent.send(msg);

            messageSent = true;
            log(logger, Logger.INFO, String.format(
                    "Factory %s requests %dL from the river",
                    msg.getSender().getLocalName(), waterTank.getCapacity()));
        }

        MessageTemplate mt = and(MatchPerformative(ACLMessage.CONFIRM), MatchSender(Globals.RiverAID));
        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        Integer waterQuantity = Integer.valueOf(msg.getContent());
        invokeMethod(myAgent, "addWaterFromRiver", waterQuantity);
        log(logger, Logger.INFO, String.format(
                "Factory %s receives %dL from the river",
                msg.getSender().getLocalName(), waterQuantity));
    }
}
