package edu.upc.fib.prop.business.search.impl;

import edu.upc.fib.prop.business.search.SearchDocument;
import edu.upc.fib.prop.exceptions.DocumentNotFoundException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.models.SortedDocumentsSet;
import edu.upc.fib.prop.models.WeightsVector;

import javax.print.Doc;
import java.util.Map;


public class SearchDocumentImpl implements SearchDocument {

    public DocumentsCollection filterByAuthor(DocumentsCollection documentsCollection, String authorName)
            throws DocumentNotFoundException {
        DocumentsCollection filteredDocuments = new DocumentsCollection();

        documentsCollection.getDocuments().stream().filter(document ->
                document.getAuthor().toLowerCase().contains(authorName.toLowerCase())).forEach(document -> {
            try {
                filteredDocuments.addDocument(document);
            } catch (InvalidDetailsException e) {
                e.printStackTrace();
            }
        });
        if (filteredDocuments.getDocuments().isEmpty()) {
            throw new DocumentNotFoundException();
        }
        return filteredDocuments;
    }

    public DocumentsCollection filterByUser(DocumentsCollection documentsCollection, String email) {
        DocumentsCollection filteredDocuments = new DocumentsCollection();
        documentsCollection.getDocuments().stream().filter(document ->
                document.getUser().toLowerCase().equals(email.toLowerCase())).forEach(document -> {
            try {
                filteredDocuments.addDocument(document);
            } catch (InvalidDetailsException e) {
                e.printStackTrace();
            }
        });
        return filteredDocuments;
    }

    @Override
    public Document filterByTitleAndAuthor(DocumentsCollection documentsCollection, String title, String authorName)
            throws DocumentNotFoundException {
        for (Document document : documentsCollection.getDocuments()) {
            if (document.getTitle().toLowerCase().equals(title.toLowerCase()) &&
                    document.getAuthor().toLowerCase().equals(authorName.toLowerCase())) {
                return document;
            }
        }
        throw new DocumentNotFoundException();
    }

    @Override
    public SortedDocumentsSet searchForSimilarDocuments(DocumentsCollection col, Document doc, int k, boolean isSuperMode) {
        if (isSuperMode) {
            WeightsVector wv1 = col.getWeights(doc);
            int min = Math.min(k, col.size());
            SortedDocumentsSet res = new SortedDocumentsSet(min);
            for (Document document : col.getDocuments()) {
                if (!doc.equals(document)) {
                    WeightsVector wv2 = col.getWeights(document);
                    Double relevance = getRelevanceFactor(wv1, wv2);
                    res.add(document, relevance);
                }
            }
            return res;
        } else {
            WeightsVector wv1 = col.getWeights2(doc);
            int min = Math.min(k, col.size());
            SortedDocumentsSet res = new SortedDocumentsSet(min);
            for (Document document : col.getDocuments()) {
                if (!doc.equals(document)) {
                    WeightsVector wv2 = col.getWeights2(document);
                    Double relevance = getRelevanceFactor(wv1, wv2);
                    res.add(document, relevance);
                }
            }
            return res;
        }
    }


    private double getRelevanceFactor(WeightsVector wv1, WeightsVector wv2){
        Double sumProd = 0.0;
        Double sumSquaresWv1 = 0.0;
        Double sumSquaresWv2 = 0.0;
        for(String term : wv1){
            sumSquaresWv1 += wv1.getWeight(term)*wv1.getWeight(term);
            if(wv2.contains(term)) {
                sumProd += wv1.getWeight(term) * wv2.getWeight(term);
            }
        }
        for(String term : wv2){
            sumSquaresWv2 += wv2.getWeight(term)*wv2.getWeight(term);
        }
        return sumProd/( (sumSquaresWv1 + sumSquaresWv2) - sumProd);
    }


}
