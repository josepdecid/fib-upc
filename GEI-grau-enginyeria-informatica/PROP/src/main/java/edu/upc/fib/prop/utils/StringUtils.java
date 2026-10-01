package edu.upc.fib.prop.utils;

import com.google.gson.*;
import edu.upc.fib.prop.models.Document;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;

public class StringUtils {

    public static String hashData(String data) throws NoSuchAlgorithmException { MessageDigest md = MessageDigest.getInstance("SHA-256"); md.update(data.getBytes()); byte byteData[] = md.digest(); //Convert byte to hex format
        StringBuilder sb = new StringBuilder();
        for (byte aByteData : byteData) {
            sb.append(Integer.toString((aByteData & 0xff) + 0x100, 16).substring(1));
        } return sb.toString();
    }

    public static String buildJSONFromFrequencyMap(Map<String, Float> termFrequencies) {
        Gson gson = new Gson();
        return gson.toJson(termFrequencies);
    }

    public static String buildJSONFromPositionsMap(Map<String, Map<Integer, Set<Integer>>> termPositions) {
        Gson gson = new Gson();
        return gson.toJson(termPositions);
    }

    public static Map<String, Float> buildFrequencyMapFromJSON(String termFrequencies) {
        Map<String, Float> deserializedObject = new HashMap<>();
        JsonParser parser = new JsonParser();
        JsonObject jsonObject = parser.parse(termFrequencies).getAsJsonObject();
        for (Map.Entry<String, JsonElement> word : jsonObject.entrySet()) {
            deserializedObject.put(word.getKey(), Float.parseFloat(word.getValue().toString()));
        }
        return deserializedObject;
    }

    public static Map<String, Map<Integer, Set<Integer>>> buildPositionMapFromJSON(String termPositions) {
        Map<String, Map<Integer, Set<Integer>>> deserializedObject = new HashMap<>();
        JsonParser parser = new JsonParser();
        JsonObject jsonObject = parser.parse(termPositions).getAsJsonObject();
        for (Map.Entry<String, JsonElement> word : jsonObject.entrySet()) {
            for (Map.Entry<String, JsonElement> sentence : word.getValue().getAsJsonObject().entrySet()) {
                for (JsonElement offset : sentence.getValue().getAsJsonArray()) {
                    Integer sentenceNumber = Integer.parseInt(sentence.getKey());
                    Integer offsetNumber = Integer.parseInt(offset.toString());
                    if (deserializedObject.containsKey(word.getKey())) {
                        if (deserializedObject.get(word.getKey()).containsKey(sentenceNumber)) {
                            deserializedObject.get(word.getKey()).get(Integer.parseInt(sentence.getKey())).add(offsetNumber);
                        } else {
                            Set<Integer> offsets = new TreeSet<>();
                            offsets.add(offsetNumber);
                            deserializedObject.get(word.getKey()).put(sentenceNumber, offsets);
                        }
                    } else {
                        Set<Integer> offsets = new TreeSet<>();
                        offsets.add(offsetNumber);
                        Map<Integer, Set<Integer>> sentences = new TreeMap<>();
                        sentences.put(sentenceNumber, offsets);
                        deserializedObject.put(word.getKey(), sentences);
                    }
                }
            }
        }
        return deserializedObject;
    }

    public static Document parseJSONToDocument(String documentJSON) {
        JsonParser parser = new JsonParser();
        JsonObject jsonObject = parser.parse(documentJSON).getAsJsonObject();

        String title = jsonObject.get("title").getAsString();
        String authorName = jsonObject.get("author").getAsString();
        String content = jsonObject.get("content").getAsString();
        String cover = jsonObject.get("cover").getAsString();
        Document document = new Document(title, authorName, content);
        if(!cover.equals("")){
            document.setCover(cover);
        }
        return document;
    }
}
