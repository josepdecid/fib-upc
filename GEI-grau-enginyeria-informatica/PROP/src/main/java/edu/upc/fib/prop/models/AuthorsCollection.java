package edu.upc.fib.prop.models;

import java.util.ArrayList;
import java.util.List;

public class AuthorsCollection {

    private List<Author> authors;

    public AuthorsCollection() {
        this.authors = new ArrayList<>();
    }

    public List<Author> getAuthors() {
        return authors;
    }

    public void addAuthor(Author author) {
        this.authors.add(author);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AuthorsCollection that = (AuthorsCollection) o;
        return authors != null ? authors.equals(that.authors) : that.authors == null;

    }

}
