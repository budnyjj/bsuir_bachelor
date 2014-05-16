package com.anash.bridge.abstraction;

import com.anash.bridge.implementor.IListImpl;

public class BaseList {
    protected IListImpl implementor;

    public void setImplementor(IListImpl _implementor) {
        implementor = _implementor;
    }

    public void add(String item) {
        implementor.addItem(item);
    }

    public void add(String item, int position) {
        if (implementor.supportsOrdering()) {
            implementor.addItem(item, position);
        }
    }

    public void remove(String item) {
        implementor.removeItem(item);
    }

    public String get(int index) {
        return implementor.getItem(index);
    }

    public int count() {
        return implementor.getNumberOfItems();
    }
}
