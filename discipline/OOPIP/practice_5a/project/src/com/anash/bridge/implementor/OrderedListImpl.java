package com.anash.bridge.implementor;

import java.util.ArrayList;

public class OrderedListImpl implements IListImpl {
    private ArrayList items = new ArrayList();

    @Override
    public void addItem(String item) {
        if (!items.contains(item)) {
            items.add(item);
        }
    }

    @Override
    public void addItem(String item, int position) {
        if (!items.contains(item)) {
            items.add(position, item);
        }
    }

    @Override
    public void removeItem(String item) {
        if (items.contains(item)) {
            items.remove(items.indexOf(item));
        }
    }

    @Override
    public int getNumberOfItems() {
        return items.size();
    }

    @Override
    public String getItem(int index) {
        if (index < items.size()) {
            return (String) items.get(index);
        }
        return null;
    }

    @Override
    public boolean supportsOrdering() {
        return true;
    }
}
