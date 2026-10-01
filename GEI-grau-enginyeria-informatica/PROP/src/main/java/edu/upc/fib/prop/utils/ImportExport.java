package edu.upc.fib.prop.utils;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.stream.JsonReader;
import edu.upc.fib.prop.exceptions.DocumentNotFoundException;
import edu.upc.fib.prop.exceptions.ImportExportException;
import edu.upc.fib.prop.models.Document;
import edu.upc.fib.prop.models.DocumentBasicInfo;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.*;
import java.util.Scanner;

public class ImportExport {

    private static class Document2Export {
        public String title,  author, content;
        public Document2Export(String _title, String _author, String _content){
            title=_title;
            author=_author;
            content=_content;
        }
        public String getTitle() {return title;}
        public String getAuthor() {return author;}
        public String getContent() {return content;}

    }

    public static Document importDocument(Stage st) throws ImportExportException, DocumentNotFoundException {
        try {
            Gson gson = new Gson();
            FileChooser fileChooser = new FileChooser();
            fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("JSON file", "*.json"));
            fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("Text file", "*.txt"));
            fileChooser.setTitle("Import document");
            File file = fileChooser.showOpenDialog(st);
            if (file != null) {
                if (file.getName().contains(".json")) {
                    JsonReader reader = new JsonReader(new FileReader(file));
                    Document doc = gson.fromJson(reader, Document.class);
                    doc.setCover(Document.DEFAULT_COVER);
                    if (doc.isCorrect()) return doc;
                }
                if (file.getName().contains(".txt")) {
                    Scanner reader = new Scanner(file);
                    String title = reader.nextLine();
                    String author = reader.nextLine();
                    String content = "";

                    while (reader.hasNextLine()){
                        String line = reader.nextLine();
                        if(line.isEmpty()) content += "\n\n";
                        else content += line;
                    }
                    Document doc = new Document(title,author,content);
                    doc.setCover(Document.DEFAULT_COVER);
                    if (doc.isCorrect()) return doc;
                }
            }
            throw new DocumentNotFoundException();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static boolean exportDocument(Stage st, Document document) throws ImportExportException {
        DocumentBasicInfo doc = new DocumentBasicInfo(document);
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("JSON file", "*.json"));
        fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("Text file", "*.txt"));
        fileChooser.setTitle("Export document");
        File file = fileChooser.showSaveDialog(st);

        try {
            if (file != null) {
                if(file.getName().contains(".json")){
                    Gson gson = new GsonBuilder().setPrettyPrinting().create();
                    Document2Export d2e = new Document2Export(document.getTitle(), document.getAuthor(), document.getContent());
                    String jsonDoc = gson.toJson(d2e);
                    FileWriter fw = new FileWriter(file);
                    BufferedWriter bw = new BufferedWriter(fw);
                    bw.write(jsonDoc);
                    bw.close();
                    return true;
                }
                else if(file.getName().contains(".txt")){
                    FileWriter fw = new FileWriter(file);
                    BufferedWriter bw = new BufferedWriter(fw);
                    bw.write(document.getTitle().toUpperCase());
                    bw.newLine();
                    bw.write(document.getAuthor());
                    bw.newLine();
                    bw.write(document.getContent());
                    bw.close();
                    return true;
                }
            }
            return false;
        } catch (IOException e) {
            throw new ImportExportException();
        }
    }
}
