package edu.urv.mai.imas.agents;

import edu.urv.mai.imas.behaviours.classifiers.TrainWekaBehaviour;
import edu.urv.mai.imas.helpers.Constants;
import weka.classifiers.AbstractClassifier;
import weka.classifiers.bayes.NaiveBayes;
import weka.classifiers.functions.Logistic;
import weka.classifiers.functions.MultilayerPerceptron;
import weka.classifiers.functions.SMO;
import weka.classifiers.lazy.IBk;
import weka.classifiers.meta.AdaBoostM1;
import weka.classifiers.meta.LogitBoost;
import weka.classifiers.rules.OneR;
import weka.classifiers.rules.PART;
import weka.classifiers.trees.DecisionStump;
import weka.classifiers.trees.J48;
import weka.core.Instance;
import weka.core.Instances;

import java.util.ArrayList;
import java.util.List;

/**
 *
 */
public class ClassifierAgent extends BaseAgent {
    private AbstractClassifier classifier;

    @Override
    protected void setup() {
        this.name = Constants.CLASSIFIER;
        this.type = Constants.CLASSIFIER;
        super.setup();

        Object[] args = getArguments();

        // Set the ClassifierAID for global access.
//        int classifierIdx = (int) args[0];
//        Constants.CLASSIFIERS_AID.add(classifierIdx, getAID());
//        Constants.CLASSIFIERS_AID_IDX.put(Constants.CLASSIFIERS_AID.get(classifierIdx), classifierIdx);

        // Instantiate corresponding classifier from the given configuration.
        String classifierMethod = (String) args[1];
        this.classifier = this.getCorrespondingClassifier(classifierMethod);

        // Add behaviour to treat the action asked from the Manager.
        addBehaviour(new TrainWekaBehaviour());
    }

    /**
     * Train the classifier with the specified data instances.
     *
     * @param trainingData Instances of the training data in WEKA format.
     * @throws Exception If anything fails internally in WEKA processes.
     */
    public void trainModel(Instances trainingData) throws Exception {
        this.classifier.buildClassifier(trainingData);
    }

    /**
     * Run a prediction with the specified data instances and an already trained model.
     *
     * @param testData Instances to obtain the predictions of.
     * @return Array of integers corresponding to the predicted class of each instance.
     * @throws Exception If anything fails internally in WEKA processes.
     */
    public int[] predictModel(Instances testData) throws Exception {
        List<Double> predictions = new ArrayList<>();
        for (Instance instance : testData)
            predictions.add(this.classifier.classifyInstance(instance));
        return predictions.stream().mapToInt(Double::intValue).toArray();
    }

    /**
     * Instantiate the corresponding method from the configuration file.
     *
     * @param classifierMethod String with the name of the classifier.
     * @return Classifier instance, which share a common inheritance from AbstractClassifier.
     */
    private AbstractClassifier getCorrespondingClassifier(String classifierMethod) {
        switch (classifierMethod) {
            case "IBk":
                return new IBk();
            case "J48":
                return new J48();
            case "PART":
                return new PART();
            case "NaiveBayes":
                return new NaiveBayes();
            case "OneR":
                return new OneR();
            case "SMO":
                return new SMO();
            case "Logistic":
                return new Logistic();
            case "AdaBoostM1":
                return new AdaBoostM1();
            case "LogitBoost":
                return new LogitBoost();
            case "DecisionStump":
                return new DecisionStump();
            case "MLP":
                MultilayerPerceptron mlp = new MultilayerPerceptron();
                mlp.setLearningRate(0.1);
                mlp.setMomentum(0.2);
                mlp.setTrainingTime(2000);
                mlp.setHiddenLayers("3");
                return mlp;
            default:
                String errorMsg = "Specified classifier is not supported, please try another one";
                System.err.println(errorMsg);
                Runtime.getRuntime().exit(1);
                return null;
        }
    }
}
