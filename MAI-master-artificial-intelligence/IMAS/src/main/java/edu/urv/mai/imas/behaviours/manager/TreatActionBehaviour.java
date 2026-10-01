package edu.urv.mai.imas.behaviours.manager;

import edu.urv.mai.imas.agents.ManagerAgent;
import edu.urv.mai.imas.helpers.Constants;
import edu.urv.mai.imas.helpers.MessageUtils;
import edu.urv.mai.imas.helpers.Results;
import jade.core.AID;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.lang.acl.UnreadableException;
import weka.core.Instances;

import java.io.IOException;
import java.util.*;

import static edu.urv.mai.imas.helpers.DFUtils.searchDF;
import static jade.lang.acl.MessageTemplate.*;

public class TreatActionBehaviour extends CyclicBehaviour {
    @Override
    public void action() {
        // Filter for messages coming from the User requesting to train
        MessageTemplate mt =
                and(
                        MatchSender(Constants.USER_AID),
                        or(
                                MatchPerformative(ACLMessage.REQUEST),
                                MatchPerformative(ACLMessage.QUERY_IF)
                        )
                );

        // Wait until we receive a message with the specified conditions
        ACLMessage msg = myAgent.receive(mt);
        while (msg == null) {
            block();
            msg = myAgent.receive(mt);
        }

        if (msg.getContent().equals(Constants.TRAIN_ACTION) && msg.getPerformative() == ACLMessage.REQUEST) {
            msg = this.actionTrain();
            myAgent.send(msg);
            return;
        }

        if (msg.getContent().equals(Constants.TEST_ACTION)) {
            if (msg.getPerformative() == ACLMessage.REQUEST)
                msg = this.requestClassifiersToPredict();
            else
                msg = this.checkClassifiersCanPredict();

            // Send back a message to the user to inform that all classifiers have been trained properly
            myAgent.send(msg);
        }
    }

    private ACLMessage actionTrain(){
        ACLMessage msg;
        AID[] classifiers = this.requestClassifiersToTrain();
        if (classifiers == null || classifiers.length == 0) {
            // Send back a message to the user to inform about failure
            msg = MessageUtils.createMessage(ACLMessage.FAILURE, Constants.USER_AID);
            msg.setContent("No classifiers found to train");
            return msg;
        }
        this.waitAllClassifiersToFinish(classifiers);

        // Inform the Manager that the classifiers are trained
        ((ManagerAgent) myAgent).setClassifiersAsTrained();

        // Send back a message to the user to inform that all classifiers have been trained properly
        msg = MessageUtils.createMessage(ACLMessage.INFORM, Constants.USER_AID);
        msg.setContent("The model has been successfully trained");

        return msg;
    }

    private AID[] requestClassifiersToTrain() {
        AID[] classifiers = searchDF(this.myAgent, Constants.CLASSIFIER);
        if (classifiers == null || classifiers.length == 0) {
            return classifiers;
        }
        int num_classifiers = classifiers.length;

        Instances instances = ((ManagerAgent) myAgent).getInstances();
        List<Integer> instancesPerClassifier = ((ManagerAgent) myAgent).getInstancesPerClassifier();

        for (int i = 0; i < num_classifiers; i++) {
            // TODO: More elegant way
            Instances instancesSubset = new Instances(instances);

            Collections.shuffle(instancesSubset);
            for (int j = instancesPerClassifier.get(i); j < instancesSubset.size(); )
                instancesSubset.remove(j);

            try {
                ACLMessage msg = MessageUtils.createMessage(ACLMessage.INFORM, classifiers[i]);
                msg.setContentObject(instancesSubset);
                myAgent.send(msg);
            } catch (IOException e) {
                e.printStackTrace();
                return classifiers;
            }
        }
        return classifiers;
    }

    private void waitAllClassifiersToFinish(AID[] classifiers) {
        MessageTemplate mt = createMessageTemplate(classifiers);

        // Wait for all classifiers to answer
        int countResponses = 0;
        while (countResponses < classifiers.length) {
            ACLMessage msg = myAgent.receive(mt);
            while (msg == null) {
                block();
                msg = myAgent.receive(mt);
            }

            // TODO: Check no errors
            countResponses += 1;
        }
    }

    private ACLMessage requestClassifiersToPredict() {
        ACLMessage msg;
        Instances instances = new Instances(((ManagerAgent) myAgent).getTestInstances());
        Collections.shuffle(instances);

        // TODO: More elegant way
        for (int i = ((ManagerAgent) myAgent).getInstancesToPredict(); i < instances.size(); )
            instances.remove(i);

        AID[] classifiers = searchDF(this.myAgent, Constants.CLASSIFIER);
        if (classifiers == null || classifiers.length == 0) {
            msg = MessageUtils.createMessage(ACLMessage.REQUEST, Constants.USER_AID);
            msg.setContent("No classifiers found to predict");
            return msg;
        }

        for (AID classifierAID : classifiers) {
            msg = MessageUtils.createMessage(ACLMessage.REQUEST, classifierAID);
            try {
                msg.setContentObject(instances);
            } catch (IOException e) {
                e.printStackTrace();
            }
            myAgent.send(msg);
        }

        MessageTemplate mt = this.createMessageTemplate(classifiers);

        // Wait for all classifiers to answer
        List<List<Integer>> predictions = new ArrayList<>();
        for (int i = 0; i < classifiers.length; i++) predictions.add(null);

        while (predictions.contains(null)) {
            msg = myAgent.receive(mt);
            while (msg == null) {
                block();
                msg = myAgent.receive(mt);
            }

            try {
                List<Integer> classifierPredictions = new ArrayList<>();
                for (int d : (int[]) msg.getContentObject()) classifierPredictions.add(d);
                List<AID> classifiers_list = Arrays.asList(classifiers);
                predictions.set(classifiers_list.indexOf(msg.getSender()), classifierPredictions);
            } catch (UnreadableException e) {
                e.printStackTrace();
            }
        }

        Results results = new Results(instances, predictions, ((ManagerAgent) myAgent).getInstancesPerClassifier());
        msg = MessageUtils.createMessage(ACLMessage.INFORM, Constants.USER_AID);

        try {
            msg.setContentObject(results);
        } catch (IOException e) {
            // TODO: Return error agent with FIPA
            e.printStackTrace();
        }

        return msg;
    }

    private ACLMessage checkClassifiersCanPredict() {
        ACLMessage msg;
        if (((ManagerAgent) myAgent).getAreClassifiersTrained()) {
            msg = MessageUtils.createMessage(ACLMessage.CONFIRM, Constants.USER_AID);
            msg.setContent("Models correctly trained, you can request a prediction");
        } else {
            msg = MessageUtils.createMessage(ACLMessage.REFUSE, Constants.USER_AID);
            msg.setContent("You must train before the model before running a prediction");
        }
        return msg;
    }

    private MessageTemplate createMessageTemplate(AID[] classifiers) {

        // Match Senders as any of the classifiers
        MessageTemplate mtSenders = MatchSender(classifiers[0]);
        for (int i = 1; i < classifiers.length; i++)
            mtSenders = or(mtSenders, MatchSender(classifiers[i]));

        // Match the performative to be INFORM
        return and(mtSenders, MatchPerformative(ACLMessage.INFORM));
    }
}
