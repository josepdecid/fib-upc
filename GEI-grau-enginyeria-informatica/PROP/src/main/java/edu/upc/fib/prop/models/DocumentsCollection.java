package edu.upc.fib.prop.models;

import edu.upc.fib.prop.exceptions.AlreadyExistingDocumentException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class DocumentsCollection {

    private List<Document> documents;
    private Map<String, Integer> wordsFrequencies;

    public DocumentsCollection() {
        this.documents = new ArrayList<>();
        this.wordsFrequencies = new TreeMap<>();
    }

    public List<Document> getDocuments() {
        return documents;
    }

    public void addDocument(Document document) throws InvalidDetailsException{
        if(!document.isCorrect()) throw new InvalidDetailsException();
        this.documents.add(document);

        for(Map.Entry<String,Float> entry : document.getTermFrequency().entrySet()) {
            addWord(entry.getKey());
        }
    }

    public void deleteDocument(Document document) {
        this.documents.remove(document);
        for(Map.Entry<String,Float> entry : document.getTermFrequency().entrySet()) {
            removeWord(entry.getKey());
        }
    }

    public boolean containsTitleAndAuthor(String title, String author){
        return (this.getDocument(title,author) != null);
    }

    public Document updateDocument(Document oldDocument, Document newDocument)
            throws InvalidDetailsException, AlreadyExistingDocumentException {
        Document updatedDoc = oldDocument.merge(newDocument);
        if (!updatedDoc.isCorrect()) throw new InvalidDetailsException();
        if (!oldDocument.getContent().equals(newDocument.getContent())){
            updatedDoc.updateFrequencies();
            updatedDoc.updatePositions();
        }
        this.documents.remove(oldDocument);
        for(Map.Entry<String,Float> entry : oldDocument.getTermFrequency().entrySet()) {
            removeWord(entry.getKey());
        }
        this.documents.add(updatedDoc);
        for(Map.Entry<String,Float> entry : updatedDoc.getTermFrequency().entrySet()) {
            addWord(entry.getKey());
        }
        return updatedDoc;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DocumentsCollection that = (DocumentsCollection) o;
        return documents != null ? documents.equals(that.documents) : that.documents == null;
    }

    private void addWord(String word){
        if (wordsFrequencies.containsKey(word)) wordsFrequencies.put(word, wordsFrequencies.get(word) + 1);
        else wordsFrequencies.put(word, 1);
    }

    private void removeWord(String word){
        if(wordsFrequencies.containsKey(word)) wordsFrequencies.put(word, wordsFrequencies.get(word) - 1);
        if(wordsFrequencies.get(word) <= 0) wordsFrequencies.remove(word);
    }

    // Inverse document frequency smooth.
    private Float getIdf(String word){
        if(!wordsFrequencies.containsKey(word)) return 0f;
        return (float)Math.log((float)documents.size() / (1 + (float)wordsFrequencies.get(word)));
    }

    // Probabilistic inverse document frequency.
    private Float getIdf2 (String word) {
        if (!wordsFrequencies.containsKey(word)) return 0f;
        return (float)Math.log(((float)documents.size() - (float)wordsFrequencies.get(word)) + 0.5 / (float)wordsFrequencies.get(word));
    }

    public int size(){ return documents.size();}

    private Document getDocument(String title, String author){
        for(Document d : documents) {
            if (d.getTitle().toLowerCase().equals(title.toLowerCase()) &&
                    d.getAuthor().toLowerCase().equals(author.toLowerCase())) {
                return d;
            }
        }
        return null;
    }

    public DocumentsSet getAllDocuments() {
        DocumentsSet ds = new DocumentsSet();
        for(Document doc : this.documents) ds.add(doc);
        return ds;
    }

    public WeightsVector getWeights(Document doc){
        WeightsVector vec = new WeightsVector();

        for (Map.Entry<String, Float> tf : doc.getTermFrequency().entrySet()) {
            vec.put(tf.getKey(), tf.getValue() * getIdf(tf.getKey()));
        }

        return vec;
    }

    public WeightsVector getWeights2(Document doc){
        WeightsVector vec = new WeightsVector();

        for (Map.Entry<String, Float> tf : doc.getTermFrequency().entrySet()) {
            vec.put(tf.getKey(), tf.getValue() * getIdf2(tf.getKey()));
        }

        return vec;
    }


}
