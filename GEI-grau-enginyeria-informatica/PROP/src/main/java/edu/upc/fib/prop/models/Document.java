package edu.upc.fib.prop.models;

import edu.upc.fib.prop.utils.Constants;

import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class Document {
    public static final String DEFAULT_COVER = "sample.png";

    private String title;
    private String author;
    private String user;
    private String content;
    private String cover;
    private float rating;
    private Map<String, Float> termFrequency;
    private Map<String, Map<Integer, Set<Integer>>> termPositions;

    public Document(String title, String author, String content, String user) {
        termFrequency = new TreeMap<>();
        this.title = title;
        this.author = author;
        this.user = user;
        this.content = content;
        this.termFrequency = new TreeMap<>();
        this.termPositions = new TreeMap<>();
        this.rating = 0f;
        this.cover = DEFAULT_COVER;
    }

    public Document(String title, String author, String content) {
        this.title = title;
        this.author = author;
        termFrequency = new TreeMap<>();
        termFrequency = new TreeMap<>();
        this.content = content;
        this.rating = 0f;
        this.cover = DEFAULT_COVER;
    }

    /* Getters and Setters */

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public Map<String, Float> getTermFrequency() {
        return termFrequency;
    }

    public void setTermFrequency(Map<String, Float> termFrequency) {
        this.termFrequency = termFrequency;
    }

    public Map<String, Map<Integer, Set<Integer>>> getTermPositions() {
        return termPositions;
    }

    public void setTermPositions(Map<String, Map<Integer, Set<Integer>>> termPositions) {
        this.termPositions = termPositions;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getCover() {
        return cover;
    }

    public void setCover(String cover) {
        this.cover = cover;
    }

    public float getRating() {
        return rating;
    }

    public void setRating(float rating) {
        this.rating = rating;
    }

    /* Utils */

    //TODO: Extract into a logic class
    public void updateFrequencies() {
        Float max = 1f;
        termFrequency = new TreeMap<>();
        for (String word : content.split(Constants.WORD_SEPARATION_REGEX)) {
            word = word.toLowerCase();
            if (!termFrequency.containsKey(word)) {
                termFrequency.put(word, 1f);
            } else {
                Float aux = termFrequency.get(word) + 1;
                termFrequency.put(word, aux);
                if (aux > max) {
                    max = aux;
                }
            }
        }
        for (Map.Entry<String, Float> tf : termFrequency.entrySet()) {
            Float newValue = 0.5f + (0.5f * tf.getValue() / max);
            tf.setValue(newValue);
        }
    }

    //TODO: Extract into a logic class
    public void updatePositions() {
        termPositions = new TreeMap<>();
        Integer sentenceCounter = 0;
        for (String sentence : content.split(Constants.SENTENCE_SEPARATION_REGEX)) {
            Integer offsetCounter = 0;
            for (String word : sentence.split(Constants.WORD_SEPARATION_REGEX)) {
                String stdWord = word.toLowerCase();
                if (termPositions.containsKey(stdWord)) {
                    if (termPositions.get(stdWord).containsKey(sentenceCounter)) {
                        termPositions.get(stdWord).get(sentenceCounter).add(offsetCounter);
                    } else {
                        Set<Integer> offsetData = new TreeSet<>();
                        offsetData.add(offsetCounter);
                        termPositions.get(stdWord).put(sentenceCounter, offsetData);
                    }
                } else {
                    Set<Integer> offsetData = new TreeSet<>();
                    offsetData.add(offsetCounter);
                    Map<Integer, Set<Integer>> sentenceData = new TreeMap<>();
                    sentenceData.put(sentenceCounter, offsetData);
                    termPositions.put(stdWord, sentenceData);
                }
                offsetCounter++;
            }
            sentenceCounter++;
        }
    }

    public Document clone(){
        Document clonedDoc = new Document(this.title, this.author, this.content, this.user);
        clonedDoc.setTermFrequency(this.termFrequency);
        clonedDoc.setTermPositions((this.termPositions));
        clonedDoc.setRating(this.rating);
        clonedDoc.setCover(this.cover);
        return clonedDoc;
    }

    public boolean isCorrect() {
        return !this.title.equals("")
                && !this.author.equals("")
                && !this.content.equals("");
    }

    Document merge(Document newDoc) {
        Document mergedDoc = this.clone();
        if(!newDoc.getTitle().equals("")) mergedDoc.setTitle(newDoc.getTitle());
        if(!newDoc.getAuthor().equals("")) mergedDoc.setAuthor(newDoc.getAuthor());
        if(!newDoc.getContent().equals("")) mergedDoc.setContent(newDoc.getContent());
        if(!newDoc.getCover().equals("")) mergedDoc.setCover(newDoc.getCover());
        if(newDoc.getRating() != this.rating) mergedDoc.setRating(newDoc.getRating());
        return mergedDoc;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Document document = (Document) o;

        return (title != null ? title.equals(document.title) : document.title == null) &&
                (author != null ? author.equals(document.author) : document.author == null) &&
                (user != null ? user.equals(document.user) : document.user == null) &&
                (content != null ? content.equals(document.content) : document.content == null) &&
                (termFrequency != null ? termFrequency.equals(document.termFrequency) : document.termFrequency == null) &&
                (termPositions != null ? termPositions.equals(document.termPositions) : document.termPositions == null);
    }
}
