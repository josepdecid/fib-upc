package edu.upc.fib.sid.behaviours.factories;

import edu.upc.fib.sid.helpers.Globals;
import edu.upc.fib.sid.helpers.ReflectionUtils;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;

import static edu.upc.fib.sid.helpers.ReflectionUtils.invokeMethod;
import static jade.lang.acl.MessageTemplate.*;
import static jade.lang.acl.MessageTemplate.MatchPerformative;

public class FactoryBypassBehaviour extends CyclicBehaviour {
    @Override
    public void action() {
        MessageTemplate mt = and(MatchSender(Globals.RiverAID), MatchPerformative(ACLMessage.INFORM));
        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        Boolean isRaining = Boolean.parseBoolean(msg.getContent());
        invokeMethod(myAgent, "setRaining", isRaining);
    }
}
