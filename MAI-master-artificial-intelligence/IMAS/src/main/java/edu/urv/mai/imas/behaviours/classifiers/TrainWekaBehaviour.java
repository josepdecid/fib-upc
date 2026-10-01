package edu.urv.mai.imas.behaviours.classifiers;

import edu.urv.mai.imas.agents.ClassifierAgent;
import edu.urv.mai.imas.helpers.Constants;
import edu.urv.mai.imas.helpers.MessageUtils;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import weka.core.Instances;

import java.util.List;

import static jade.lang.acl.MessageTemplate.*;

public class TrainWekaBehaviour extends CyclicBehaviour {
    @Override
    public void action() {
        MessageTemplate mt =
                and(
                        MatchSender(Constants.MANAGER_AID),
                        or(
                                MatchPerformative(ACLMessage.INFORM),
                                MatchPerformative(ACLMessage.REQUEST)
                        )
                );

        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        if (msg.getPerformative() == ACLMessage.INFORM) {
            this.trainWeka(msg);
        } else if (msg.getPerformative() == ACLMessage.REQUEST) {
            this.predictWeka(msg);
        }
    }

    private void trainWeka(ACLMessage msg) {
        try {
            ((ClassifierAgent) myAgent).trainModel((Instances) msg.getContentObject());
            msg = MessageUtils.createMessage(ACLMessage.INFORM, Constants.MANAGER_AID);
            myAgent.send(msg);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void predictWeka(ACLMessage msg) {
        try {
            int[] predictions = ((ClassifierAgent) myAgent).predictModel((Instances) msg.getContentObject());

            ACLMessage reply = MessageUtils.createMessage(ACLMessage.INFORM, Constants.MANAGER_AID);
            reply.setContentObject(predictions);

            myAgent.send(reply);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
