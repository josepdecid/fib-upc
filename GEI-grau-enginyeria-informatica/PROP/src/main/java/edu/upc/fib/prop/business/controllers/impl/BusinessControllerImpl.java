package edu.upc.fib.prop.business.controllers.impl;

import edu.upc.fib.prop.business.controllers.BusinessController;
import edu.upc.fib.prop.business.search.SearchBooleanExpression;
import edu.upc.fib.prop.business.search.impl.SearchAuthorImpl;
import edu.upc.fib.prop.business.search.impl.SearchBooleanExpressionImpl;
import edu.upc.fib.prop.business.search.impl.SearchDocumentImpl;
import edu.upc.fib.prop.business.users.UsersManager;
import edu.upc.fib.prop.business.users.impl.UsersManagerImpl;
import edu.upc.fib.prop.exceptions.*;
import edu.upc.fib.prop.models.*;
import edu.upc.fib.prop.persistence.controllers.PersistenceController;
import edu.upc.fib.prop.persistence.controllers.impl.PersistenceControllerImpl;
import edu.upc.fib.prop.utils.ImportExport;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.math.BigInteger;
import java.net.URI;
import java.security.SecureRandom;
import java.sql.SQLException;
import java.util.Random;
import java.util.Scanner;

public class BusinessControllerImpl implements BusinessController {

    private PersistenceController persistenceController;

    private SearchAuthorImpl searchAuthor;
    private SearchDocumentImpl searchDocument;
    private SearchBooleanExpression searchBooleanExpression;

    private AuthorsCollection authorsCollection;
    private DocumentsCollection documentsCollection;

    private UsersManager usersManager;

    public BusinessControllerImpl() {
        System.out.println("Initializing business controller");

        this.persistenceController = new PersistenceControllerImpl();
        this.searchAuthor = new SearchAuthorImpl();
        this.searchDocument = new SearchDocumentImpl();
        this.searchBooleanExpression = new SearchBooleanExpressionImpl();

        // Load in memory all authors and documents on instantiate
        this.authorsCollection = this.persistenceController.getAuthors();
        this.documentsCollection = this.persistenceController.getDocuments();

        this.usersManager = new UsersManagerImpl();
    }

    /*--------------- Users */


    @Override
    public User checkLoginDetails(String email, String password)
            throws InvalidDetailsException, UserNotFoundException {
        password = usersManager.login(email, password);
        User user = persistenceController.loginUser(email, password);
        usersManager.setCurrentUser(user);
        return user;
    }

    @Override
    public User registerNewUser(String email, String userName, String password, String password2)
            throws InvalidDetailsException, AlreadyExistingUserException {
        User user = usersManager.register(email, userName, password, password2);
        persistenceController.createUser(user);
        usersManager.setCurrentUser(user);
        return user;
    }

    @Override
    public void updateUser(String newEmail, String newName, String newPassword)
            throws InvalidDetailsException, UserNotFoundException, AlreadyExistingUserException {
        User user = usersManager.register(newEmail, newName, newPassword, newPassword);
        persistenceController.updateUser(usersManager.getCurrentUser(), user);
        usersManager.setCurrentUser(user);
    }

    @Override
    public void deleteUser() throws UserNotFoundException {
        User user = usersManager.getCurrentUser();
        DocumentsSet docs = searchDocument.filterByUser(this.documentsCollection, user.getEmail()).getAllDocuments();
        for(Document d : docs){
            persistenceController.deleteAllFavouritesOfDocument(d);
            persistenceController.deleteAllRatingsOfDocument(d);
            persistenceController.deleteDocument(d);
        }
        persistenceController.deleteUser(user);
        usersManager.logout();
    }

    @Override
    public void logout() {
        usersManager.logout();
    }

    /*--------------- Documents */

    @Override
    public DocumentsSet searchForAllDocuments() {
        return this.documentsCollection.getAllDocuments();
    }

