package edu.upc.fib.prop.view.controllers;

import edu.upc.fib.prop.exceptions.*;

import java.sql.SQLException;

public interface ViewGraphicController {

    /**
     * Gets all authors given a prefix.
     * @param authorPrefix Given prefix to filter authors.
     * @return Collection of matching authors.
     */
    String getAuthorsWithPrefix(String authorPrefix) throws AuthorNotFoundException;

    /**
     * Gets all documents of an author.
     * @param authorName Given author name to filter.
     * @return Collection of matching documents.
     */
    String getDocumentsByAuthorId(String authorName) throws DocumentNotFoundException;

    /**
     * Get a document that matches with a title and its author.
     * @param title  Given title.
     * @param author Given author.
     * @return Matching document
     */
    String getDocumentByTitleAndAuthor(String title, String author) throws DocumentNotFoundException;

    /**
     * Gets documents matching a boolean expression
     * @param booleanExpression Expression following a format to search.
     * @return Documents matching a boolean expression.
     */
    String getDocumentsByBooleanExpression(String booleanExpression) throws InvalidQueryException;

    /**
     * Search for k similar documents to a given key
     * @param query query to search
     * @param numberOfDocuments number of documents to search
     * @return sorted set of similar documents
     */
    String getDocumentsByQuery(String query, int numberOfDocuments, boolean isSuperMode)
            throws InvalidQueryException, DocumentNotFoundException;

    /**
     * Gets the k most similar document to a given document.
     * @param documentTitle Title of the document to compare.
     * @param authorName Name of the author of the document.
     * @param k Number of similar documents to look for.
     * @param isSuperMode Different query formula.
     * @return K most similar documents
     */
    String getDocumentsByRelevance(String documentTitle, String authorName, int k, boolean isSuperMode)
            throws DocumentNotFoundException;

    /**
     * Tries to log a user in the system.
     * @param email Email to try the login..
     * @param password Password to try the login.
     */
    String userLogin(String email, String password) throws UserNotFoundException, InvalidDetailsException;

    /**
     * Tries to register a new user in the system.
     * @param email Email to try the register.
     * @param userName Username to try the register.
     * @param password Password to try the register.
     * @param password2 Repeat password to try the register.
     */
    String userRegister(String email, String userName, String password, String password2)
            throws InvalidDetailsException, AlreadyExistingUserException;

    /**
     * Tries to update an user with new details.
     * @param newEmail    New email to set to the user.
     * @param newName     New username to set to the user.
     * @param newPassword New password to set to the user.
     */
    void userUpdate(String newEmail, String newName, String newPassword)
            throws InvalidDetailsException, UserNotFoundException, AlreadyExistingUserException;

    /**
     * Tries to delete an user from the system.
     */
    void userDelete() throws UserNotFoundException;

    /**
     * Gets documents from the current user.
     */
    String getCurrentUserDocuments();

    /**
     * Gets the favourite documents from the current user.
     */
    String getCurrentUserFavourites();

    /**
     * Stores a new document in the system.
     * @param documentJSON New document to store.
     */
    String storeNewDocument(String documentJSON) throws AlreadyExistingDocumentException, InvalidDetailsException;

    /**
     * Updates a document in persistence.
     * @param oldDocumentJSON the document to update
     * @param editedDocumentJSON the document updated
     */
    void updateDocument(String oldDocumentJSON, String editedDocumentJSON)
            throws InvalidDetailsException, AlreadyExistingDocumentException, DocumentNotFoundException;

    /**
     * Document to delete from the system.
     * @param title  Document to delete title.
     * @param author Document to delete author.
     */
    void deleteDocument(String title, String author);

    /**
     * Removes user session.
     */
    void userLogout();

    /**
     * Returns all the documents in the system.
     * @return DocumentSet with all the documents.
     */
    String searchForAllDocuments();

    /**
     * Imports a document to the data base.
     * @return The document imported
     * @throws ImportExportException when error importing.
     * @throws AlreadyExistingDocumentException when document already exists.
     * @throws InvalidDetailsException when some details are incorrect.
     * @throws DocumentNotFoundException when document does not exist.
     */
    String importDocument() throws ImportExportException, AlreadyExistingDocumentException,
            InvalidDetailsException, DocumentNotFoundException;

    /**
     * Exports a document from the data base.
     * @param documentJSON Address where the document will be exported.
     * @return True if successful, false if not.
     * @throws ImportExportException when error exporting.
     */
    boolean exportDocument(String documentJSON) throws ImportExportException;

    /**
     * Rates a document from the data base.
     * @param title Document title.
     * @param author Document author name.
     * @param rating New rating to set.
     * @return Updated mean rating value.
     * @throws DocumentNotFoundException When document does not exist.
     */
    float rateDocument(String title, String author, int rating) throws DocumentNotFoundException;

    /**
     * Get the rating of a document
     * @param title Title of the document
     * @param author Author of the document
     * @return Document's rating
     */
    int getMyRating(String title, String author);

    /**
     * Gets a set of recommended documents.
     * @param numDocs Number of documents wanted in the set
     * @return DocumentsSet of numDocs recommended documents
     */
    String getRecommendedDocs(int numDocs);

    /**
     * Returns numDocs random documents from all documents.
     * @param numDocs Number of documents to return.
     * @return DocumentsSet of random documents.
     */
    String getNewDiscoveries(int numDocs);

    /**
     * Changes current user's avatar for the one given.
     * @param avatar The new avatar.
     * @throws SQLException when DB error.
     */
    void changeUserAvatar(int avatar) throws SQLException;

    /**
     * Selects a new image.
     * @return Filename of the image
     */
    String selectImage();

    /**
     * Edits a content by using an external tool
     * @param content New content
     * @return Content modified
     */
    String editContentExternalTool(String content);

    /**
     * Does a search of the given title and author in google.
     * @param title Title that we want to search
     * @param author Author that we want to search
     */
    void searchInformation(String title, String author);

    /**
     * Does a search of the given title and author in amazon.
     * @param title Title that we want to search
     * @param author Author that we want to search
     */
    void searchOnAmazon(String title, String author);

    /**
     * Shares a document using email
     * @param title title of the docuemtn
     * @param author author
     * @param content content
     */
    void shareByEmail(String title, String author, String content);

    /**
     * Prints the document defined by the parameters.
     * @param title Title of the document
     * @param author Author of the document
     * @param content Content of the document
     */
    void printDocument(String title, String author, String content);

    /**
     * Says if a document is favourite or not.
     * @param title Document title.
     * @param author Document author name.
     * @return If document is favourited by current logged user.
     */
    boolean isDocumentFavourite(String title, String author);

    /**
     * Adds document to current logged user favourites.
     * @param title Document title.
     * @param author Document author name.
     * @throws DocumentNotFoundException When document does not exist.
     */
    void addFavourite(String title, String author) throws DocumentNotFoundException;

    /**
     * Removes document from current logged user favourites.
     * @param title Document title.
     * @param author Document author name.
     * @throws DocumentNotFoundException When document does not exist
     */
    void removeFavourite(String title, String author) throws DocumentNotFoundException;

}

