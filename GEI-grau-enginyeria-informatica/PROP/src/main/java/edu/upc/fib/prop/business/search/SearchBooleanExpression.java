package edu.upc.fib.prop.business.search;

import edu.upc.fib.prop.exceptions.InvalidQueryException;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.models.DocumentsSet;


public interface SearchBooleanExpression {

    /**
     * Checks for an expression valid format.
     * @param booleanExpression boolean expression to check its correctness.
     */
    boolean checkValidBooleanExpression(String booleanExpression);

    /**
     * Search for matching authors given boolean expression.
     * @param booleanExpression boolean expression to search by.
     * @return Set of matching documents.
     * @throws InvalidQueryException when the query has a wrong format.
     */
    DocumentsSet searchDocumentsByBooleanExpression(String booleanExpression, DocumentsCollection allDocuments)
        throws InvalidQueryException;
}
