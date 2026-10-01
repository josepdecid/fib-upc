package edu.upc.fib.prop.business.search.impl;

import edu.upc.fib.prop.exceptions.AuthorNotFoundException;
import edu.upc.fib.prop.models.AuthorsCollection;
import edu.upc.fib.prop.business.search.SearchAuthor;

public class SearchAuthorImpl implements SearchAuthor {

    public AuthorsCollection filterByPrefix(AuthorsCollection authorsCollection, String authorPrefix)
            throws AuthorNotFoundException {
        AuthorsCollection filteredAuthors = new AuthorsCollection();
        authorsCollection.getAuthors().stream().filter(author ->
                author.getName().toLowerCase().matches("(?i)" + authorPrefix.toLowerCase() + ".*"))
                .forEach(filteredAuthors::addAuthor);
        if (filteredAuthors.getAuthors().isEmpty()) {
            throw new AuthorNotFoundException();
        }
        return filteredAuthors;
    }

}
