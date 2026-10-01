package edu.upc.fib.prop.models;

import java.util.*;

public class SortedDocumentsSet{

    private TreeMap<Double, List<Document>> docs;

    private boolean limited;
    private int limit;
    private int size;

    //TODO: Remove if unused
    public SortedDocumentsSet(){
        limited = false;
        docs = new TreeMap<>(Collections.reverseOrder());
        size=0;
    }

    /**
     * permite definir un tamaño maximo
     * @param max tamaño maximo de la lista
     */
    public SortedDocumentsSet(int max){
        limited = true;
        limit = max;
        docs = new TreeMap<>(Collections.reverseOrder());
        size=0;
    }

    /**
     * Devuelve el tamaño de la lista
     * @return tamaño de la lista
     */
    public int getSize(){
        return this.size;
    }

    /**
     * Añade un elemento a la lista. Si está limitada y llena, se eliminará el documento con valor menor para hacer hueco.
     * @param doc Documento a añadir
     * @param weight Peso del documento
     */
    public void add(Document doc, Double weight){
        if(limited && size>=limit){
            putElement(doc, weight);
            removeLessWeighted();
        }
        else{
            putElement(doc, weight);
            size++;
        }
    }

    /**
     * Devuelve el documento en la posicion indicada
     * @param index posicion a la que se accede
     * @return devuelve el documento
     */
    public Document getDocument(int index){
        if(index>=size) return null;
        int cont = 0;
        for(Double weight : docs.keySet()){
            for(Document doc : docs.get(weight)){
                if(cont == index) return doc;
                cont++;
            }
        }
        return null;
    }

    /**
     * Devuelve el valor que acompaña al documento en la posicion indicada
     * @param index posicion a la que se accede
     * @return devuelve el valor
     */
    public Double getValue(int index){
        if(index>=size) return null;
        int cont = 0;
        for(Double weight : docs.keySet()){
            for(Document doc : docs.get(weight)){
                if(cont == index) return weight;
                cont++;
            }
        }
        return null;
    }

    /**
     * Elimina el ultimo documento
     */
    private void removeLessWeighted() {
        Double lowerKey =Collections.min(docs.keySet());
        if(docs.get(lowerKey).size()==1){
            docs.remove(lowerKey);
        }
        else {
            docs.get(lowerKey).remove(docs.get(lowerKey).size()-1);
        }
    }

    /**
     * Añade un elemento a la lista.
     * @param doc   documento a añadir
     * @param weight    peso del documento
     */
    private void putElement(Document doc, Double weight) {
        if(docs.containsKey(weight)){
            docs.get(weight).add(doc);
        }
        else{
            List<Document> l = new ArrayList<>();
            l.add(doc);
            docs.put(weight, l);
        }
        Comparator<Document> comp = (Document doc1, Document doc2) -> {
            if(doc1.getAuthor().toLowerCase().compareTo(doc2.getAuthor().toLowerCase()) > 0) return 1;
            else if(doc1.getAuthor().toLowerCase().equals(doc2.getAuthor().toLowerCase()) &&
                    doc1.getTitle().toLowerCase().compareTo(doc2.getTitle().toLowerCase()) > 0) return 1;
            else return 0;
        };

        Collections.sort(docs.get(weight), comp);
    }

    public TreeMap<Double, List<Document>> getDocs() {
        return docs;
    }
}
