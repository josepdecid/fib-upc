package edu.upc.fib.prop.models;

import java.util.Iterator;
import java.util.TreeMap;

public class WeightsVector implements Iterable<String> {

    private TreeMap<String, Float> vector;

    public WeightsVector(){
        vector = new TreeMap<>();
    }

    void put(String word, Float weight){
        vector.put(word,weight);
    }

    public void remove(String word){
        vector.remove(word);
    }

    public boolean contains(String word){
        return vector.containsKey(word);
    }

    public Float getWeight(String word){
        return vector.get(word);
    }

    public  TreeMap<String, Float> getVector(){
        return vector;
    }

    @Override
    public Iterator iterator() {
        return vector.keySet().iterator();
    }
}
