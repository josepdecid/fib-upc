package edu.upc.fib.prop.persistence.dao.documents;

import edu.upc.fib.prop.exceptions.AlreadyExistingDocumentException;
import edu.upc.fib.prop.exceptions.DocumentNotFoundException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.models.DocumentsSet;

import java.sql.Connection;

/**
 * Data Access Object for documents in persistence.
 */
public interface DaoDocuments {

    /**
     * Creates a new document in persistence.
     * @param c DB connection.
     * @param document Document to add in persistence.
     * @throws AlreadyExistingDocumentException when document already exists.
     */
    void createNewDocument(Connection c, Document document) throws AlreadyExistingDocumentException;

    /**
     * Gets all documents stored in persistence.
     * @param c DB connection.
     * @return Collection of all documents will all data.
     */
    DocumentsCollection getAllDocuments(Connection c);

    /**
     * Edits an existing document updating it with new data.
     * @param c DB connection.
     * @param oldDocument Old document to be replaced.
     * @param newDocument New document to store.
     * @throws AlreadyExistingDocumentException when document already exists.
     */
    void editExistingDocument(Connection c, Document oldDocument, Document newDocument)
            throws AlreadyExistingDocumentException;

    /**
     * Deletes an existing document in the system.
     * @param c DB connection.
     * @param document Document to delete.
     */
    void deleteExistingDocument(Connection c, Document document);

    /**
     * Updates documents owned by a user when changes account details.
     * @param c DB connection.
     * @param oldEmail Old email to replace.
     * @param newEmail New email to set.
     */
    void updateDocumentOwner(Connection c, String oldEmail, String newEmail);

    /**
     * Deletes documents owned by a user.
     * @param c DB connection.
     * @param email Email to filter documents to delete.
     */
    void deleteDocuments(Connection c, String email);

    /**
     * Rates a document.
     * @param c DB connection.
     * @param doc Document to rate.
     * @param rating Points given to the document.
     * @param user User who rates the document.
     * @throws DocumentNotFoundException when document not found in the system.
     */
    float rateDocument(Connection c, Document doc, int rating, String user) throws DocumentNotFoundException;

    /**
     * Adds a document to favourites.
     * @param c DB connection.
     * @param title Document title.
     * @param author Document author name.
     * @param user User who favourites the document.
     * @throws DocumentNotFoundException when document not found in the system.
     */
    void addDocumentToFavourites(Connection c, String title, String author, String user)
            throws DocumentNotFoundException;

    /**
     * Removes a document from favourites.
     * @param c DB connection.
     * @param title Document title.
     * @param author Document author name.
     * @param user User who remove favourite from the document.
     * @throws DocumentNotFoundException when document not found in the system.
     */
    void deleteDocumentFromFavourites(Connection c, String title, String author, String user)
            throws DocumentNotFoundException;

    /**
     * Removes all favourites of a given document from all users.
     * @param c DB Connection.
     * @param document All favourites related with this book will be deleted.
     */
    void deleteAllFavouritesOfDocument(Connection c, Document document);

    /**
     * Removes all ratings of a given document from all users.
     * @param c DB Connection.
     * @param document All ratings related with this book will be deleted.
     */
    void deleteAllRatingsOfDocument(Connection c, Document document);

    /**
     * Gets a specific document given the title and the author name.
     * @param c DB connection.
     * @param title Document title.
     * @param author Document author name.
     * @return Desired document if exists.
     */
    Document getDocument(Connection c, String title, String author) throws DocumentNotFoundException;

    /**
     * Get all user favourite documents.
     * @param c DB connection.
     * @param email User which requires favourites.
     * @return Favourite documents by a user.
     */
    DocumentsCollection getFavourites(Connection c, String email);

    /**
     * Checks if a document is or not favourite of given user.
     * @param c DB connection.
     * @param title Document title.
     * @param author Document author
     * @param email User email which requires favourites.
     * @return If document is or not favourite of given user.
     */
    boolean isDocumentFavourite(Connection c,String title, String author, String email);

    /**
     * Gets given user rating for a document.
     * @param c DB connection.
     * @param title Document title.
     * @param author Document author name.
     * @param email User email.
     * @return Rating value for desired document.
     */
    int getMyRating(Connection c, String title, String author, String email);

    /**
     * Gets a document set of numDocs recommended documents.
     * @param c DB connection.
     * @param numDocs Number of documents.
     * @param email User email.
     * @return DocumentsSet of numDocs recommended documents.
     */
    DocumentsSet getRecommendedDocuments(Connection c, int numDocs, String email);
}