    @Override
    public Document importDocument(Stage st)
            throws ImportExportException, AlreadyExistingDocumentException, InvalidDetailsException, DocumentNotFoundException {
        Document doc = ImportExport.importDocument(st);
        this.storeNewDocument(doc);
        return doc;
    }

    @Override
    public boolean exportDocument(Stage st, Document document) throws ImportExportException {
        return ImportExport.exportDocument(st, document);
    }

    @Override
    public SortedDocumentsSet searchDocumentsByRelevance(Document document, int k, boolean isSuperMode)
            throws DocumentNotFoundException {
        return this.searchDocument.searchForSimilarDocuments(this.documentsCollection, document, k, isSuperMode);
    }

    @Override
    public SortedDocumentsSet searchDocumentsByQuery(String str, int k, boolean isSuperMode) {
        Document document = new Document("", "", str);
        document.updateFrequencies();
        return this.searchDocument.searchForSimilarDocuments(this.documentsCollection, document, k, isSuperMode);
    }

    @Override
    public float rateDocument(String title, String author, int rating) throws DocumentNotFoundException {

        try {
            Document document = persistenceController.getDocument(title, author);
            float newRating = persistenceController.rateDocument(document, rating, this.usersManager.getCurrentUser().getEmail());
            Document updatedDoc = persistenceController.getDocument(document.getTitle(), document.getAuthor());
            documentsCollection.updateDocument(document, updatedDoc);
            return newRating;
        } catch (InvalidDetailsException | AlreadyExistingDocumentException e) {
            e.printStackTrace();
        }
        return 0f;
    }

    @Override
    public void addDocumentToFavourites(String title, String author) throws DocumentNotFoundException {
        persistenceController.addDocumentToFavourites(title, author, this.usersManager.getCurrentUser().getEmail());
    }

    @Override
    public void deleteDocumentFromFavourites(String title, String author) throws DocumentNotFoundException {
        persistenceController.deleteDocumentFromFavourites(title, author, this.usersManager.getCurrentUser().getEmail());
    }

    @Override
    public boolean isDocumentFavourite(String title, String author) {
        return persistenceController.isDocumentFavourite(title, author, usersManager.getCurrentUser().getEmail());
    }

    @Override
    public int getMyRating(String title, String author) {
        return persistenceController.getMyRating(title,author,usersManager.getCurrentUser().getEmail());
    }

    @Override
    public void changeUserAvatar(int avatar) {
        this.persistenceController.changeUserAvatar(usersManager.getCurrentUser().getEmail(), avatar);
    }



    @Override
    public String selectImage(Stage st) {

        FileChooser fc = new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter
                ("Image Files", "*.png", "*.jpg", "*.gif"));
        fc.setTitle("Load image");
        File file = fc.showOpenDialog(st);
        BufferedImage bufferedImage = null;
        try {
            bufferedImage = ImageIO.read(file);
        } catch (IOException e) {
            e.printStackTrace();
        }

        SecureRandom random = new SecureRandom();
        String filename = new BigInteger(130, random).toString(32);

