package com.anash.bridge.abstraction;

import com.anash.bridge.abstraction.BaseList;

public class OrnamentedList extends BaseList {
    private char itemType;

    public char getItemType() {
        return itemType;
    }

    public void setItemType(char newItemType) {
        if (newItemType > ' ') {
            itemType = newItemType;
        }
    }

    @Override
    public String get(int index) {
        return itemType + " " + super.get(index);
    }
}
