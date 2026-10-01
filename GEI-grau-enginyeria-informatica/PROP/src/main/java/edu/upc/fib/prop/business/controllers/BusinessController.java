package edu.upc.fib.prop.business.controllers;

import edu.upc.fib.prop.exceptions.*;
import edu.upc.fib.prop.models.*;
import javafx.stage.Stage;

import java.sql.SQLException;

public interface BusinessController {

    /*--------------- Users */

    /**
     * Check if input details match with a user.
     *  @param email    Account email.
     * @param password Account password.
     */
    User checkLoginDetails(String email, String password) throws InvalidDetailsException, UserNotFoundException;

    /**
     * Check if input details can be used to create a new user.
     *
     * @param email     New account email.
     * @param userName  New username.
     * @param password  New password.
     * @param password2 New password repeated.
     */
    User registerNewUser(String email, String userName, String password, String password2)
            throws InvalidDetailsException, AlreadyExistingUserException;

    /**
     * Check if input details can be used to update an existing user.
     *
     * @param newEmail    Account new email.
     * @param newName     Account new name.
     * @param newPassword Account new password.
     */
    void updateUser(String newEmail, String newName, String newPassword)
            throws InvalidDetailsException, UserNotFoundException, AlreadyExistingUserException;

    /**
     * Deletes current user from the system.
     */
    void deleteUser() throws UserNotFoundException;

    /**
     * Deletes active user session.
     */
    void logout();

    /*--------------- Authors */

    /**
     * Search for matching authors with a given prefix.
     *
     * @param authorPrefix User input to search.
     * @return Collection of matching authors (even if empty).
     */
    AuthorsCollection searchMatchingAuthors(String authorPrefix) throws AuthorNotFoundException;

    /*--------------- Documents */

    /**
     * Search for documents written by an author.
     *
     * @param authorName Author name identifier.
     * @return Collection of matching documents (even if empty).
     */
    DocumentsCollection searchDocumentsByAuthor(String authorName) throws DocumentNotFoundException;

    /**
     * Search for documents given a title and an author.
     *
     * @param title      Document title identifier.
     * @param authorName Document author identifier.
     * @return Document matching title and author.
     */
    Document searchDocumentsByTitleAndAuthor(String title, String authorName) throws DocumentNotFoundException;

    /**
     * Returns all the documents stored in the system
     *
     * @return All documents in the system.
     */
    DocumentsSet searchForAllDocuments();

    /**
     * Sorts a k size document set by relevance given a document.
     *
     * @param document reference document
     * @param k        number of documents to find
     * @return sorted set of similar documents
     */
    SortedDocumentsSet searchDocumentsByRelevance(Document document, int k, boolean isSuperMode)
            throws DocumentNotFoundException;

    /**
     * Gets current session logged user documents.
     *
     * @return Documents owned by current user.
     */
    DocumentsCollection getCurrentUserDocuments();

    /**
     * Gets current session logged user favourite documents.
     * @return Favourite documents of the current user.
     */
    DocumentsCollection getCurrentUserFavourites();

    /**
     * Stores in persistence a new document.
     *
     * @param document Document to store.
     */
    void storeNewDocument(Document document)
            throws AlreadyExistingDocumentException, InvalidDetailsException;

    void shareByEmail(String title, String author, String content);

    /**
     * Updates a document in persistence.
     *
     * @param title title of the document to update
     * @param author author of the document to update
     * @param newDoc New document
     */
    void updateDocument(String title, String author, Document newDoc)
            throws InvalidDetailsException, AlreadyExistingDocumentException, DocumentNotFoundException;

    /**
     * Deletes a document in persistence.
     *
     * @param title Document to delete title.
     * @param authorName Document to delete author.
     */
    void deleteDocument(String title, String authorName) throws DocumentNotFoundException;

    /**
     * Imports a document to the data base given a Stage.
     *
     * @param st Stage where the document is found
     * @return The document imported
     */
    Document importDocument(Stage st)
            throws ImportExportException, AlreadyExistingDocumentException, InvalidDetailsException, DocumentNotFoundException;

    /**
     * Exports a document from the data base.
     *
     * @param st Stage where the document will be exported
     * @param document Document to be exported
     * @return True if successful, false if not
     */
    boolean exportDocument(Stage st, Document document) throws ImportExportException;

    /**
     * Search for matching documents by a boolean expression.
     *
     * @param booleanExpression Expression to search by.
     * @return A set of matching documents.
     */
    DocumentsSet searchDocumentsByBooleanExpression(String booleanExpression) throws InvalidQueryException;

    /**
     * Search for k similar documents to a given key
     *
     * @param str query to search
     * @param k   number of documents to search
     * @return sorted set of similar documents
     */
    SortedDocumentsSet searchDocumentsByQuery(String str, int k, boolean isSuperMode)
            throws DocumentNotFoundException;

    /**
     * Gives a document a certain rating.
     *
     * @param title Title of the document
     * @param author Author of the document
     * @param rating Our rating
     * @return The average rating of the document
     */
    float rateDocument(String title, String author, int rating) throws DocumentNotFoundException;

    /**
     * Deletes a document form the current user favourites list.
     *
     * @param title Title of the document
     * @param author Author of the document
     */
    void deleteDocumentFromFavourites(String title, String author) throws DocumentNotFoundException;

    /**
     * Adds the document given to the current user favourites list.
     *
     * @param title Title of the document
     * @param author Author of the document
     */
    void addDocumentToFavourites(String title, String author) throws DocumentNotFoundException;

    /**
     * Returns true if the document with the given title and author is marked as a favourite by the logged user
     *
     * @param title title of the document
     * @param author author of the document
     * @return true if favourite, false if not
     */
    boolean isDocumentFavourite(String title, String author);

    /**
     * Get the rating of a document
     *
     * @param title Title of the document
     * @param author Author of the document
     * @return Document's rating
     */
    int getMyRating(String title, String author);

    /**
     * Changes current user's avatar for the one given.
     *
     * @param avatar The new avatar
     */
    void changeUserAvatar(int avatar) throws SQLException;

    /**
     * Selects an image from a new stage
     *
     * @param st New stage
     * @return Filename of the image
     */
    String selectImage(Stage st);

    /**
     * Edits a content by using an external tool
     *
     * @param content New content
     * @return Content modified
     */
    String editContentExternalTool(String content);

    /**
     * Does a search of the given title and author in google.
     *
     * @param title Title that we want to search
     * @param author Authro that we want to search
     */
    void searchInformation(String title, String author);

    /**
     * Prints the document defined by the parameters.
     *
     * @param title Title of the document
     * @param author Author of the document
     * @param content Content of the document
     */
    void printDocument(String title, String author, String content);

    /**
     * Gets a set of recommended documents.
     *
     * @param numDocs Number of documents wanted in the set
     * @return DocumentsSet of numDocs recommended documents
     */
    DocumentsSet getRecommendedDocuments(int numDocs);

    /**
     * Returns numDocs random documents from all documents.
     *
     * @param numDocs Number of documents to retunr
     * @return DocumentsSet of random documents
     */
    DocumentsSet getNewDiscoveries(int numDocs);

    /**
     * Searches a document on Amazon
     * @param title
     * @param author
     */
    void searchOnAmazon(String title, String author);
}