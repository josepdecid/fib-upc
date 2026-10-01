package edu.upc.fib.prop.models;

import edu.upc.fib.prop.exceptions.InvalidDetailsException;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;


public class DocumentsSet implements Iterable<Document>{
    private List<Document> documents;

    public DocumentsSet() {
        this.documents = new ArrayList<>();
    }

    public void add(Document document) {
        this.documents.add(document);
    }

    public void remove(Document document) {
        this.documents.remove(document);
    }

    public void update(Document oldDoc, Document newDoc) throws InvalidDetailsException {
        newDoc = oldDoc.merge(newDoc);
        this.documents.remove(oldDoc);
        this.documents.add(newDoc);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DocumentsSet that = (DocumentsSet) o;
        return documents != null ? documents.equals(that.documents) : that.documents == null;

    }

    public int size(){
        return this.documents.size();
    }

    @Override
    public Iterator iterator() {
        return documents.iterator();
    }

    public Document get(int index) {
        return documents.get(index);
    }
}
