package edu.upc.fib.sid.ontology.impl;

import edu.upc.fib.sid.ontology.ifaces.WaterMass;
import edu.upc.fib.sid.ontology.ifaces.WaterTank;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.Serializable;

public class WaterTankImpl implements WaterTank, Serializable {
    protected PropertyChangeSupport pcs = new PropertyChangeSupport(this);

    public void addPropertyChangeListener(PropertyChangeListener pcl) {
        pcs.addPropertyChangeListener(pcl);
    }

    public void removePropertyChangeListener(PropertyChangeListener pcl) {
        pcs.removePropertyChangeListener(pcl);
    }


    private static final long serialVersionUID = 5620337684464241768L;

    private String _internalInstanceName;

    public WaterTankImpl() {
        this._internalInstanceName = "";
    }

    public WaterTankImpl(String instance_name) {
        this._internalInstanceName = instance_name;
    }

    public String toString() {
        return _internalInstanceName;
    }

    private WaterMass hasWaterMass;

    public void setHasWaterMass(WaterMass value) {
        pcs.firePropertyChange("hasWaterMass", (this.hasWaterMass == null
                ? new WaterMassImpl()
                : this.hasWaterMass), value);
        this.hasWaterMass = value;
    }

    public WaterMass getHasWaterMass() {
        return this.hasWaterMass;
    }

    private Object ownedBy;

    public void setOwnedBy(Object value) {
        pcs.firePropertyChange("ownedBy", (this.ownedBy == null ? new Object() : this.ownedBy), value);
        this.ownedBy = value;
    }

    public Object getOwnedBy() {
        return this.ownedBy;
    }

}
