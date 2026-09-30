package edu.upc.fib.sid.helpers;

import edu.upc.fib.sid.ontology.BesosRiverOntology;
import edu.upc.fib.sid.ontology.impl.RequestPourImpl;
import jade.content.AgentAction;
import jade.content.onto.basic.Action;
import jade.core.AID;
import jade.core.Agent;
import jade.domain.FIPANames;
import jade.lang.acl.ACLMessage;

public class MessageUtils {
    public static ACLMessage createMessage(int performative, AID receiver) {
        ACLMessage msg = new ACLMessage(performative);
        if (receiver != null) msg.addReceiver(receiver);
        msg.setLanguage(FIPANames.ContentLanguage.FIPA_SL0);
        msg.setOntology(BesosRiverOntology.ONTOLOGY_NAME);
        return msg;
    }

    public static void setOntologyAction(Agent agent, ACLMessage reply, AgentAction act) {
        try {
            Action action = new Action();
            action.setActor(reply.getSender());
            action.setAction(act);
            agent.getContentManager().fillContent(reply, action);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
