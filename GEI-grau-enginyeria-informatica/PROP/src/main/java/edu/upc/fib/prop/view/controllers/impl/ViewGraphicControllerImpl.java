package edu.upc.fib.prop.view.controllers.impl;

import com.google.gson.Gson;
import edu.upc.fib.prop.business.controllers.BusinessController;
import edu.upc.fib.prop.business.controllers.impl.BusinessControllerImpl;
import edu.upc.fib.prop.exceptions.*;
import edu.upc.fib.prop.models.*;
import edu.upc.fib.prop.utils.StringUtils;
import edu.upc.fib.prop.view.controllers.ViewGraphicController;
import javafx.stage.Stage;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ViewGraphicControllerImpl implements ViewGraphicController {

    private BusinessController businessController;
    private Stage stage;

    public ViewGraphicControllerImpl(Stage stage) {
        System.out.println("Initializing view controller (GRAPHICAL MODE)");
        businessController = new BusinessControllerImpl();
        this.stage = stage;
    }

    @Override
    public String getAuthorsWithPrefix(String authorPrefix) throws AuthorNotFoundException {
        AuthorsCollection authorsCollection = this.businessController.searchMatchingAuthors(authorPrefix);
        return new Gson().toJson(authorsCollection);
    }

    @Override
    public String getDocumentsByAuthorId(String authorName) throws DocumentNotFoundException {
        DocumentsCollection documentsCollection = this.businessController.searchDocumentsByAuthor(authorName);
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Document document : documentsCollection.getAllDocuments()) {
            documentsBasicInfo.add(new DocumentBasicInfo(document));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String getDocumentByTitleAndAuthor(String title, String author) throws DocumentNotFoundException {
        Document document = this.businessController.searchDocumentsByTitleAndAuthor(title, author);
        DocumentBasicInfo documentBasicInfo = new DocumentBasicInfo(document);
        return new Gson().toJson(documentBasicInfo);
    }

    @Override
    public String getDocumentsByBooleanExpression(String booleanExpression) throws InvalidQueryException {
        DocumentsSet documentSet = businessController.searchDocumentsByBooleanExpression(booleanExpression);
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Document document : documentSet) {
            documentsBasicInfo.add(new DocumentBasicInfo(document));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String getDocumentsByQuery(String query, int numberOfDocuments, boolean isSuperMode)
            throws InvalidQueryException, DocumentNotFoundException {
        SortedDocumentsSet dss = this.businessController.searchDocumentsByQuery(query, numberOfDocuments, isSuperMode);
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Map.Entry<Double, List<Document>> documents : dss.getDocs().entrySet()) {
            documentsBasicInfo.addAll(documents.getValue().stream().map(document ->
                    new DocumentBasicInfo(document, documents.getKey())).collect(Collectors.toList()));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String getDocumentsByRelevance(String documentTitle, String authorName, int k, boolean isSuperMode)
            throws DocumentNotFoundException {
        Document originalDocument = businessController.searchDocumentsByTitleAndAuthor(documentTitle, authorName);
        SortedDocumentsSet sortedDocumentsSet = this.businessController.searchDocumentsByRelevance(originalDocument, k, isSuperMode);
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Map.Entry<Double, List<Document>> documents : sortedDocumentsSet.getDocs().entrySet()) {
            documentsBasicInfo.addAll(documents.getValue().stream().map(document ->
                    new DocumentBasicInfo(document, documents.getKey())).collect(Collectors.toList()));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String userLogin(String email, String password) throws UserNotFoundException, InvalidDetailsException {
        User user = businessController.checkLoginDetails(email, password);
        return new Gson().toJson(user);
    }

    @Override
    public String userRegister(String email, String userName, String password, String password2)
            throws InvalidDetailsException, AlreadyExistingUserException {
        User user = businessController.registerNewUser(email, userName, password, password2);
        return new Gson().toJson(user);
    }

    @Override
    public void userUpdate(String newEmail, String newName, String newPassword) throws InvalidDetailsException, UserNotFoundException, AlreadyExistingUserException {

    }

    @Override
    public void userDelete() throws UserNotFoundException {
        businessController.deleteUser();
    }

    @Override
    public String getCurrentUserDocuments() {
        DocumentsCollection documents = this.businessController.getCurrentUserDocuments();
        List<DocumentBasicInfo> documentsBasicInfo = documents.getDocuments().stream().map(DocumentBasicInfo::new)
                .collect(Collectors.toList());
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String getCurrentUserFavourites() {
        DocumentsCollection documents = this.businessController.getCurrentUserFavourites();
        List<DocumentBasicInfo> documentsBasicInfo = documents.getDocuments().stream().map(DocumentBasicInfo::new)
                .collect(Collectors.toList());
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String storeNewDocument(String documentJSON)
            throws AlreadyExistingDocumentException, InvalidDetailsException {
        Document document = StringUtils.parseJSONToDocument(documentJSON);
        this.businessController.storeNewDocument(document);
        return new Gson().toJson( new DocumentBasicInfo(document));
    }

    @Override
    public void updateDocument(String oldDocumentJSON, String editedDocumentJSON)
            throws InvalidDetailsException, AlreadyExistingDocumentException, DocumentNotFoundException {
        Document oldDocument = StringUtils.parseJSONToDocument(oldDocumentJSON);
        Document editedDocument = StringUtils.parseJSONToDocument(editedDocumentJSON);
        businessController.updateDocument(oldDocument.getTitle(), oldDocument.getAuthor(), editedDocument);
    }

    @Override
    public void deleteDocument(String title, String authorName) {
        try {
            this.businessController.deleteDocument(title, authorName);
        } catch (DocumentNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void userLogout() {
        businessController.logout();
    }

    @Override
    public String searchForAllDocuments() {
        DocumentsSet documents = this.businessController.searchForAllDocuments();
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Document document : documents) {
            documentsBasicInfo.add(new DocumentBasicInfo(document));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String importDocument()
            throws ImportExportException, AlreadyExistingDocumentException, InvalidDetailsException, DocumentNotFoundException {
        Document doc = this.businessController.importDocument(stage);
        DocumentBasicInfo documentBasicInfo = new DocumentBasicInfo(doc);
        return new Gson().toJson(documentBasicInfo);
    }

    @Override
    public boolean exportDocument(String documentJSON) throws ImportExportException {
        Document document = StringUtils.parseJSONToDocument(documentJSON);
        return this.businessController.exportDocument(stage, document);
    }

    @Override
    public float rateDocument(String title, String author, int rating) throws DocumentNotFoundException {
        return this.businessController.rateDocument(title, author, rating);
    }

    @Override
    public boolean isDocumentFavourite(String title, String author){
        return this.businessController.isDocumentFavourite(title, author);
    }

    @Override
    public void addFavourite(String title, String author) throws DocumentNotFoundException {
        this.businessController.addDocumentToFavourites(title, author);
    }

    @Override
    public void removeFavourite(String title, String author) throws DocumentNotFoundException {
        this.businessController.deleteDocumentFromFavourites(title, author);
    }

    @Override
    public int getMyRating(String title, String author){
        return businessController.getMyRating(title,author);
    }

    @Override
    public String getRecommendedDocs(int numDocs) {
        DocumentsSet documents = this.businessController.getRecommendedDocuments(numDocs);
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Document document : documents) {
            documentsBasicInfo.add(new DocumentBasicInfo(document));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public String getNewDiscoveries(int numDocs) {
        DocumentsSet documents = this.businessController.getNewDiscoveries(numDocs);
        List<DocumentBasicInfo> documentsBasicInfo = new ArrayList<>();
        for (Document document : documents) {
            documentsBasicInfo.add(new DocumentBasicInfo(document));
        }
        return new Gson().toJson(documentsBasicInfo);
    }

    @Override
    public void changeUserAvatar(int avatar) throws SQLException {
        this.businessController.changeUserAvatar(avatar);
    }

    @Override
    public String selectImage() {
        return businessController.selectImage(stage);
    }

    @Override
    public String editContentExternalTool(String content) {
        return this.businessController.editContentExternalTool(content);
    }

    @Override
    public void searchInformation(String title, String author) {
        this.businessController.searchInformation(title, author);
    }

    @Override
    public void searchOnAmazon(String title, String author) {
        this.businessController.searchOnAmazon(title, author);
    }

    @Override
    public void shareByEmail(String title, String author, String content) {
        this.businessController.shareByEmail(title, author, content);
    }

    @Override
    public void printDocument(String title, String author, String content) {
        this.businessController.printDocument(title, author, content);
    }
}
