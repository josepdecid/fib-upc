package edu.upc.fib.sid.ontology.impl;

import edu.upc.fib.sid.ontology.ifaces.RequestPour;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.Serializable;

public class RequestPourImpl implements RequestPour, Serializable {
    protected PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public void addPropertyChangeListener(PropertyChangeListener pcl) {
        pcs.addPropertyChangeListener(pcl);
    }

    public void removePropertyChangeListener(PropertyChangeListener pcl) {
        pcs.removePropertyChangeListener(pcl);
    }


    private static final long serialVersionUID = 5620337684464241768L;

    private String _internalInstanceName;

    public RequestPourImpl() {
        this._internalInstanceName = "";
    }

    public RequestPourImpl(String instance_name) {
        this._internalInstanceName = instance_name;
    }

    public String toString() {
        return _internalInstanceName;
    }

}
