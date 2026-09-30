package edu.upc.fib.sid.ontology.ifaces;

import java.beans.PropertyChangeListener;
import java.io.Serializable;

public interface PaperMill extends Factory, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

}
