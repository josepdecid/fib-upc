package edu.urv.mai.imas.behaviours.manager;

import edu.urv.mai.imas.agents.ManagerAgent;
import edu.urv.mai.imas.helpers.Configuration;
import edu.urv.mai.imas.helpers.Constants;
import jade.core.Runtime;
import jade.core.behaviours.OneShotBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.UnreadableException;
import jade.util.Logger;
import jade.wrapper.ContainerController;
import jade.wrapper.StaleProxyException;
import weka.core.Instances;
import weka.core.converters.ArffLoader;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.net.URLDecoder;

import static edu.urv.mai.imas.helpers.Constants.CLASSIFIER_PKG;

public class InstantiateClassifiersBehaviour extends OneShotBehaviour {
    private Logger logger = Logger.getMyLogger(this.getClass().getName());

    @Override
    public void action() {
        ACLMessage msg = myAgent.receive();
        while (msg == null) {
            block();
            msg = myAgent.receive();
        }

        // Instantiate N classifiers

        try {
            int numClassifiers = ((Configuration) msg.getContentObject()).getNumClassifiers();
            String classifierModelName = ((Configuration) msg.getContentObject()).getAlgorithm();

            ((ManagerAgent) myAgent).setInstancesPerClassifier(((Configuration)
                    msg.getContentObject()).getInstancesPerClassifier());

            ((ManagerAgent) myAgent).setInstancesToPredict(((Configuration)
                    msg.getContentObject()).getClassifyInstances());

            ContainerController containerController = this.myAgent.getContainerController();
            StringBuilder nicknames = new StringBuilder();
            for (int i = 0; i < numClassifiers; i++) {
                String nickname = String.format("%s_%d", Constants.CLASSIFIER, i);
                nicknames.append(nickname).append(';');

                Object[] args = {i, classifierModelName};
                containerController.createNewAgent(nickname, CLASSIFIER_PKG, args).start();
            }

            String agentsToSniff = nicknames.toString() + "MANAGER;USER";
            containerController.createNewAgent(
                    "SNIFFER",
                    "jade.tools.sniffer.Sniffer",
                    new Object[]{agentsToSniff}
            ).start();
        } catch (UnreadableException | StaleProxyException e) {
            e.printStackTrace();
        }

        // Read dataset

        try {
            String fileName = ((Configuration) msg.getContentObject()).getDataset();
            Instances data = readData(fileName);

            ((ManagerAgent) myAgent).setInstances(data);
        } catch (UnreadableException | IOException e) {
            e.printStackTrace();
        }

        // Read test data

        try {
            if (((Configuration) msg.getContentObject()).getTestDataset() == null) {
                // If there is no test dataset, we set train data
                ((ManagerAgent) myAgent).setTestInstances(
                        ((ManagerAgent) myAgent).getInstances());
            } else {
                String fileName = ((Configuration) msg.getContentObject()).getTestDataset();
                Instances data = readData(fileName);
                ((ManagerAgent) myAgent).setTestInstances(data);

            }
        } catch (UnreadableException | IOException e) {
            e.printStackTrace();
        }
    }

    private Instances readData(String fileName) throws IOException {
        fileName = String.format("data/%s", fileName);

        URL url = getClass().getClassLoader().getResource(fileName);
        if (url == null) {
            System.out.println("Invalid file!");
            Runtime.instance().shutDown();
            java.lang.Runtime.getRuntime().exit(1);
        }

        String path = url.getFile();
        path = URLDecoder.decode(path, "UTF-8");

        BufferedReader reader = new BufferedReader(new FileReader(path));
        ArffLoader.ArffReader arffReader = new ArffLoader.ArffReader(reader);
        Instances data = arffReader.getData();
        data.setClassIndex(data.numAttributes() - 1);
        return data;
    }
}
