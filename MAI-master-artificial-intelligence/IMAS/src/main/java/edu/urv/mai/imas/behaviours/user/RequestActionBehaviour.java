package edu.urv.mai.imas.behaviours.user;

import edu.urv.mai.imas.agents.UserAgent;
import edu.urv.mai.imas.helpers.Constants;
import edu.urv.mai.imas.helpers.MessageUtils;
import edu.urv.mai.imas.helpers.Results;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.UnreadableException;

import java.util.Scanner;

public class RequestActionBehaviour extends CyclicBehaviour {
    private Scanner scanner = new Scanner(System.in);
    private long actionStartTime;

    @Override
    public void action() {
        System.out.print("Introduce action (T / P / L): ");
        String action = scanner.nextLine().toUpperCase();

        actionStartTime = System.nanoTime();

        switch (action) {
            case "T":
                requestTrain();
                break;
            case "P":
                requestPredict();
                break;
            case "L":
                System.out.print("Introduce action file path: ");
                String configurationFileName = scanner.nextLine().toUpperCase();
                myAgent.addBehaviour(new ReadConfigurationBehaviour(configurationFileName));
                break;
            default:
                System.err.println("Invalid Option (T / P / L)");
                break;
        }

    }

    private void requestTrain() {
        ACLMessage msg = MessageUtils.createMessage(ACLMessage.REQUEST, ((UserAgent) this.myAgent).getManagerAID());
        msg.setContent(Constants.TRAIN_ACTION);
        myAgent.send(msg);

        msg = myAgent.receive();
        while (msg == null) {
            block();
            msg = myAgent.receive();
        }

        System.out.println(msg.getContent());

        long timeElapsed = System.nanoTime();
        System.out.println((timeElapsed - actionStartTime) / 1000000);
    }

    private void requestPredict() {
        ACLMessage msg = MessageUtils.createMessage(ACLMessage.QUERY_IF, Constants.MANAGER_AID);
        msg.setContent(Constants.TEST_ACTION);
        myAgent.send(msg);

        msg = myAgent.receive();
        while (msg == null) {
            block();
            msg = myAgent.receive();
        }

        if (msg.getPerformative() == ACLMessage.CONFIRM) {
            msg = MessageUtils.createMessage(ACLMessage.REQUEST, Constants.MANAGER_AID);
            msg.setContent(Constants.TEST_ACTION);
            myAgent.send(msg);

            msg = myAgent.receive();
            while (msg == null) {
                block();
                msg = myAgent.receive();
            }

            try {
                Results results = (Results) msg.getContentObject();
                System.out.println(results.toString());

                long timeElapsed = System.nanoTime();
                System.out.println((timeElapsed - actionStartTime) / 1000000);
            } catch (UnreadableException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("You must train the model before running predict");
        }
    }
}
