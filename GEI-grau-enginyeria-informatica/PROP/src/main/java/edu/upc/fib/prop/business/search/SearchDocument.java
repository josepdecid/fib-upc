package edu.upc.fib.prop.business.search;

import edu.upc.fib.prop.exceptions.DocumentNotFoundException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.models.SortedDocumentsSet;

public interface SearchDocument {

    /**
     * Filter documents by an existing author.
     *
     * @param documentsCollection List of all documents.
     * @param authorName          Author identifier name.
     * @return Set of matching documents.
     */
    DocumentsCollection filterByAuthor(DocumentsCollection documentsCollection, String authorName)
            throws DocumentNotFoundException;

    /**
     * Filter documents by the user owner.
     *
     * @param documentsCollection Set of all documents.
     * @param email               User to check owned documents.
     * @return Set of matching documents.
     */
    DocumentsCollection filterByUser(DocumentsCollection documentsCollection, String email);

    /**
     * Filter documents by title and author
     *
     * @param documentsCollection List of all documents
     * @param title               Document title
     * @param authorName          Author name
     * @return Matching document
     */
    Document filterByTitleAndAuthor(DocumentsCollection documentsCollection, String title, String authorName)
            throws DocumentNotFoundException;

    /**
     * Given a number k greater than 0 and a document, finds the k most similar documents in the collection.
     *
     * @param col List of all documents
     * @param doc Document which will be used as a reference.
     * @param k   number of documents that will be found if possible
     * @return A set of document sorted.
     */
    SortedDocumentsSet searchForSimilarDocuments(DocumentsCollection col, Document doc, int k, boolean isSuperMode);
}