        try {
            if(file.getName().contains(".png")){
                filename = filename.concat(".png");
                assert bufferedImage != null;
                ImageIO.write(bufferedImage, "png", new File("./covers/" + filename));
            }
            else if(file.getName().contains(".jpg")){
                filename = filename.concat(".jpg");
                assert bufferedImage != null;
                ImageIO.write(bufferedImage, "jpg", new File("./covers/" + filename));
            }
            else if(file.getName().contains(".gif")){
                filename = filename.concat(".gif");
                assert bufferedImage != null;
                ImageIO.write(bufferedImage, "gif", new File("./covers/" + filename));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        return filename;
    }

    @Override
    public String editContentExternalTool(String content) {
        try {
            File file=File.createTempFile("temp", ".txt");
            file.deleteOnExit();
            FileWriter fw = new FileWriter(file);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(content);
            bw.close();

            Desktop d = java.awt.Desktop.getDesktop();
            if(d.isSupported(Desktop.Action.EDIT)){
                d.edit(file);
            }
            System.err.println("seguimos ejecucion");
            Scanner reader = new Scanner(file);
            String newContent = "";

            while (reader.hasNextLine()){
                String line = reader.nextLine();
                if(line.isEmpty()) newContent += "\n\n";
                else newContent += line;
            }
            System.err.println(newContent);
            return newContent;
        } catch (IOException e) {
            e.printStackTrace();
            return content;
        }
    }

    @Override
    public void searchInformation(String title, String author) {
        Desktop d = java.awt.Desktop.getDesktop();
        String url = "https://www.google.es/#q=" + title + " " + author;
        url = url.replace(' ', '+');

        if(d.isSupported(Desktop.Action.BROWSE)){
            try {
                d.browse(URI.create(url));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void searchOnAmazon(String title, String author) {
        Desktop d = java.awt.Desktop.getDesktop();
        String url = "https://www.amazon.es/s/ref=nb_sb_noss?__mk_es_ES=%C3%85M%C3%85%C5%BD%C3%95%C3%91&url=search-alias%3Dstripbooks&field-keywords=" + title + " " + author;
        url = url.replace(' ', '+');

        if(d.isSupported(Desktop.Action.BROWSE)){
            try {
                d.browse(URI.create(url));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void shareByEmail(String title, String author, String content) {
        Desktop d = java.awt.Desktop.getDesktop();
        String subject = "Hey, look at this book!";
        String br = "%0D%0A";
        String body = title + br + author + br + br + content.substring(0,500) + "...";
        body += br + br + "You can find it on Amazon" + br;
        //body += br + "https://www.amazon.es/s/ref=nb_sb_noss?__mk_es_ES=%C3%85M%C3%85%C5%BD%C3%95%C3%91&url=search-alias%3Dstripbooks&field-keywords=" + title + " " + author +br;
        String to = "";
        String uriStr = String.format("mailto:%s?subject=%s&body=%s", to, subject, body);
        uriStr = uriStr.replace(" ", "%20");

        if(d.isSupported(Desktop.Action.MAIL)){
            try {
                d.mail(URI.create(uriStr));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }



    @Override
    public void updateDocument(String title, String author, Document newDoc)
            throws AlreadyExistingDocumentException, InvalidDetailsException, DocumentNotFoundException {

        Document oldDoc = searchDocumentsByTitleAndAuthor(title, author);
        if (!(newDoc.getAuthor().equals("") && newDoc.getTitle().equals("") && newDoc.getContent().equals(""))) {
            if (!(oldDoc.getAuthor().toLowerCase().equals(newDoc.getAuthor().toLowerCase()) &&
                    oldDoc.getAuthor().toLowerCase().equals(newDoc.getAuthor().toLowerCase()))) {
                if (documentsCollection.containsTitleAndAuthor(newDoc.getTitle(), newDoc.getAuthor())) {
                    throw new AlreadyExistingDocumentException();
                }
            }
            if (!oldDoc.getTitle().equals(newDoc.getTitle()) || !oldDoc.getAuthor().equals(newDoc.getAuthor())) {
                persistenceController.deleteAllFavouritesOfDocument(oldDoc);
                persistenceController.deleteAllRatingsOfDocument(oldDoc);
                newDoc.setRating(0f);
            }
            Document updatedDoc = documentsCollection.updateDocument(oldDoc, newDoc);
            persistenceController.updateDocument(oldDoc, updatedDoc);

            reloadDBData();
        }
    }

    @Override
    public DocumentsSet searchDocumentsByBooleanExpression(String booleanExpression) throws InvalidQueryException {
        return searchBooleanExpression.searchDocumentsByBooleanExpression(booleanExpression, documentsCollection);
    }

    /*--------------- Authors */

    @Override
    public AuthorsCollection searchMatchingAuthors(String authorPrefix) throws AuthorNotFoundException {
        return this.searchAuthor.filterByPrefix(this.authorsCollection, authorPrefix);
    }

    @Override
    public DocumentsCollection searchDocumentsByAuthor(String authorName) throws DocumentNotFoundException {
        return this.searchDocument.filterByAuthor(this.documentsCollection, authorName);
    }

    @Override
    public Document searchDocumentsByTitleAndAuthor(String title, String authorName)
            throws DocumentNotFoundException {
        return this.searchDocument.filterByTitleAndAuthor(this.documentsCollection, title, authorName);
    }

    @Override
    public DocumentsCollection getCurrentUserDocuments() {
        String user = this.usersManager.getCurrentUser().getEmail();
        return this.searchDocument.filterByUser(this.documentsCollection, user);
    }

    @Override
    public DocumentsCollection getCurrentUserFavourites() {
        String user = this.usersManager.getCurrentUser().getEmail();
        return this.persistenceController.getFavouriteDocuments(user);
    }

    @Override
    public void storeNewDocument(Document document) throws AlreadyExistingDocumentException, InvalidDetailsException {
        document.setUser(usersManager.getCurrentUser().getEmail());
        if (!document.isCorrect()) {
            throw new InvalidDetailsException();
        } else if (documentsCollection.containsTitleAndAuthor(document.getTitle(), document.getAuthor())) {
            throw new AlreadyExistingDocumentException();
        } else {
            document.updateFrequencies();
            document.updatePositions();
            try {
                documentsCollection.addDocument(document);
                persistenceController.writeNewDocument(document);
                reloadDBData();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void deleteDocument(String title, String authorName) throws DocumentNotFoundException {
        Document document = searchDocumentsByTitleAndAuthor(title, authorName);
        documentsCollection.deleteDocument(document);
        persistenceController.deleteDocument(document);
        persistenceController.deleteAllFavouritesOfDocument(document);
        persistenceController.deleteAllRatingsOfDocument(document);

        File cover = new File("./covers/" + document.getCover());
        if(cover!=null){
            cover.delete();
        }

        reloadDBData();
    }

    public void printDocument(String title, String author, String content){
        Desktop d = java.awt.Desktop.getDesktop();
        if(d.isSupported(Desktop.Action.PRINT)){
            try {

                File file = File.createTempFile(title.replace(" ", ""), ".txt");
                FileWriter fw = new FileWriter(file);
                BufferedWriter bw = new BufferedWriter(fw);
                bw.newLine();
                bw.newLine();
                bw.write(title);
                bw.newLine();
                bw.write(author);
                bw.newLine();
                bw.newLine();
                bw.write(content);
                bw.close();
                d.print(file);
                file.deleteOnExit();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public DocumentsSet getRecommendedDocuments(int numDocs) {
        return this.persistenceController.getRecommendedDocuments(numDocs, usersManager.getCurrentUser().getEmail());
    }

    @Override
    public DocumentsSet getNewDiscoveries(int numDocs) {
        DocumentsSet docs =  this.documentsCollection.getAllDocuments();
        DocumentsSet res =  new DocumentsSet();
        int added=0;
        Random randomGenerator = new Random();
        while(added<numDocs && docs.size()>0){
            int index = randomGenerator.nextInt(docs.size());
            Document d = docs.get(index);
            if(!d.getUser().equals(usersManager.getCurrentUser().getEmail()) &&
                    !persistenceController.isDocumentFavourite(d.getTitle(), d.getAuthor(), usersManager.getCurrentUser().getEmail())){
                res.add(d);
                added++;
            }
            docs.remove(d);
        }
        return res;
    }

    //////////

    // TODO: Improve performance
    private void reloadDBData() {
        authorsCollection = persistenceController.getAuthors();
        documentsCollection = persistenceController.getDocuments();
    }

}
