package edu.urv.mai.imas.helpers;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Configuration is the Java Object representation for the simulation configuration specifications.
 */
public class Configuration implements Serializable {
    private String algorithm;
    private int numClassifiers;
    private List<Integer> instancesPerClassifier;
    private int classifyInstances;
    private String dataset;
    private String testData;

    public Configuration(Document document) {
        Node root = document.getDocumentElement();
        NodeList nodes = root.getChildNodes();
        for (int i = 0; i < nodes.getLength(); i++) {
            Node nNode = nodes.item(i);
            if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                String value = nNode.getFirstChild().getNodeValue();
                switch (nNode.getNodeName()) {
                    case "classifiers":
                        this.numClassifiers = Integer.parseInt(value);
                        break;
                    case "algorithm":
                        this.algorithm = value;
                        break;
                    case "trainingSettings":
                        this.instancesPerClassifier = new ArrayList<>();
                        for (String val : value.split(","))
                            this.instancesPerClassifier.add(Integer.parseInt(val));
                        break;
                    case "classifyInstances":
                        this.classifyInstances = Integer.parseInt(value);
                        break;
                    case "file":
                        this.dataset = value;
                        break;
                    case "testFile":
                        this.testData = value;
                        break;
                    default:
                }
            }
        }
    }

    public int getNumClassifiers() {
        return numClassifiers;
    }

    public String getAlgorithm() {
        return algorithm;
    }

    public List<Integer> getInstancesPerClassifier() {
        return instancesPerClassifier;
    }

    public int getClassifyInstances() { return classifyInstances; }

    public String getDataset() {
        return dataset;
    }

    public String getTestDataset() { return testData; }
}
