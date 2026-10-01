package edu.upc.fib.prop.persistence.controllers;

import edu.upc.fib.prop.exceptions.*;
import edu.upc.fib.prop.models.*;

import java.sql.SQLException;

public interface PersistenceController {

    /**
     * Gets all the authors from the data base.
     * @return Collection of all authors from the data base.
     */
    AuthorsCollection getAuthors();
    /**
     * Gets all the documents from the data base.
     * @return Collection of all documents from the data base.
     */
    DocumentsCollection getDocuments();

    /**
     * Modifies an existing document for a given one.
     * @param document Given document.
     */
    void writeNewDocument(Document document) throws AlreadyExistingDocumentException, SQLException;

    /**
     * Creates a given user in the data base.
     * @param user Given user.
     */
    void createUser(User user) throws AlreadyExistingUserException;

    /**
     * Checks the validity of a user in the data base.
     * @param email Given email.
     * @param password Given password.
     * @return The user with the given email and password.
     */
    User loginUser(String email, String password) throws UserNotFoundException, InvalidDetailsException;

    /**
     * Overwrites a user in the data base for another one.
     * @param currentUser User that is doing the modification.
     * @param newUser The modification of the user.
     */
    void updateUser(User currentUser, User newUser) throws UserNotFoundException, AlreadyExistingUserException;

    /**
     * Deletes a given user from the data base.
     * @param user Given user.
     */
    void deleteUser(User user) throws UserNotFoundException;

    /**
     * Deletes a given document from the data base.
     * @param document Given document.
     */
    void deleteDocument(Document document);

    /**
     * Overwrites a document in the data base for another one.
     * @param oldDocument Modified document.
     * @param newDocument Modifying document.
     */
    void updateDocument(Document oldDocument, Document newDocument) throws AlreadyExistingDocumentException;

    float rateDocument(Document document, int rating, String user) throws DocumentNotFoundException;

    /**
     *  Adds a document as a favourite of a given user
     * @param title Title of the document to add as a
     * @param author Author of the document to add as a favourite
     * @param user User that added the document as a favourite
     */
    void addDocumentToFavourites(String title, String author, String user) throws DocumentNotFoundException;

    /**
     * Removes a document from an user's favourite documents list
     * @param title Title of the document that will be removed from favourites list
     * @param author Author of the document that will be removed from favourites list
     * @param user User that deleted the document as a favourite
     */
    void deleteDocumentFromFavourites(String title, String author, String user) throws DocumentNotFoundException;

    /**
     * Removes all favourites from all users of a given document
     * @param document The favourites related to this document will be deleted
     */
    void deleteAllFavouritesOfDocument(Document document);

    /**
     * Removes all ratings from all users of a given document
     * @param document The ratings related to this document will be deleted
     */
    void deleteAllRatingsOfDocument(Document document);

    /**
     * It returns, if exists, the document with a given title and author.
     * @param title Title of the document
     * @param author Author of the document
     * @return Document with this title and author
     */
    Document getDocument(String title, String author) throws DocumentNotFoundException;

    /**
     * Gets the list of favourite documents of the user given
     * @param user The email of the user
     * @return DocumentsCollection of the favourite documents of the user
     */
    DocumentsCollection getFavouriteDocuments(String user);

    /**
     * Returns true if the document with the given title and authors is marked as a favourite by the user with the given email
     * @param title Title of the document
     * @param author Author of the document
     * @param email Email of the user
     * @return true if the document is marked as favourite, false if not
     */
    boolean isDocumentFavourite(String title, String author, String email);

    /**
     * Gets the rating that a user has given to a document, given its title and author
     * @param title Title of the document
     * @param author Author of the document
     * @param email Email of the user
     * @return The rating that the user has given to this document
     */
    int getMyRating(String title, String author, String email);

    /**
     * Changes the users' avatar for the one given
     * @param email Email of the user
     * @param avatar New avatar
     */
    void changeUserAvatar(String email, int avatar);

    /**
     * Gets the list of numDocs recommended documents of a user
     * @param numDocs Number of documents in the list
     * @param email Email of the user
     * @return returns the list of recommended documents of this user
     */
    DocumentsSet getRecommendedDocuments(int numDocs, String email);
}
