package edu.urv.mai.imas.helpers;

import jade.core.AID;
import jade.domain.FIPANames;
import jade.lang.acl.ACLMessage;

public class MessageUtils {
    public static ACLMessage createMessage(int performative, AID receiver) {
        ACLMessage msg = new ACLMessage(performative);
        if (receiver != null) msg.addReceiver(receiver);
        msg.setLanguage(FIPANames.ContentLanguage.FIPA_SL0);
        return msg;
    }
}