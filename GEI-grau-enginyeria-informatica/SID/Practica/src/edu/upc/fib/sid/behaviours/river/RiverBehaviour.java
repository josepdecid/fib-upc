package edu.upc.fib.sid.behaviours.river;

import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.helpers.MessageUtils;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.util.Logger;

import static edu.upc.fib.sid.helpers.LoggerUtils.log;
import static jade.lang.acl.MessageTemplate.*;

public class RiverBehaviour extends CyclicBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());

    public void action() {
        MessageTemplate mt = or(
                and(MatchSender(Globals.TreatmentPlantAID), MatchPerformative(ACLMessage.INFORM)),
                and(not(MatchSender(Globals.TreatmentPlantAID)), MatchPerformative(ACLMessage.REQUEST)));
        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        if (msg.getPerformative() == ACLMessage.REQUEST) {
            Integer quantity = Integer.valueOf(msg.getContent());
            ACLMessage reply = MessageUtils.createMessage(ACLMessage.CONFIRM, msg.getSender());
            reply.setContent(String.valueOf(quantity));
            myAgent.send(reply);
            log(logger, Logger.INFO, String.format(
                    "River gives %dL to Factory %s",
                    quantity, msg.getSender().getLocalName()));
        } else if (msg.getPerformative() == ACLMessage.INFORM) {
            log(logger, Logger.INFO, "River gets water from Treatment Plant");
        }
    }
}
