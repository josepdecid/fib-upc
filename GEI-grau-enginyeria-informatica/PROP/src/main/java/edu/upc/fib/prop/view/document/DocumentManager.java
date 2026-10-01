package edu.upc.fib.prop.view.document;

import edu.upc.fib.prop.exceptions.DocumentNotFoundException;
import edu.upc.fib.prop.exceptions.InvalidDetailsException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentsCollection;
import edu.upc.fib.prop.utils.IOUtils;
import javafx.util.Pair;

public class DocumentManager {

    private DocumentsCollection documentsCollection;

    public DocumentManager(DocumentsCollection documentsCollection) {
        this.documentsCollection = documentsCollection;
    }

    public void setDocumentsCollection(DocumentsCollection documentsCollection) {
        this.documentsCollection = documentsCollection;
    }

    public void addDocumentToCollection(Document document) throws InvalidDetailsException{
        this.documentsCollection.addDocument(document);
    }

    public Document createDocument() {
        String title = IOUtils.askForString("Title");
        String author = IOUtils.askForString("Author");
        String content = IOUtils.askForString("Content");
        return new Document(title, author, content);
    }

    public void readDocument() {
        int size = showList();
        if (size > 0) {
            System.out.println();
            int documentSelected = IOUtils.askForInt("Document", 1, size) - 1;
            System.out.println();
            Document document = this.documentsCollection.getDocuments().get(documentSelected);
            System.out.println(document.getTitle().toUpperCase() + " | " + document.getAuthor());
            int space = document.getTitle().length()+document.getAuthor().length()+3;
            for (int i = 0; i < space; i++) {
                System.out.print("-");
            }
            System.out.println();
            System.out.println(document.getContent());
        } else {
            System.out.println("No documents found!");
        }
    }

    public Pair<Document, Document> updateDocument() throws DocumentNotFoundException {
        int numDocuments = showList();
        System.out.println();
        if (numDocuments == 0) {
            throw new DocumentNotFoundException();
        } else {
            int documentSelected = IOUtils.askForInt("Choose a document", 1, numDocuments);
            Document oldDocument = this.documentsCollection.getDocuments().get(documentSelected - 1);
            System.out.println();
            String newTitle = IOUtils.askForString("New title");
            String newAuthor = IOUtils.askForString("New author");
            String newContent = IOUtils.askForString("New content");
            System.out.println();
            Document newDocument = new Document(newTitle, newAuthor, newContent, oldDocument.getUser());
            return new Pair<>(oldDocument, newDocument);
        }
    }

    public Document deleteDocument() throws DocumentNotFoundException {
        int numDocuments = showList();
        if (numDocuments == 0) {
            throw new DocumentNotFoundException();
        } else {
            System.out.println();
            int documentSelected = IOUtils.askForInt("Choose a document", 1, numDocuments);
            System.out.println();
            return this.documentsCollection.getDocuments().get(documentSelected - 1);
        }
    }

    private int showList() {
        int i = 0;
        IOUtils.drawLine(70);
        System.out.printf( "    %-35s %-30s %n", "Title", "Author");
        IOUtils.drawLine(70);
        for (Document document : this.documentsCollection.getDocuments()) {
            System.out.printf("%-3d %-35s %-30s %n",++i,document.getTitle(),document.getAuthor());
        }
        return this.documentsCollection.getDocuments().size();
    }

}
