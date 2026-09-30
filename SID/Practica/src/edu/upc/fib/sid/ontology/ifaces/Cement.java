package edu.upc.fib.sid.ontology.ifaces;

import java.io.Serializable;
import java.beans.PropertyChangeListener;

public interface Cement extends Factory, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

}
