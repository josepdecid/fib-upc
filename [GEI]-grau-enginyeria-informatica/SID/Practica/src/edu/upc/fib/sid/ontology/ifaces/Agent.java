package edu.upc.fib.sid.ontology.ifaces;

import java.beans.PropertyChangeListener;
import java.io.Serializable;


public interface Agent extends jade.content.Concept, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

}
