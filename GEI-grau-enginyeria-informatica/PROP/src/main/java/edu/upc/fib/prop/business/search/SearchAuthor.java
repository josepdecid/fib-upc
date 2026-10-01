package edu.upc.fib.prop.business.search;

import edu.upc.fib.prop.exceptions.AuthorNotFoundException;
import edu.upc.fib.prop.models.AuthorsCollection;

public interface SearchAuthor {

    /**
     * Search for matching authors given a prefix
     * @param authorsCollection Set of all authors.
     * @param authorPrefix Prefix to filter to.
     * @return Set of matching authors.
     */
    AuthorsCollection filterByPrefix(AuthorsCollection authorsCollection, String authorPrefix) throws AuthorNotFoundException;

}
