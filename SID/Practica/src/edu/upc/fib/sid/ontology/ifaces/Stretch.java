package edu.upc.fib.sid.ontology.ifaces;

import java.beans.PropertyChangeListener;
import java.io.Serializable;

public interface Stretch extends River, Serializable {
    public void addPropertyChangeListener(PropertyChangeListener pcl);

    public void removePropertyChangeListener(PropertyChangeListener pcl);

    public void setNextStretch(Stretch value);

    public Stretch getNextStretch();

}
