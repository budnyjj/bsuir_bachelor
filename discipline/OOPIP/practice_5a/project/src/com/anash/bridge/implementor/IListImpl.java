package com.anash.bridge.implementor;

public interface IListImpl {
    public void addItem(String item);
    public void addItem(String item, int position);
    public void removeItem(String item);
    public int getNumberOfItems();
    public String getItem(int index);
    public boolean supportsOrdering();
}
