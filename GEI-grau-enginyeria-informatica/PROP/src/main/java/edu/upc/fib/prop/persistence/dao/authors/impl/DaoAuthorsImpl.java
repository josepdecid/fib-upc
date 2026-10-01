package edu.upc.fib.prop.persistence.dao.authors.impl;

import edu.upc.fib.prop.exceptions.AuthorNotFoundException;
import edu.upc.fib.prop.models.Author;
import edu.upc.fib.prop.models.AuthorsCollection;
import edu.upc.fib.prop.persistence.dao.authors.DaoAuthors;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DaoAuthorsImpl implements DaoAuthors {

    @Override
    public void createAuthor(Connection c, String author) throws SQLException {
        Statement statement = c.createStatement();
        String query = String.format("INSERT INTO authors VALUES ('%s');", author);
        statement.executeUpdate(query);
    }

    @Override
    public AuthorsCollection getAllAuthors(Connection c) {
        AuthorsCollection authorsCollection = new AuthorsCollection();
        try {
            Statement statement = c.createStatement();
            String query = "SELECT * FROM authors ORDER BY author_name ASC;";
            ResultSet rs = statement.executeQuery(query);
            while (rs.next()) {
                authorsCollection.addAuthor(new Author(rs.getString("author_name")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return authorsCollection;
    }

    @Override
    public Author getAuthorByName(Connection c, String author) throws AuthorNotFoundException {
        try {
            Statement statement = c.createStatement();
            String query = String.format("SELECT * FROM authors WHERE UPPER(author_name)='%s';", author.toUpperCase());
            ResultSet rs = statement.executeQuery(query);
            if (rs.next()) {
                return new Author(rs.getString("author_name"));
            } else {
                throw new AuthorNotFoundException();
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public boolean existsAuthor(Connection c, String author) {
        try {
            Statement statement = c.createStatement();
            String query = String.format("SELECT * FROM authors WHERE UPPER(author_name)='%s';", author.toUpperCase());
            ResultSet rs = statement.executeQuery(query);
            return rs.isBeforeFirst();
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    @Override
    public void deleteIfNoDocuments(Connection c, String author) {
        try {
            Statement statement = c.createStatement();
            String query = String.format("DELETE FROM authors WHERE author_name='%s' AND " +
                    "NOT EXISTS (SELECT * FROM documents WHERE documents.author_name = authors.author_name);", author);
            statement.executeUpdate(query);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
