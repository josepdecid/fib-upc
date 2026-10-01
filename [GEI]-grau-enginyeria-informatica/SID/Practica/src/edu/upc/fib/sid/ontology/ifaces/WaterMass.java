package edu.upc.fib.sid.ontology.ifaces;

import java.beans.PropertyChangeListener;
import java.io.Serializable;

public interface WaterMass extends jade.content.Concept, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

    public void setVolume(String value);

    public String getVolume();

    public void setContaminant(String value);

    public String getContaminant();

}
