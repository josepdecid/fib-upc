package edu.urv.mai.imas.helpers;

import weka.core.Instances;

import java.io.Serializable;
import java.util.*;

public class Results implements Serializable {
    private Instances instances;
    private List<Integer> maxOccurrencesPredictions;

    public Results(Instances instances, List<List<Integer>> predictions, List<Integer> instancesPerClassifier) {
        this.instances = instances;

        Double totalInstances = instancesPerClassifier.stream().mapToDouble(Integer::doubleValue).sum();
        maxOccurrencesPredictions = new ArrayList<>();

        for (int i = 0; i < predictions.get(0).size(); i++) {
            int numClassifiers = predictions.size();
            Map<Integer, Double> predictionsCounter = new HashMap<>();

            for (int j = 0; j < numClassifiers; j++) {
                Double currentCount = predictionsCounter.getOrDefault(predictions.get(j).get(i), 0.0);
                Double additionTerm = Constants.WEIGHTED_VOTING ? instancesPerClassifier.get(j) / totalInstances : 1.0;
                predictionsCounter.put(predictions.get(j).get(i), currentCount + additionTerm);
            }

            Map.Entry<Integer, Double> maxEntry =
                    Collections.max(predictionsCounter.entrySet(),
                            Comparator.comparing(Map.Entry::getValue));

            maxOccurrencesPredictions.add(maxEntry.getKey());
        }
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        float corrects = 0;
        for (int i = 0; i < maxOccurrencesPredictions.size(); i++) {
            int realClass = (int) instances.get(i).classValue();
            if (maxOccurrencesPredictions.get(i) == realClass) corrects += 1;
            stringBuilder.append("| Predicted class: ").append(maxOccurrencesPredictions.get(i));
            stringBuilder.append("| Real class: ").append(realClass).append(" |\n");
        }

        stringBuilder.append("| Accuracy: ").append(100 * corrects / maxOccurrencesPredictions.size()).append("% /\n");
        return stringBuilder.toString();
    }
}
