package edu.upc.fib.prop.persistence.dao.authors;

import edu.upc.fib.prop.exceptions.AuthorNotFoundException;
import edu.upc.fib.prop.models.Author;
import edu.upc.fib.prop.models.AuthorsCollection;

import java.sql.Connection;
import java.sql.SQLException;

/**
 * Data Access Object for authors in persistence.
 */
public interface DaoAuthors {

    /**
     * Creates an author in persistence.
     * @param c DB connection.
     * @param author Author to store in the DB.
     * @throws SQLException when SQLiteDB related error.
     */
    void createAuthor(Connection c, String author) throws SQLException;

    /**
     * Gets all authors stored in persistence.
     * @return Set of all authors.
     */
    AuthorsCollection getAllAuthors(Connection c);

    /**
     * Gets an author by name from persistence.
     * @param c DB connection.
     * @param author Author to search for.
     * @return Author that matches desired author.
     * @throws AuthorNotFoundException when author doesn't match any DB entry.
     */
    Author getAuthorByName(Connection c, String author) throws AuthorNotFoundException;

    /**
     * Check if an author exists in the database.
     * @param c DB Connection.
     * @param author Author name.
     * @return  true if exists, false otherwise.
     */
    boolean existsAuthor(Connection c, String author);

    /**
     * If there is no documents in the database from the author, it is deleted.
     * @param author author name.
     */
    void deleteIfNoDocuments(Connection c, String author);
}
