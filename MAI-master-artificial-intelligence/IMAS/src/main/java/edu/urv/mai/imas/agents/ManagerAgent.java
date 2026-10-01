package edu.urv.mai.imas.agents;

import edu.urv.mai.imas.behaviours.manager.InstantiateClassifiersBehaviour;
import edu.urv.mai.imas.behaviours.manager.TreatActionBehaviour;
import edu.urv.mai.imas.helpers.Constants;
import weka.core.Instances;

import java.util.List;

/**
 * The Manager agent holds the logistic part of being the bridge between the User and the Classifiers, receiving actions
 * to perform, and using its internal state, which contains the data, and parameters for training to communicate with
 * the classifiers and ask them to perform an specific task which its corresponding parameters and slice of data. When
 * the simulation starts, it receives the configuration of the simulation from the user and it reads and builds the
 * required dataset and classifiers with the corresponding parameters respectively. It also builds back a report for the
 * user with the prediction results, to simplify its interpretation.
 */
public class ManagerAgent extends BaseAgent {
    // Indicates if classifiers have been trained.
    private boolean areClassifiersTrained = false;
    // Dataset representation in WEKA prepared format.
    private Instances instances;
    // Test instances in WEKA prepared format
    private Instances testInstances;
    // Number of instances to send to each classifier to train the model.
    private List<Integer> instancesPerClassifier;
    // Number of instances to use (randomly selected) when running a prediction.
    private int instancesToPredict;

    @Override
    protected void setup() {
        this.name = Constants.MANAGER;
        this.type = Constants.MANAGER;
        super.setup();

        // Set the ManagerAID for global access.
        Constants.MANAGER_AID = getAID();

        // Add behaviour to create the specified classifiers by the configuration received from the user.
        addBehaviour(new InstantiateClassifiersBehaviour());

        // Add behaviour to treat the action asked from the User (T) train or (P) predict.
        addBehaviour(new TreatActionBehaviour());
    }

    // -------------------------------------------
    // Getters and Setters for the private fields.
    // -------------------------------------------

    public boolean getAreClassifiersTrained() {
        return areClassifiersTrained;
    }

    public void setClassifiersAsTrained() {
        this.areClassifiersTrained = true;
    }

    public Instances getInstances() {
        return instances;
    }

    public void setInstances(Instances instances) {
        this.instances = instances;
    }

    public Instances getTestInstances() {
        return testInstances;
    }

    public void setTestInstances(Instances testInstances) {
        this.testInstances = testInstances;
    }

    public List<Integer> getInstancesPerClassifier() {
        return instancesPerClassifier;
    }

    public void setInstancesPerClassifier(List<Integer> instancesPerClassifier) {
        this.instancesPerClassifier = instancesPerClassifier;
    }

    public int getInstancesToPredict() {
        return instancesToPredict;
    }

    public void setInstancesToPredict(int instancesToPredict) {
        this.instancesToPredict = instancesToPredict;
    }
}
