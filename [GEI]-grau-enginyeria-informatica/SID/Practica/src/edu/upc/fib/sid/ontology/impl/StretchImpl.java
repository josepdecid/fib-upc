package edu.upc.fib.sid.ontology.impl;

import edu.upc.fib.sid.ontology.ifaces.Stretch;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.Serializable;

public class StretchImpl implements Stretch, Serializable {
    protected PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public void addPropertyChangeListener(PropertyChangeListener pcl) {
        pcs.addPropertyChangeListener(pcl);
    }

    public void removePropertyChangeListener(PropertyChangeListener pcl) {
        pcs.removePropertyChangeListener(pcl);
    }


    private static final long serialVersionUID = 5620337684464241768L;

    private String _internalInstanceName;

    public StretchImpl() {
        this._internalInstanceName = "";
    }

    public StretchImpl(String instance_name) {
        this._internalInstanceName = instance_name;
    }

    public String toString() {
        return _internalInstanceName;
    }

    private Stretch nextStretch;

    public void setNextStretch(Stretch value) {
        pcs.firePropertyChange("nextStretch", (this.nextStretch == null
                ? new StretchImpl()
                : this.nextStretch), value);
        this.nextStretch = value;
    }

    public Stretch getNextStretch() {
        return this.nextStretch;
    }

}
